#pragma once

#include <CompilerMacros.h>
#include <Macros/DllMarcos.h>
#include <Macros/TypeDef.h>

#ifdef DEBUG_MODE

#include <initializer_list>
#include <string>

#include "Reflection/Reflection.h"

#include <EngineGUI/GUIModules/LogGUI.h>
#include <EngineGUI/engineGUIServer.h>

#include "eLogType.h"

namespace dooms
{
	namespace logger
	{
		

		extern void InitLogger();
		extern void StopIfError(eLogType logType);
		extern void breakpoint();

		extern bool CheckLogAcceptable(const eLogType logType);
		
		inline extern const char* LogTypeStr(const eLogType logType) noexcept
		{
			switch (logType)
			{
			case eLogType::D_LOG:
				return "LOG";
				break;

			case eLogType::D_WARNING:
				return "WARNING";
				break;

			case eLogType::D_ERROR:
				return "ERROR";
				break;

			default:
				__assume(0);
			}

			return "ERROR";
		}

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
			template<typename ... Args>
			FORCE_INLINE void Log(const char* fileName, const long codeLineNum, const eLogType logType, const char* const format, Args ... args) noexcept
			{
				//dooms::ui::log::LogOnGUI("File : %s , Code Line : %d, Log Type : %s", fileName, codeLineNum, LogTypeStr(logType));
				dooms::ui::log::LogOnGUI(format, std::forward<Args>(args)...);
			}
		};





		template<typename ... Args>
		FORCE_INLINE void Log(const char* fileName, const long codeLineNum, const eLogType logType, const char* const format, Args ... args) noexcept
		{
			if (CheckLogAcceptable(logType) == true)
			{
				if(dooms::ui::engineGUIServer::GetIsEngineGUIAvaliable() == false)
				{
					StdStreamLogger::Log(fileName, codeLineNum, logType, format, std::forward<Args>(args)...);
				}

				GUILogger::Log(fileName, codeLineNum, logType, format, std::forward<Args>(args)...);
				
			}

			StopIfError(logType);
		}
	}
}

using dooms::logger::eLogType;


#endif