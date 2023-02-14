#include "CommandLine.h"

std::string dooms::CommandLine::CommandLineString{};

void dooms::CommandLine::AppendCommandLineString(const char* const InStr)
{
	static bool bInit = false;

	if(bInit == true)
	{
		CommandLineString.append(" ");
	}
	bInit = true;

	CommandLineString.append(InStr);
}

const std::string& dooms::CommandLine::GetCommandLineString()
{
	return CommandLineString;
}

bool dooms::CommandLine::CheckCommandLineContainStr(const char* const InStr)
{
	return CommandLine::GetCommandLineString().find(InStr) != std::string::npos;
}
