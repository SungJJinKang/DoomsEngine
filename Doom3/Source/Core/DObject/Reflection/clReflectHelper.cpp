#include "clReflectHelper.h"

#include <CSharpHelper/SmartCSharpLibrary.h>

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


inline static const char* clReflectAdditionalCompilerOptions
#if defined(__GNUC__)  || defined( __clang__)
= "-fno-rtti";
#elif defined(_MSC_VER)
= "-fdiagnostics-format=msvc -fms-extensions -fms-compatibility -mms-bitfields -fdelayed-template-parsing -fno-rtti";
#endif      // -fms-extensions is important!!

void doom::clReflectHelper::AutoConfiguration()
{
	clScanPath = path::_GetCurrentPath("clscan.exe");
	clMergePath = path::_GetCurrentPath("clmerge.exe");
	clExportPath = path::_GetCurrentPath("clexport.exe");;
	ProjectFilePath = path::_GetCurrentPath("Doom3.vcxproj");
}

namespace doom
{
	namespace clReflectHelper
	{
		std::string Generate_clReflectAdditionalCompilerOptions()
		{
			std::string clReflectAdditionalCompilerOptionsString = clReflectAdditionalCompilerOptions;
			clReflectAdditionalCompilerOptionsString.append(" ");
			clReflectAdditionalCompilerOptionsString.append(CPP_VERSION_COMPILER_OPTION_FOR_CLANG);


			return clReflectAdditionalCompilerOptionsString;
		}

	}
}

bool doom::clReflectHelper::Generate_clReflect_BinaryReflectionData()
{
	const std::string currentPath_narrow_string = path::_GetCurrentPath();
	std::wstring currentPath { currentPath_narrow_string.begin(), currentPath_narrow_string .end() };
	currentPath += L"/";
	currentPath += clReflect_automation_dll_filename;

	doom::SmartCSharpLibrary c_sharp_library{ currentPath.c_str() };

	std::string clReflectArgs{};
	clReflectArgs.append(clScanPath);
	clReflectArgs.append(" ");
	clReflectArgs.append(clMergePath);
	clReflectArgs.append(" ");
	clReflectArgs.append(clExportPath);
	clReflectArgs.append(" ");
	clReflectArgs.append(ProjectFilePath);
	clReflectArgs.append(" ");
	clReflectArgs.append(Generate_clReflectAdditionalCompilerOptions());
	
	const std::wstring clReflect_additional_compiler_options_wide_string{ clReflectArgs.begin(), clReflectArgs.end() };
	
	return c_sharp_library.CallFunction("c_Generate_clReflect_data", clReflect_additional_compiler_options_wide_string.c_str());
}
