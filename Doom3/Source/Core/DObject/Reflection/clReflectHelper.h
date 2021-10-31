#pragma once

#include <Core.h>

#include <string>

namespace doom
{
	namespace clReflectHelper
	{
		inline extern const std::wstring clReflect_automation_dll_filename = L"clReflect_automation.dll";

		inline extern std::string clScanPath{};
		inline extern std::string clMergePath{};
		inline extern std::string clExportPath{};
		inline extern std::string ProjectFilePath{};

		extern void AutoConfiguration();
		
		extern bool Generate_clReflect_BinaryReflectionData();

	};
}