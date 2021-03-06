#include "TextAsset.h"

void doom::asset::TextAsset::SetText(const std::string& str)
{
	this->mText = str;
}

const std::string& doom::asset::TextAsset::GetText()
{
	return this->mText;
}