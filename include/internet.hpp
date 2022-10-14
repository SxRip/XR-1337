#pragma once
#include <string>
#include <urlmon.h>
#include <wininet.h>
#pragma comment (lib, "Wininet.lib")

std::string GetKey(const char* _Site)
{
	HINTERNET Browser = InternetOpen("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
	HINTERNET site = nullptr;

	if (!Browser)
		return "";

	site = InternetOpenUrl(Browser, _Site, nullptr, 0, 0, INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS);
	if (!site)
	{
		InternetCloseHandle(Browser);
		return "";
	}

	std::string msg;
	char buffer[50]{};
	DWORD bytes = 1;

	while (true)
	{
		InternetReadFile(site, buffer, 50, &bytes);
		if (!bytes)
			break;

		msg.append(buffer, bytes);
		ZeroMemory(buffer, 50);

		if (msg.size() > 50)
		{
			msg.clear();
			break;
		}
	}

	if (Browser)
		InternetCloseHandle(Browser);

	if (site)
		InternetCloseHandle(site);

	return msg;
}