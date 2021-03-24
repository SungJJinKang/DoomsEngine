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

			inline static void Bind(const char* str, unsigned int id)
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

			/// <summary>
			/// Check If target id is bound???
			/// </summary>
			/// <param name="str"></param>
			/// <param name="id"></param>

			FORCE_INLINE static void CheckIsBound(const char* str, unsigned int id)
			{
				auto element = OverlapBindChecker::mCurrentBoundId.find(str);
#ifdef DEBUG_MODE
				if (element == OverlapBindChecker::mCurrentBoundId.end() || (*element).second != id)
				{
					D_DEBUG_LOG({ std::string("Please Bind : ") + str + "  Required ID : " + std::to_string(id) }, eLogType::D_ERROR);
				}
#endif
			}

			FORCE_INLINE static unsigned int GetBoundID(const char* str)
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

		};


	}
}

#define D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(str, id) OverlapBindChecker::Bind(str, id);
#define D_CHECK_IS_BOUND(str, id) OverlapBindChecker::CheckIsBound(str, id);
/*
//TODO : 무조건 Overlap 체크하는게 빠른지 보고 그냥 macro를 함수로 호출로 바꾸자
#if defined(DEBUG_MODE) && !defined(DISABLE_OVERLAP_CHECK)
#define D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(str, id) OverlapBindChecker::Bind(str, id);
#define D_CHECK_IS_BOUND(str, id) OverlapBindChecker::CheckIsBound(str, id);
#else
#define D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(str, id) 
#define D_CHECK_IS_BOUND(str, id) 
#endif
*/