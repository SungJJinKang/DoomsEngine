#pragma once

#include <initializer_list>
#include <string>
#include "../Graphics/Color.h"
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
			
			static void StopIfError(eLogType logType);
			static void Log(const char* log, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(const std::string log, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) noexcept;
			
			//TODO : Support various type and multiple items
			//TODO : Requirement 
			// 1. when std::string is passed, take it as const std::string& ( for performance )
			// 2. take not string type (int, double, bool .....)
			// 3. take multiple items -> Use Variadic template and recursive
			// 4. don't require brace({}) when pass multiple items
			//static void Log(Last arg, eLogType logType = eLogType::D_LOG) noexcept;
			//static void Log(First firstArg, Args... args, eLogType logType = eLogType::D_LOG) noexcept;
			

			static void Draw3DLine(const math::Vector3& startPosition, const math::Vector3& endPosition, eColor color) noexcept;
			static void DrawSphere(const math::Vector3& centerPosition, float radius, eColor color) noexcept;
		};
		
	
	}
}

using namespace doom::logger;
using doom::logger::eLogType;


