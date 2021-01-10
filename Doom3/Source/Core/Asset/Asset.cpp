#include "Asset.h"

void Doom::Asset::SetBaseMetaData(std::filesystem::path& path)
{
	AssetName = path.has_filename() ? path.filename().string() : "";
	AssetPath = path.string();
}


