#include "AssetApiImporter.h"

void doom::assetimporter::ClearAllApiImporterQueue()
{
	ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FIRST_ENUM_ASSETTYPE_VALUE, ::doom::asset::LAST_ENUM_ASSETTYPE_VALUE, eCondition_OperatorType::SmallerThanOrEqual, 1, ClearApiImporterQueueFunctor>();
}