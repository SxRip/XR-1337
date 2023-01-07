#include "config.hpp"

config::config() : _parser{ _config }, _config{}, _config_name{ "config.ini" }
{
}

bool config::create(const char* inject_method, const char* dll_path)
{
	_config.open(_config_name, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!_config.is_open())
		return false;

	const char* inject_mthd = inject_method ? inject_method : "STANDARD";
	const char* dll = dll_path ? dll_path : "xrEngine-1337.dll";

	_config << "[INJECT METHOD] " << inject_mthd << std::endl;
	_config << "[THE DLL NAME] " << dll << std::endl;

	_inject_data.inject_method = inject_mthd;
	_inject_data.dll_name = dll;

	return true;
}

std::string config::get_dll() noexcept
{
	std::string dll = _parser.get_dll();

	if (dll.empty())
		return {};

	if (std::filesystem::path(dll).extension().string().empty())
		dll.append(".dll");

	return get_full_path(dll.c_str());
}

std::string config::get_inject_method() noexcept
{
	return _parser.get_inject_method();
}

bool config::update() noexcept
{
	if (!_config.is_open())
		return false;

	_inject_data.inject_method = get_inject_method();
	_inject_data.dll_name = get_dll();

	return !_inject_data.dll_name.empty() && !_inject_data.inject_method.empty();
}

bool config::already_created() const noexcept
{
	return std::filesystem::exists(_config_name);
}

bool config::open(const char* config_name) noexcept
{
	_config.open(config_name ? config_name : _config_name, std::fstream::in | std::fstream::out);

	return _config.is_open();
}

void config::close() noexcept
{
	if (!_config.is_open())
		_config.close();
}


std::string config::config_parser::parse(const char* word) noexcept
{
	if (!_config || !_config->is_open())
		return {};

	_config->clear();
	_config->seekg(0, std::ios::beg);

	std::string _buffer;

	while (!_config->eof())
	{
		*_config >> _buffer;
		if (_buffer == word)
		{
			*_config >> _buffer;
			return _buffer;
		}
	}
	return {};
}

std::string config::config_parser::get_dll() noexcept
{
	return parse("NAME]");
}

std::string config::config_parser::get_inject_method() noexcept
{
	return parse("METHOD]");
}
