#include "clReflectHelper.h"

#include <string>

#include <Misc/DynamicLinkingHelper/SmartDynamicLinking.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>

#include <EngineGUI/PrintText.h>

#include "EngineConfigurationData/ConfigData.h"


namespace dooms
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

			//clReflectAdditionalCompilerOptionsString.append(" -I");
			//std::filesystem::path additionalDirectoryForClang = ""
			//clReflectAdditionalCompilerOptionsString.append(dooms::path::_GetCurrentPath(sourceDependencyFolderDirectory.generic_u8string()));

			clReflectAdditionalCompilerOptionsString.append(" -SD");
			std::filesystem::path sourceDependencyFolderDirectory = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "SOURCE_DEPENDENCIES_FOLDER_NAME");
			clReflectAdditionalCompilerOptionsString.append(dooms::path::_GetCurrentPath(sourceDependencyFolderDirectory.generic_u8string()));
			clReflectAdditionalCompilerOptionsString.append("\\");

			clReflectAdditionalCompilerOptionsString.append(" -ROOTCLASS_TYPENAME");
			clReflectAdditionalCompilerOptionsString.append("dooms::DObject");

			clReflectAdditionalCompilerOptionsString.append(" -REFLECTION_BINARY_FILENAME");
			clReflectAdditionalCompilerOptionsString.append(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "REFLECTION_BINARY_FILE_NAME"));

			if (ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "PRINT_GENERATE_REFLECTION_DATA_VERBOSE") == true)
			{
				clReflectAdditionalCompilerOptionsString.append(" -v"); // print clReflect verbose
			}

			clReflectAdditionalCompilerOptionsString.append(" ");
			clReflectAdditionalCompilerOptionsString.append(CPP_VERSION_COMPILER_OPTION_FOR_CLANG);

			clReflectAdditionalCompilerOptionsString.append(" ");
			clReflectAdditionalCompilerOptionsString.append(CPP_VERSION_COMPILER_OPTION_FOR_CLANG);

			return clReflectAdditionalCompilerOptionsString;
		}

		std::wstring GetclReflectAutomationArguments()
		{
			std::string clReflectArgs{};

			const std::filesystem::path clScanPath = path::_GetCurrentPath(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "CL_SCAN_RELATIVE_PATH"));
			clReflectArgs.append(clScanPath.generic_string());
			clReflectArgs.append(" ");

			const std::filesystem::path clMergePath = path::_GetCurrentPath(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "CL_MERGE_RELATIVE_PATH"));
			clReflectArgs.append(clMergePath.generic_string());
			clReflectArgs.append(" ");

			const std::filesystem::path clExportPath = path::_GetCurrentPath(ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "CL_EXPORT_RELATIVE_PATH"));
			clReflectArgs.append(clExportPath.generic_string());
			clReflectArgs.append(" ");

			const std::filesystem::path projectFilePath = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "PROJECT_VCXPROJ_PATH");
			clReflectArgs.append(projectFilePath.generic_string());
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
			clReflectArgs.append(dooms::clReflectHelper::Generate_clReflectAdditionalCompilerOptions());

			return std::wstring{ clReflectArgs.begin(), clReflectArgs.end() };



		}

		DWORD StartclReflect_automation(const std::string& filePath, const std::wstring& arguments)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			std::wstring filePath_wstring;
			filePath_wstring.assign(filePath.begin(), filePath.end());

			const std::wstring argumentForExe = filePath_wstring + L' ' + arguments;
			// Start the child process. 
			if (!CreateProcess(
				filePath_wstring.c_str(),   // No module name (use command line)
				const_cast<wchar_t*>(argumentForExe.c_str()),        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				0,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				)
			{
				D_ASSERT_LOG(false, "CreateProcess failed (%d).\n", GetLastError());
				dooms::ui::PrintText("CreateProcess failed (%d).\n", GetLastError());
				return 1;
			}

			// Wait until child process exits.
			WaitForSingleObject(pi.hProcess, INFINITE);

			DWORD exit_code;
			if (FALSE == GetExitCodeProcess(pi.hProcess, &exit_code))
			{
				D_ASSERT_LOG(false, "GetExitCodeProcess() failure: %u", GetLastError());
			}
			else if (STILL_ACTIVE == exit_code)
			{
				D_ASSERT_LOG(false, "Process is still running.");
			}

			// Close process and thread handles. 
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			return exit_code;
		}
	}
}


bool dooms::clReflectHelper::Generate_clReflect_BinaryReflectionData()
{
	dooms::ui::PrintText("Start to generate reflection data");


	//TODO : when call this function again in run-time, make argument string again???
	const std::wstring clReflect_additional_compiler_options_wide_string = GetclReflectAutomationArguments();
	
	const std::string currentPath_narrow_string = path::_GetCurrentPath();
	std::string currentPath{ currentPath_narrow_string.begin(), currentPath_narrow_string.end() };
	currentPath += "\\";
	currentPath += clReflect_automation_dll_filename;

	const DWORD result = StartclReflect_automation(currentPath, clReflect_additional_compiler_options_wide_string);

	return result == 0;
}

