#pragma once

#include <string>


namespace doom
{
	namespace stringHelper
	{
		typedef unsigned long DWORD;

		DWORD convert_ansi_to_unicode_string(
			std::wstring& unicode,
			const char* ansi,
			const size_t ansi_size
		);
		

		DWORD convert_unicode_to_ansi_string(
			std::string& ansi,
			const wchar_t* unicode,
			const size_t unicode_size
		);

		DWORD convert_unicode_to_utf8_string(
			std::string& utf8,
			const wchar_t* unicode,
			const size_t unicode_size
		);

		DWORD convert_utf8_to_unicode_string(
			std::wstring& unicode,
			const char* utf8,
			const size_t utf8_size
		);
	};
}

