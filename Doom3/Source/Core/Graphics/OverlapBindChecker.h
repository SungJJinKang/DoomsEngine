#pragma once

#include <unordered_map>

#include <Core.h>

#define USE_OVERLAP_BIND_CHECKER
#define MAX_BOUND_ID_COUNT 30
namespace dooms
{
	namespace graphics
	{

		class DOOM_API D_CLASS OverlapBindChecker
		{
		private:

			template <const char* str>
			inline static UINT32 mCurrentBoundId{};
			template <const char* str>
			inline static UINT32 mCurrentBoundIds[MAX_BOUND_ID_COUNT]{};
			template <const char* str>
			inline static UINT32 mCurrentBound2DIndexId[MAX_BOUND_ID_COUNT][MAX_BOUND_ID_COUNT]{};

		public:

			template <const char* str>
			FORCE_INLINE static void Bind(UINT32 id)
			{
				mCurrentBoundId<str> = id;
			}

			template <const char* str>
			FORCE_INLINE static void Bind(size_t index, UINT32 id)
			{
				mCurrentBoundIds<str>[index] = id;
			}

			template <const char* str>
			FORCE_INLINE static void Bind(size_t index1, size_t index2, UINT32 id )
			{
				mCurrentBound2DIndexId<str>[index1][index2] = id;
			}

	
			template <const char* str>
			FORCE_INLINE static UINT32 GetBoundID()
			{
				// if key doesn't exist yet, maybe 0 will be set
				return OverlapBindChecker::mCurrentBoundId<str>;
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

			template <const char* str>
			FORCE_INLINE static UINT32 GetBoundID(size_t index)
			{
				// if key doesn't exist yet, maybe 0 will be set
				return OverlapBindChecker::mCurrentBoundIds<str>[index];
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

			template <const char* str>
			FORCE_INLINE static UINT32 GetBoundID(size_t index1, size_t index2)
			{
				// if key doesn't exist yet, maybe 0 will be set
				return OverlapBindChecker::mCurrentBound2DIndexId<str>[index1][index2];
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
			template <const char* str>
			FORCE_INLINE static bool CheckIsNotBoundAndBindID(UINT32 id)
			{
				if (OverlapBindChecker::GetBoundID<str>() == id)
				{
					return false;
				}
				else
				{
					OverlapBindChecker::Bind<str>(id);
					return true;
				}
			}
			template <const char* str>
			FORCE_INLINE static bool CheckIsNotBoundAndBindID(size_t index, UINT32 id)
			{
				if (OverlapBindChecker::GetBoundID<str>(index) == id)
				{
					return false;
				}
				else
				{
					OverlapBindChecker::Bind<str>(index, id);
					return true;
				}
			}

			template <const char* str>
			FORCE_INLINE static bool CheckIsNotBoundAndBindID(size_t index1, size_t index2, UINT32 id)
			{
				if (OverlapBindChecker::GetBoundID<str>(index1, index2) == id)
				{
					return false;
				}
				else
				{
					OverlapBindChecker::Bind<str>(index1, index2, id);
					return true;
				}
			}
		};


	}
}

#ifdef USE_OVERLAP_BIND_CHECKER

#define D_OVERLAP_BIND_GET_BIND_ID(str) OverlapBindChecker::GetBoundID<str>()
#define D_OVERLAP_BIND_GET_BIND_ID_WITH_INDEX(str, index) OverlapBindChecker::GetBoundID<str>(index)
#define D_OVERLAP_BIND_GET_BIND_ID_WITH_DOUBLE_INDEX(str, index1, index2) OverlapBindChecker::GetBoundID<str>(index1, index2)
#define D_OVERLAP_BIND_CHECK_BINDID(str, id) OverlapBindChecker::Bind<str>(id)
#define D_OVERLAP_BIND_CHECK_BINDID_WITH_INDEX(str, index, id) OverlapBindChecker::Bind<str>(index, id)
#define D_OVERLAP_BIND_CHECK_BINDID_WITH_DOUBLE_INDEX(str, index1, index2, id) OverlapBindChecker::Bind<str>(index1, index2, id)
#define D_OVERLAP_BIND_CHECK_IS_ALREADY_BOUND(str, id) OverlapBindChecker::GetBoundID<str>() == id
#define D_OVERLAP_BIND_CHECK_IS_ALREADY_BOUND_WITH_INDEX(str, index, id) OverlapBindChecker::GetBoundID<str>(index) == id
#define D_OVERLAP_BIND_CHECK_IS_ALREADY_BOUND_WITH_DOUBLE_INDEX(str, index1, index2, id) OverlapBindChecker::GetBoundID<str>(index1, index2) == id
#define D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(str, id) OverlapBindChecker::CheckIsNotBoundAndBindID<str>(id)
#define D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_INDEX(str, index, id) OverlapBindChecker::CheckIsNotBoundAndBindID<str>(index, id)
#define D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(str, index1, index2, id) OverlapBindChecker::CheckIsNotBoundAndBindID<str>(index1, index2, id)


#else

#define D_OVERLAP_BIND_CHECK_BINDID(str, id)
#define D_OVERLAP_BIND_CHECK_IS_ALREADY_BOUND(str, id) false
#define D_OVERLAP_BIND_CHECK_CHECK_IS_ALREADY_BOUND_OR_NOT_BIND_ID(str, id)
#endif
