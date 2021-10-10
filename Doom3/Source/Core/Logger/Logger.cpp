#include "Logger.h"

#ifdef DEBUG_MODE

#include <cstdarg>
#include <string>
#include <intrin.h>
#include <cstdio>
#include <type_traits>

#include <Graphics/DebugGraphics/DebugDrawer.h>
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Game/ConfigData.h"

#include <exception>



using namespace doom::logger;

namespace doom
{
	namespace logger
	{
		const char* LogTypeStr(eLogType logType) noexcept;

		class StdStreamLogger
		{
		private:


		public:
			constexpr StdStreamLogger() noexcept
			{

			}


			FORCE_INLINE void Log(const char* fileName, long codeLineNum, const char* log, eLogType logType = eLogType::D_LOG) const noexcept;
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType = eLogType::D_LOG) const noexcept;
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept;
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string>& logs, eLogType logType = eLogType::D_LOG) const noexcept;



		};

		class EmptyLogger
		{
		private:
			EmptyLogger()
			{

			}

		public:
			friend class Logger;

			FORCE_INLINE void Log(const char* fileName, long codeLineNum, const char* log, eLogType logType = eLogType::D_LOG) const noexcept {}
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType = eLogType::D_LOG) const noexcept {}
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept {}
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string>& logs, eLogType logType = eLogType::D_LOG) const noexcept {}
		};

		constexpr inline StdStreamLogger mLogger{};
		eLogType MIN_DEBUG_LEVEL{ eLogType::D_LOG };
		eLogType MAX_DEBUG_LEVEL{ eLogType::D_LOG };
		void Logger::InitLogger()
		{
			MIN_DEBUG_LEVEL = static_cast<eLogType>(::doom::ConfigData::GetSingleton()->GetConfigData().GetValue<int>("SYSTEM", "MIN_DEBUG_LEVEL"));
			MAX_DEBUG_LEVEL = static_cast<eLogType>(::doom::ConfigData::GetSingleton()->GetConfigData().GetValue<int>("SYSTEM", "MAX_DEBUG_LEVEL"));
		}

		FORCE_INLINE void Logger::StopIfError(eLogType logType)
		{
			if (logType == eLogType::D_ERROR)
			{
				std::fflush(stdout);
				std::terminate();
			}
		}
		void Logger::Log(const char* fileName, long codeLineNum, const char* log, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, log, logType);
				StopIfError(logType);
			}
		}
		void Logger::Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, log, logType);
				StopIfError(logType);
			}
		}
		void Logger::Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, logs, logType);
				StopIfError(logType);
			}
		}
		void Logger::Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string> logs, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, logs, logType);
				StopIfError(logType);
			}
		}

		/*
		template <typename Last>
		void Logger::Log(Last arg, eLogType logType) noexcept
		{
			if constexpr (std::is_same_v<char, std::remove_cv<Last>> || std::is_same_v< wchar_t, std::remove_cv<Last>> || std::is_same_v<std::string, std::remove_cv<Last>> || std::is_same_v<std::wstring, std::remove_cv<Last>>)
			{
				Logger.Log(firstArg);
			}
			else
			{
				Logger.Log(std::to_string(firstArg));
			}
		}
		template <typename First, typename... Args>
		void Logger::Log(First firstArg, Args... args, eLogType logType) noexcept
		{
			Logger::Log(firstArg, logType);

			Logger::Log(args..., logType);
		}
		*/



	}
}







FORCE_INLINE const char* doom::logger::LogTypeStr(eLogType logType) noexcept
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

FORCE_INLINE void StdStreamLogger::Log(const char* fileName, long codeLineNum, const char* log, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::printf("( %s ) %s at File : %s , Code Line : %d\n", LogTypeStr(logType), log, fileName, codeLineNum);
}



FORCE_INLINE void StdStreamLogger::Log(const char* fileName, long codeLineNum, std::string log, eLogType logType /*= Doom::LogType::D_LOG*/) const noexcept
{
	std::printf("( %s ) %s at File : %s , Code Line : %d\n", LogTypeStr(logType), log.c_str(), fileName, codeLineNum);
}


FORCE_INLINE void StdStreamLogger::Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::printf("( %s ) ", LogTypeStr(logType));
	for (const char* log : logs)
	{
		std::printf("%s", log);
	}
	std::printf("at File : %s , Code Line : %d\n", fileName, codeLineNum);
}

FORCE_INLINE void StdStreamLogger::Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string>& logs, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::printf("( %s ) ", LogTypeStr(logType));
	for (const std::string& log : logs)
	{
		std::printf("%s", log.c_str());
	}
	std::printf("at File : %s , Code Line : %d\n", fileName, codeLineNum);
}

#endif