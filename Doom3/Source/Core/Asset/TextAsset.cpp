#include "TextAsset.h"

void doom::asset::TextAsset::SetText(const std::string& str)
{
	mText = str;
}

const std::string& doom::asset::TextAsset::GetText()
{
	return mText;
}