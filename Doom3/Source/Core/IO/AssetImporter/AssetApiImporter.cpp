#include "AssetApiImporter.h"

void doom::assetimporter::ClearAllApiImporterQueue()
{
	ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FirstAssetType, ::doom::asset::LastAssetType, 1, ClearApiImporterQueueFunctor>();
}