#include "FontAsset.h"

void dooms::asset::FontAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();
}

dooms::asset::eAssetType dooms::asset::FontAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::FONT;
}
