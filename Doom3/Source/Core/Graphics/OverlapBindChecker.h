#pragma once

#include <unordered_map>
#include <string>

#include "../Core.h"

#define USE_OVERLAP_BIND_CHECKER

namespace doom
{
	namespace graphics
	{

		class OverlapBindChecker
		{
		private:
			static std::unordered_map<const char*, unsigned int> mCurrentBoundId;
		public:

			FORCE_INLINE static void Bind(const char* str, unsigned int id)
			{
				OverlapBindChecker::mCurrentBoundId.insert_or_assign(str, id);
			}

			/// <summary>
			/// Check If target id is bound???
			/// </summary>
			/// <param name="str"></param>
			/// <param name="id"></param>
			/*
			FORCE_INLINE static bool CheckIsAlreadyBound(const char* str, unsigned int id)
			{
				auto element = OverlapBindChecker::mCurrentBoundId.find(str);
#ifdef DEBUG_MODE
				if (element == OverlapBindChecker::mCurrentBoundId.end() || (*element).second != id)
				{
					D_DEBUG_LOG({ std::string("Please Bind : ") + str + "  Required ID : " + std::to_string(id) }, eLogType::D_ERROR);
				}
#endif
			}
			*/

			FORCE_INLINE static unsigned int GetBoundID(const char* str)
			{
				// if key doesn't exist yet, maybe 0 will be set
				return OverlapBindChecker::mCurrentBoundId[str];
				/*
				auto element = OverlapBindChecker::mCurrentBoundId.find(str);

				if (element != OverlapBindChecker::mCurrentBoundId.end())
				{//if key exitst
					return (*element).second;
				}
				else
				{//key doesn't exist
					return 0;
				}
				*/
			}

			/// <summary>
			/// if ID is already bound, return true.
			/// else bind ID and return false
			/// </summary>
			/// <param name="str"></param>
			/// <param name="id"></param>
			/// <returns></returns>
			FORCE_INLINE static bool CheckIsNotBoundAndBindID(const char* str, unsigned int id)
			{
				if (OverlapBindChecker::GetBoundID(str) == id)
				{
					return false;
				}
				else
				{
					OverlapBindChecker::Bind(str, id);
					return true;
				}
			}

		};


	}
}

#ifdef USE_OVERLAP_BIND_CHECKER

#define D_OVERLAP_BIND_CHECK_BINDID(str, id) OverlapBindChecker::Bind(str, id)
#define D_OVERLAP_BIND_CHECK_IS_ALREADY_BOUND(str, id) OverlapBindChecker::GetBoundID(str) == id
#define D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(str, id) OverlapBindChecker::CheckIsNotBoundAndBindID(str, id)
#else

#define D_OVERLAP_BIND_CHECK_BINDID(str, id)
#define D_OVERLAP_BIND_CHECK_IS_ALREADY_BOUND(str, id) false
#define D_OVERLAP_BIND_CHECK_CHECK_IS_ALREADY_BOUND_OR_NOT_BIND_ID(str, id)
#endif
