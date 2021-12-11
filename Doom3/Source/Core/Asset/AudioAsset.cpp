#include "AudioAsset.h"

void dooms::asset::AudioAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();
}

dooms::asset::eAssetType dooms::asset::AudioAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::AUDIO;
}
