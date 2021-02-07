#include "OverlapBindChecker.h"

std::unordered_map<std::string, unsigned int> doom::graphics::OverlapBindChecker::mCurrentBoundId{};

void doom::graphics::OverlapBindChecker::Bind(const char* str, unsigned int id)
{
	std::string key{ str };
	auto element = OverlapBindChecker::mCurrentBoundId.find(key);

	if (element == OverlapBindChecker::mCurrentBoundId.end())
	{//if key doesn't exitst
		OverlapBindChecker::mCurrentBoundId.insert({ key, id });
	}
	else
	{//key exist
		if ((*element).second == id)
		{//overlap bound
			D_DEBUG_LOG({ "Overlap Bind : ", str }, LogType::D_LOG);
		}
		else
		{
			(*element).second = id;
		}
	}
}