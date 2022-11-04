#include "Memory.hpp"

Memory* signature::_mem = nullptr;

bool BypassDebugging()
{
	PPEB ProcessPEB = GetCurrentPebProcess();

	if (!ProcessPEB)
		return false;

	if (static_cast<size_t>(ProcessPEB->BeingDebugged))
		ProcessPEB->BeingDebugged = 0;
	return true;
}

PPEB GetCurrentPebProcess()
{
	PROCESS_BASIC_INFORMATION ProcessInformation{};
	DWORD ReturnValue;

	NTSTATUS NotOK = NtQueryInformationProcess(GetCurrentProcess(),
		ProcessBasicInformation, &ProcessInformation, sizeof(PROCESS_BASIC_INFORMATION), &ReturnValue);

	if (NotOK || !ProcessInformation.PebBaseAddress)
		return nullptr;

	return ProcessInformation.PebBaseAddress;
}

bool Memory::nop(signature& _Sign) const noexcept
{
	return nop(*_Sign.get_ptr(), _Sign.get_nop_bytes());
}

bool Memory::path(signature& _Sign, const char* _PathSign, size_t _Size) const noexcept
{
	return path(*_Sign.get_ptr(), _PathSign, _Size);
}

void Memory::_nop(signature& _Sign) const noexcept
{
	_nop(*_Sign.get_ptr(), _Sign.get_nop_bytes());
}

void Memory::_path(signature& _Sign, const char* _PathSign, size_t _Size) const noexcept
{
	_path(*_Sign.get_ptr(), _PathSign, _Size);
}