#include "TextAsset.h"

doom::TextAsset::TextAsset(const std::string& str)
{
	this->mText = str;
}

const std::string& doom::TextAsset::GetText()
{
	return this->mText;
}