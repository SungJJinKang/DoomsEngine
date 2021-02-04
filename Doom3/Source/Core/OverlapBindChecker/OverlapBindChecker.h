#pragma once

#include <unordered_map>
#include <string>

#include "../Core.h"

class OverlapBindChecker
{
private:
	static inline std::unordered_map<std::string, unsigned int> mCurrentBoundId{};
public:
	static inline void Bind(const char* str, unsigned int id)
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
};

#ifdef DEBUG_MODE
#define D_CHECK_OVERLAP_BIND(str, id) OverlapBindChecker::Bind(str, id);
#else
#define D_CHECK_OVERLAP_BIND(str, id) 
#endif