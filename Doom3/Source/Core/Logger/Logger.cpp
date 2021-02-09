#define MACRO_IMPLEMENTATION

#include "Logger.h"

#include <iostream>

using namespace doom::logger;


const char* doom::logger::LogTypeStr(eLogType logType) noexcept
{
	switch (logType)
	{
	case eLogType::D_LOG:
		return "LOG : ";
		break;

	case eLogType::D_WARNING:
		return "WARNING : ";
		break;

	case eLogType::D_ERROR:
		return "ERROR : ";
		break;

	default:
		__assume(0);
	}

	return "ERROR : ";
}

void StdStreamLogger::Log(const char* log, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType) << log << std::endl;
}


void StdStreamLogger::Log(std::string log, eLogType logType /*= Doom::LogType::D_LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType) << log << std::endl;
}


void StdStreamLogger::Log(std::initializer_list<const char*> logs, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType);
	for (auto c : logs)
		std::cerr << c;
	std::cerr << std::endl;
}

void StdStreamLogger::Log(std::initializer_list<const std::string> logs, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType);
	for (auto c : logs)
		std::cerr << c;
	std::cerr << std::endl;
}
