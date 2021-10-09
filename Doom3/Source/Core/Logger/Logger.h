#pragma once

#ifdef DEBUG_MODE

#include <initializer_list>
#include <string>


namespace math
{
	template <size_t ComponentCount, typename T>
	struct Vector;

	using Vector2 = typename Vector<2, float>;
	using Vector3 = typename Vector<3, float>;
	using Vector4 = typename Vector<4, float>;
}

namespace doom
{
	namespace logger
	{
		enum class eLogType
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

		class DOOM_API Logger
		{
		public:
			
			static void InitLogger();

			static void StopIfError(eLogType logType);
			static void Log(const char* fileName, long codeLineNum, const char* log, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(const char* fileName, long codeLineNum, const std::string log, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(const char* fileName, long codeLineNum, std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) noexcept;
			static void Log(const char* fileName, long codeLineNum, std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) noexcept;
			
			//TODO : Support various type and multiple items
			//TODO : Requirement 
			// 1. when std::string is passed, take it as const std::string& ( for performance )
			// 2. take not string type (int, double, bool .....)
			// 3. take multiple items -> Use Variadic template and recursive
			// 4. don't require brace({}) when pass multiple items
			//static void Log(Last arg, eLogType logType = eLogType::D_LOG) noexcept;
			//static void Log(First firstArg, Args... args, eLogType logType = eLogType::D_LOG) noexcept;
			

			
		};
		
	
	}
}

using namespace doom::logger;
using doom::logger::eLogType;


#endif