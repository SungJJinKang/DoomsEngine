#pragma once

#include <Doom_Core.h>

#include <filesystem>

struct aiScene;
namespace doom
{

	namespace assetExporter
	{
		namespace assetExporterThreeDModel
		{
			extern void ExportToAssFile(const std::filesystem::path& path, const aiScene* const pScene);

			extern void SetAssFileFormatId(const char* id);
		}
	}
}
