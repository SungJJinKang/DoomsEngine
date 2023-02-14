#include "CommandLine.h"

std::string dooms::CommandLine::CommandLineString{};

void dooms::CommandLine::AppendCommandLine(const char* const InText)
{
	CommandLineString.append(InText);
	CommandLineString.append(" ");
}

const std::string& dooms::CommandLine::GetCommandLine()
{
	return CommandLineString;
}
