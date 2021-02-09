#pragma once

#include <initializer_list>
#include <string>
namespace doom
{
	namespace logger
	{
		
		enum class eLogType
		{
			D_LOG,
			D_WARNING,
			D_ERROR
		};

		void Log(const char* log, eLogType logType = eLogType::D_LOG) noexcept;
		void Log(const std::string log, eLogType logType = eLogType::D_LOG) noexcept;
		void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) noexcept;
		void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) noexcept;
	}
}
using doom::logger::eLogType;

#ifdef MACRO_IMPLEMENTATION

#include <cstdarg>
#include <string>

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


			void Log(const char* log, eLogType logType = eLogType::D_LOG) const noexcept;
			void Log(const std::string log, eLogType logType = eLogType::D_LOG) const noexcept;
			void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept;
			void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) const noexcept;


		};

		class EmptyLogger
		{
		private:
			EmptyLogger()
			{

			}

		public:
			friend class Debug;

			inline void Log(const char* log, eLogType logType = eLogType::D_LOG) const noexcept {}
			inline void Log(const std::string log, eLogType logType = eLogType::D_LOG) const noexcept {}
			inline void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept {}
			inline void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) const noexcept {}
		};

		constexpr inline StdStreamLogger Logger{};

		void Log(const char* log, eLogType logType) noexcept
		{
			Logger.Log(log, logType);
		}
		void Log(const std::string log, eLogType logType) noexcept
		{
			Logger.Log(log, logType);
		}
		void Log(std::initializer_list<const char*> logs, eLogType logType) noexcept
		{
			Logger.Log(logs, logType);
		}
		void Log(std::initializer_list<const std::string> logs, eLogType logType) noexcept
		{
			Logger.Log(logs, logType);
		}

	}
}

#endif


