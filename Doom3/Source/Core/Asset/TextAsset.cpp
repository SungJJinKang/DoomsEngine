#include "TextAsset.h"

void doom::asset::TextAsset::SetText(const std::string& str)
{
	mText = str;
}

doom::asset::eAssetType doom::asset::TextAsset::GetEAssetType() const
{
	return doom::asset::eAssetType::TEXT;
}

const std::string& doom::asset::TextAsset::GetText()
{
	return mText;
}
