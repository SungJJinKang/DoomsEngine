#pragma once

#include <CompilerMacros.h>
#include <Macros/DllMarcos.h>
#include <Macros/TypeDef.h>

#ifdef DEBUG_MODE

#include <initializer_list>
#include <string>

#include "DObject/Reflection/Reflection.h"

namespace dooms
{
	namespace logger
	{
		enum class D_ENUM eLogType
		{
			D_LOG = 0,
			D_WARNING = 1,
			D_ERROR = 2,
			/// <summary>
			/// always call
			/// Remove this after use this
			/// </summary>
			D_ALWAYS = 3
		};
	
		extern void InitLogger();

		extern void StopIfError(eLogType logType);
		extern void Log(const char* fileName, long codeLineNum, const char* log, eLogType logType = eLogType::D_LOG) noexcept;
		extern void Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType = eLogType::D_LOG) noexcept;
		extern void Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) noexcept;
		extern void Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) noexcept;
		
		//TODO : Support various type and multiple items
		//TODO : Requirement 
		// 1. when std::string is passed, take it as const std::string& ( for performance )
		// 2. take not string type (INT32, FLOAT64, bool .....)
		// 3. take multiple items -> Use Variadic template and recursive
		// 4. don't require brace({}) when pass multiple items
		//static void Log(Last arg, eLogType logType = eLogType::D_LOG) noexcept;
		//static void Log(First firstArg, Args... args, eLogType logType = eLogType::D_LOG) noexcept;
		

	
	}
}

using dooms::logger::eLogType;


#endif