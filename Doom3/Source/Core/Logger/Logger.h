#pragma once

#include <CompilerMacros.h>

#include <string>


#include "eLogType.h"

namespace dooms
{
	namespace logger
	{
		

		extern void InitLogger();
		extern void StopIfError(eLogType logType);
		extern void breakpoint();

		extern bool CheckLogAcceptable(const eLogType logType);
		
		extern const char* LogTypeStr(const eLogType logType);

		namespace StdStreamLogger
		{
			template<typename ... Args>
			FORCE_INLINE void Log(const char* fileName, const long codeLineNum, const eLogType logType, const char* const format, Args ... args) noexcept
			{
				//std::printf("File : %s , Code Line : %d, Log Type : %s", fileName, codeLineNum, LogTypeStr(logType));
				std::printf(format, std::forward<Args>(args)...);
			}
		};

		namespace GUILogger
		{
			extern void LogToLogGUI(const char* const log);
			template<typename ... Args>
			FORCE_INLINE void Log(const char* fileName, const long codeLineNum, const eLogType logType, const char* const format, Args ... args) noexcept
			{
				char str[300];
				sprintf_s(str, 300, format, args...);
				LogToLogGUI(str);
			}
		};





		template<typename ... Args>
		FORCE_INLINE void Log(const char* fileName, const long codeLineNum, const eLogType logType, const char* const format, Args ... args) noexcept
		{
			if (CheckLogAcceptable(logType) == true)
			{
				StdStreamLogger::Log(fileName, codeLineNum, logType, format, std::forward<Args>(args)...);
				GUILogger::Log(fileName, codeLineNum, logType, format, std::forward<Args>(args)...);
			}

			StopIfError(logType);
		}
	}
}

using dooms::logger::eLogType;

