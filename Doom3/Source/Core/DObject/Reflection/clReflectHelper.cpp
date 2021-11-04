#include "clReflectHelper.h"

#include <string>

#include <DynamicLinkingHelper/SmartDynamicLinking.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>

#include <UI/PrintText.h>

#include "Game/ConfigData.h"

void doom::clReflectHelper::AutoConfiguration()
{
	//TODO : 나중에 config로 빼자
	clScanPath = path::_GetCurrentPath(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "CL_SCAN_RELATIVE_PATH"));
	clMergePath = path::_GetCurrentPath(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "CL_MERGE_RELATIVE_PATH"));
	clExportPath = path::_GetCurrentPath(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "CL_EXPORT_RELATIVE_PATH"));;
	ProjectFilePath = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "PROJECT_VCXPROJ_PATH");


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


			if(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "PRINT_GENERATE_REFLECTION_DATA_VERBOSE"))
			{
				clReflectAdditionalCompilerOptionsString.append(" -v"); // print clReflect verbose
			}

			clReflectAdditionalCompilerOptionsString.append(" ");
			clReflectAdditionalCompilerOptionsString.append(CPP_VERSION_COMPILER_OPTION_FOR_CLANG);


			return clReflectAdditionalCompilerOptionsString;
		}

	}
}


bool doom::clReflectHelper::Generate_clReflect_BinaryReflectionData()
{
	doom::ui::PrintText("Start to generate reflection data");

	
	
	std::string clReflectArgs{};
	clReflectArgs.append(clScanPath.generic_string());
	clReflectArgs.append(" ");
	clReflectArgs.append(clMergePath.generic_string());
	clReflectArgs.append(" ");
	clReflectArgs.append(clExportPath.generic_string());
	clReflectArgs.append(" ");
	clReflectArgs.append(ProjectFilePath.generic_string());
	clReflectArgs.append(" ");

#if defined(DEBUG_MODE)
	clReflectArgs.append("Debug");
#elif defined(RELEASE_MODE)
	clReflectArgs.append("Release");
#endif

	clReflectArgs.append(" ");

#if defined(OS_WIN64)
	clReflectArgs.append("x64");
#elif defined(OS_WIN32)
	clReflectArgs.append("Win32");
#endif

	clReflectArgs.append(" ");
	clReflectArgs.append(Generate_clReflectAdditionalCompilerOptions());
	
	const std::wstring clReflect_additional_compiler_options_wide_string{ clReflectArgs.begin(), clReflectArgs.end() };

	int result = 1;

	const std::string currentPath_narrow_string = path::_GetCurrentPath();
	std::string currentPath{ currentPath_narrow_string.begin(), currentPath_narrow_string.end() };
	currentPath += "\\";
	currentPath += clReflect_automation_dll_filename;

	doom::SmartDynamicLinking c_sharp_library{ currentPath };
	auto future = doom::resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(
		std::function<void()>(
		[&]()
		{
			c_sharp_library.CallFunctionWithReturn<int>(clReflect_automation_dll_function_name.c_str(), result, clReflect_additional_compiler_options_wide_string.c_str());
		}
		)
	);

	future.wait();
	
	return result == 0;
}

