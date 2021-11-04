#pragma once

#include <Core.h>

#include <string>
#include <filesystem>

namespace doom
{
	namespace clReflectHelper
	{

#if CURRENT_CPP_VERSION == CPP_98_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++98"
#elif CURRENT_CPP_VERSION == CPP_11_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++11"
#elif CURRENT_CPP_VERSION == CPP_14_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++14"
#elif CURRENT_CPP_VERSION == CPP_17_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++17"
#elif CURRENT_CPP_VERSION == CPP_20_VERSION 
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++20"
#endif

		inline static const char* const clReflectAdditionalCompilerOptionsPortable = "-fno-rtti -DUNICODE -D_HAS_STATIC_RTTI=0 -mavx2";

		inline static const char* const clReflectAdditionalCompilerOptionsForScpecificCompiler
#if defined(__GNUC__)  || defined( __clang__)
			= "";
#elif defined(_MSC_VER)
			= "-fdiagnostics-format=msvc -fms-extensions -fms-compatibility -mms-bitfields -fdelayed-template-parsing"; //-D_HAS_STATIC_RTTI=0 -> https://stackoverflow.com/questions/47950690/clang-stdfunction-and-fno-rtti
#endif      // -fms-extensions is important!!

		inline static const char* const clReflectAdditionalCompilerOptions_Configuration
#if defined(DEBUG_MODE)
			= "_DEBUG";
#elif defined(RELEASE_MODE)
			= "NDEBUG";
#endif

		inline extern const std::string clReflect_automation_dll_filename = "clReflect_automation.dll";
		inline extern const std::string clReflect_automation_dll_function_name = "c_Generate_clReflect_data";

		inline extern std::filesystem::path clScanPath{};
		inline extern std::filesystem::path clMergePath{};
		inline extern std::filesystem::path clExportPath{};
		inline extern std::filesystem::path ProjectFilePath{};
		inline extern std::filesystem::path SourceDependenciesFolderDirectory{};

		extern void AutoConfiguration();
		
		extern bool Generate_clReflect_BinaryReflectionData();

	};
}