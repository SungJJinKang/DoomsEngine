#pragma once

#include <string>

namespace dooms
{
	class CommandLine
	{
	public:

		static void AppendCommandLine(const char* const InText);
		static const std::string& GetCommandLine();

	private:

		static std::string CommandLineString;
	};
}
