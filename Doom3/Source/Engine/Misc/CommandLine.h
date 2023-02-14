#pragma once

#include <string>

namespace dooms
{
	class CommandLine
	{
	public:

		static void AppendCommandLineString(const char* const InStr);
		static const std::string& GetCommandLineString(); 
		static bool CheckCommandLineContainStr(const char* const InStr);

	private:

		static std::string CommandLineString;
	};
}
