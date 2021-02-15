#pragma once

#include <initializer_list>
#include <string>

namespace math
{
	template <size_t ComponentCount, typename T>
	struct Vector;

	using Vector3 = typename Vector<3, float>;
	using Vector4 = typename Vector<4, float>;
}

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

		class Debug
		{
		public:
			

			static void Log(const char* log, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(const std::string log, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) noexcept;
			
			static void DrawLine(const math::Vector3& startPosition, const math::Vector3& endPosition, const math::Vector4& color) noexcept;
			static void DrawSphere(const math::Vector3& centerPosition, float radius, const math::Vector4& color) noexcept;
		};
		
	
	}
}

using namespace doom::logger;
using doom::logger::eLogType;

#ifdef MACRO_IMPLEMENTATION

#include <cstdarg>
#include <string>
#include "../Graphics/Graphics_Server.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Math/LightMath_Cpp/Vector4.h"

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

		void Debug::Log(const char* log, eLogType logType) noexcept
		{
			Logger.Log(log, logType);
		}
		void Debug::Log(const std::string log, eLogType logType) noexcept
		{
			Logger.Log(log, logType);
		}
		void Debug::Log(std::initializer_list<const char*> logs, eLogType logType) noexcept
		{
			Logger.Log(logs, logType);
		}
		void Debug::Log(std::initializer_list<const std::string> logs, eLogType logType) noexcept
		{
			Logger.Log(logs, logType);
		}

		void Debug::DrawLine(const math::Vector3& startPosition, const math::Vector3& endPosition, const math::Vector4& color) noexcept
		{
			doom::graphics::Graphics_Server::GetSingleton()->DebugDrawLine(startPosition, endPosition, color);
		}
		void Debug::DrawSphere(const math::Vector3& centerPosition, float radius, const math::Vector4& color) noexcept
		{
			doom::graphics::Graphics_Server::GetSingleton()->DebugDrawSphere(centerPosition, radius, color);
		}

	}
}

#endif


