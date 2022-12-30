#pragma once
#include <fstream>
#include <filesystem>

enum class INJECT_STATUS
{
	OK,
	ERROR_MEMORY_ALLOCATION,
	ERROR_MEMORY_WRITING,
	ERROR_CREATING_REMOTE_THREAD
};

class config
{
	class config_parser
	{
	public:
		config_parser() = default;
		config_parser(config_parser&) = delete;
		config_parser operator=(config_parser&&) = delete;

		config_parser(std::fstream& config) : _config{ &config } {}

		std::string get_dll() noexcept;
		std::string get_inject_method() noexcept;

	private:
		std::string parse(const char* word) noexcept;
		std::fstream* _config;
	};

public:

	typedef struct _INJECT_DATA
	{
		std::string dll_name;
		std::string inject_method;
	} INJECT_DATA;

	config(config&) = delete;
	config operator=(config&&) = delete;

	config();
	bool create(const char* inject_method = nullptr, const char* dll_path = nullptr);

	~config()
	{
		close();
	}

	std::string get_dll() noexcept;
	std::string get_inject_method() noexcept;

	bool update() noexcept;
	bool already_created() const noexcept;
	bool open(const char* config_name = nullptr) noexcept;

	void close() noexcept;

private:

	inline std::string get_full_path(const char* _File)
	{
		std::string _Path_with_file = std::filesystem::current_path().string();

		_Path_with_file.append("\\");
		_Path_with_file.append(_File);
		return _Path_with_file;
	}


	INJECT_DATA _inject_data;
	std::fstream _config;
	config_parser _parser;

	const std::string _config_name;
};