#pragma once

#include <unordered_map>
#include <string>

#include "../Core.h"

namespace doom
{
	namespace graphics
	{

		class OverlapBindChecker
		{
		private:
			static std::unordered_map<std::string, unsigned int> mCurrentBoundId;
		public:
			static void Bind(const char* str, unsigned int id);
		};


	}
}

#define DISABLE_OVERLAP_CHECK

#if defined(DEBUG_MODE) && !defined(DISABLE_OVERLAP_CHECK)
#define D_CHECK_OVERLAP_BIND(str, id) OverlapBindChecker::Bind(str, id);
#else
#define D_CHECK_OVERLAP_BIND(str, id) 
#endif