#include "Logger.h"



#ifdef DEBUG_MODE

#include <cstdarg>
#include <string>
#include <cstdio>

#include "../Game/ConfigData.h"
#include "LoggerSetting.h"


using namespace dooms::logger;

namespace dooms
{
	namespace logger
	{
		



	}
}


void dooms::logger::InitLogger()
{
	MIN_DEBUG_LEVEL = static_cast<eLogType>(::dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("SYSTEM", "MIN_DEBUG_LEVEL"));
	MAX_DEBUG_LEVEL = static_cast<eLogType>(::dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("SYSTEM", "MAX_DEBUG_LEVEL"));
}

void dooms::logger::StopIfError(eLogType logType)
{
	if (logType == eLogType::D_ERROR)
	{
		breakpoint();
	}
}


void dooms::logger::breakpoint()
{
	std::fflush(stdout);
	__debugbreak();
}

bool dooms::logger::CheckLogAcceptable(const eLogType logType)
{
	return logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL);
}


#endif
