#include "Logger.h"

#ifdef DEBUG_MODE

#include <cstdarg>
#include <string>
#include <cstdio>

#include "../Game/ConfigData.h"


using namespace dooms::logger;

namespace dooms
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

			void breakpoint() const;
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

			FORCE_INLINE void Log(const char* fileName, long codeLineNum, const char* log, eLogType logType = eLogType::D_LOG) const noexcept {}
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType = eLogType::D_LOG) const noexcept {}
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept {}
			FORCE_INLINE void Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string>& logs, eLogType logType = eLogType::D_LOG) const noexcept {}
		};

		constexpr inline StdStreamLogger mLogger{};
		eLogType MIN_DEBUG_LEVEL{ eLogType::D_LOG };
		eLogType MAX_DEBUG_LEVEL{ eLogType::D_LOG };
		void InitLogger()
		{
			MIN_DEBUG_LEVEL = static_cast<eLogType>(::dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("SYSTEM", "MIN_DEBUG_LEVEL"));
			MAX_DEBUG_LEVEL = static_cast<eLogType>(::dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("SYSTEM", "MAX_DEBUG_LEVEL"));
		}

		FORCE_INLINE void StopIfError(eLogType logType)
		{
			if (logType == eLogType::D_ERROR)
			{
				mLogger.breakpoint();
			}
		}
		void Log(const char* fileName, long codeLineNum, const char* log, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, log, logType);
				StopIfError(logType);
			}
		}
		void Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, log, logType);
				StopIfError(logType);
			}
		}
		void Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, logs, logType);
				StopIfError(logType);
			}
		}
		void Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string> logs, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(fileName, codeLineNum, logs, logType);
				StopIfError(logType);
			}
		}

		/*
		template <typename Last>
		void Log(Last arg, eLogType logType) noexcept
		{
			if constexpr (std::is_same_v<char, std::remove_cv<Last>> || std::is_same_v< wchar_t, std::remove_cv<Last>> || std::is_same_v<std::string, std::remove_cv<Last>> || std::is_same_v<std::wstring, std::remove_cv<Last>>)
			{
				logger.Log(firstArg);
			}
			else
			{
				logger.Log(std::to_string(firstArg));
			}
		}
		template <typename First, typename... Args>
		void Log(First firstArg, Args... args, eLogType logType) noexcept
		{
			Log(firstArg, logType);

			Log(args..., logType);
		}
		*/



	}
}







FORCE_INLINE const char* dooms::logger::LogTypeStr(eLogType logType) noexcept
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

void StdStreamLogger::breakpoint() const
{
	std::fflush(stdout);
	__debugbreak();
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