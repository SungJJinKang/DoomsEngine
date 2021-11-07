#include "TextAsset.h"

void dooms::asset::TextAsset::SetText(const std::string& str)
{
	mText = str;
}

dooms::asset::eAssetType dooms::asset::TextAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXT;
}

const std::string& dooms::asset::TextAsset::GetText()
{
	return mText;
}
