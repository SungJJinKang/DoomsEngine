#include "clReflectHelper.h"


#include <CSharpHelper/SmartCSharpLibrary.h>


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
			std::string clReflectAdditionalCompilerOptionsString = clReflectAdditionalCompilerOptionsForScpecificCompiler;
			clReflectAdditionalCompilerOptionsString.append(" ");
			clReflectAdditionalCompilerOptionsString.append(clReflectAdditionalCompilerOptionsPortable);
			clReflectAdditionalCompilerOptionsString.append(" -D");
			clReflectAdditionalCompilerOptionsString.append(clReflectAdditionalCompilerOptions_Configuration);

			clReflectAdditionalCompilerOptionsString.append(" ");
			clReflectAdditionalCompilerOptionsString.append(CPP_VERSION_COMPILER_OPTION_FOR_CLANG);


			return clReflectAdditionalCompilerOptionsString;
		}

	}
}


bool doom::clReflectHelper::Generate_clReflect_BinaryReflectionData()
{
	const std::string currentPath_narrow_string = path::_GetCurrentPath();
	std::string currentPath { currentPath_narrow_string.begin(), currentPath_narrow_string .end() };
	currentPath += "\\";
	currentPath += clReflect_automation_dll_filename;

	doom::SmartCSharpLibrary c_sharp_library{ currentPath };

	std::string clReflectArgs{};
	clReflectArgs.append(clScanPath.generic_string());
	clReflectArgs.append(" ");
	clReflectArgs.append(clMergePath.generic_string());
	clReflectArgs.append(" ");
	clReflectArgs.append(clExportPath.generic_string());
	clReflectArgs.append(" ");
	clReflectArgs.append(ProjectFilePath.generic_string());
	clReflectArgs.append(" ");

#ifdef DEBUG_MODE
	clReflectArgs.append("Debug");
#elif RELEASE_MODE
	clReflectArgs.append("Release");
#endif

	clReflectArgs.append(" ");

#ifdef OS_WIN64
	clReflectArgs.append("x64");
#elif OS_WIN32
	clReflectArgs.append("Win32");
#endif

	clReflectArgs.append(" ");
	clReflectArgs.append(Generate_clReflectAdditionalCompilerOptions());
	
	const std::wstring clReflect_additional_compiler_options_wide_string{ clReflectArgs.begin(), clReflectArgs.end() };

	int result;
	c_sharp_library.CallFunctionWithReturn<int>(clReflect_automation_dll_function_name.c_str(), result, clReflect_additional_compiler_options_wide_string.c_str());
	
	return result == 0;
}

