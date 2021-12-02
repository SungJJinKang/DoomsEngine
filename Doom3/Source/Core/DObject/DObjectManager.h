#pragma once

#include <vector>
#include <mutex>
#include <cassert>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include <CompilerMacros.h>

#include "DObject_Constant.h"

#define DEFUALT_DOBJECT_LIST_RESERVATION_SIZE 200

#include "DObjectManager.reflection.h"
namespace dooms
{
	class DObject;

	struct DObjectsContainer
	{
		friend class DObejct;

		std::vector<DObject*> mDObjectList;
		std::vector<UINT64> mDObjectIDList;
		std::vector<UINT32> mDObjectFlagList;

		DObjectsContainer();
		DObjectsContainer(const DObjectsContainer&) = delete;
		DObjectsContainer(DObjectsContainer&&) noexcept = delete;
		DObjectsContainer& operator=(const DObjectsContainer&) = delete;
		DObjectsContainer& operator=(DObjectsContainer&&) noexcept = delete;

		bool IsEmpty() const;

		FORCE_INLINE UINT32& GetDObjectFlag(const size_t index)
		{
			assert(index < mDObjectFlagList.size());
			return mDObjectFlagList[index];
		}
	};

	class DOOM_API /*D_CLASS*/ DObjectManager
	{
		//GENERATE_BODY()

		friend class DObject;

	private:

		inline static std::atomic<UINT64> mDObjectCounter = 0;

		/// <summary>
		/// this is need to be optimized
		///	because searching is too slow.
		/// </summary>
		inline static DObjectsContainer mDObjectsContainer{};

		static UINT64 GenerateNewDObejctID();

		inline static std::recursive_mutex DObjectListMutex{};
		static void InsertDObjectIDIfExist(DObject* const dObject);
		static void InsertDObjectID(DObject* const dObject, const UINT64 dObjectID);

		static bool AddNewDObject(DObject* const dObject);
		static bool ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject);
		static bool RemoveDObject(DObject* const dObject);

	public:

		static void DestroyAllDObjects(const bool force);
		static void ClearConatiner();

		/// <summary>
		/// Check if DObject address is valid
		///	this function check if passed pointer is null and if passed address is alive dObject address
		/// </summary>
		/// <param name="dObject"></param>
		/// <returns></returns>
		static bool IsDObjectStrongValid(const DObject* const dObject);

		static bool IsEmpty();

		static size_t GetDObjectCount();

	};
}
