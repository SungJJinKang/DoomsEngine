#include "AssetApiImporter.h"

void doom::assetimporter::ClearAllApiImporterQueue()
{
	ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FIRST_ENUM_ASSETTYPE_VALUE, ::doom::asset::LAST_ENUM_ASSETTYPE_VALUE, eConditionType::LE, 1, ClearApiImporterQueueFunctor>();
}