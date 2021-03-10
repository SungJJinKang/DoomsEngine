#include "AssetApiImporter.h"

void doom::assetimporter::ClearAllApiImporterQueue()
{
	ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FirstAssetType, ::doom::asset::LastAssetType, eCondition_OperatorType::SmallerThanOrEqual, 1, ClearApiImporterQueueFunctor>();
}