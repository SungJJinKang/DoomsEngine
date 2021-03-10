#include "OverlapBindChecker.h"

std::unordered_map<const char*, unsigned int> doom::graphics::OverlapBindChecker::mCurrentBoundId{};

void doom::graphics::OverlapBindChecker::Bind(const char* str, unsigned int id)
{
	auto element = OverlapBindChecker::mCurrentBoundId.find(str);

	if (element == OverlapBindChecker::mCurrentBoundId.end())
	{//if key doesn't exitst
		OverlapBindChecker::mCurrentBoundId.insert({ str, id });
	}
	else
	{//key exist
		if ((*element).second == id)
		{//overlap bound
			D_DEBUG_LOG({ "Overlap Bind : ", str }, eLogType::D_LOG);
		}
		else
		{
			(*element).second = id;
		}
	}
}

void doom::graphics::OverlapBindChecker::CheckIsBound(const char* str, unsigned int id)
{
	auto element = OverlapBindChecker::mCurrentBoundId.find(str);

	if (element == OverlapBindChecker::mCurrentBoundId.end() || (*element).second != id)
	{
		D_DEBUG_LOG({ std::string("Please Bind : ") + str + "  Required ID : " + std::to_string(id) }, eLogType::D_ERROR);
	}
}

unsigned int doom::graphics::OverlapBindChecker::GetBoundID(const char* str)
{
	auto element = OverlapBindChecker::mCurrentBoundId.find(str);

	if (element == OverlapBindChecker::mCurrentBoundId.end())
	{//if key doesn't exitst
		return 0;
	}
	else
	{//key exist
		return (*element).second;
	}
}
