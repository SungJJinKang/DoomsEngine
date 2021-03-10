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
			static std::unordered_map<const char*, unsigned int> mCurrentBoundId;
		public:
			static void Bind(const char* str, unsigned int id);
			/// <summary>
			/// Check If target id is bound???
			/// </summary>
			/// <param name="str"></param>
			/// <param name="id"></param>
			static void CheckIsBound(const char* str, unsigned int id);
			static unsigned int GetBoundID(const char* str);
		};


	}
}


#if defined(DEBUG_MODE) && !defined(DISABLE_OVERLAP_CHECK)
#define D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(str, id) OverlapBindChecker::Bind(str, id);
#define D_CHECK_IS_BOUND(str, id) OverlapBindChecker::CheckIsBound(str, id);
#else
#define D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(str, id) 
#define D_CHECK_IS_BOUND(str, id) 
#endif