#pragma once

#include <vector>
#include <mutex>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include <CompilerMacros.h>

#include "DObject_Constant.h"

#define DEFUALT_DOBJECT_LIST_RESERVATION_SIZE 1000

#include "DObjectManager.reflection.h"
namespace dooms
{
	class DObject;

	namespace gc
	{
		class GarbageCollectorManager;
	}

	struct DObjectsContainer
	{
		friend class DObject;

		std::vector<DObject*> mDObjectList;

		DObjectsContainer();
		DObjectsContainer(const DObjectsContainer&) = delete;
		DObjectsContainer(DObjectsContainer&&) noexcept = delete;
		DObjectsContainer& operator=(const DObjectsContainer&) = delete;
		DObjectsContainer& operator=(DObjectsContainer&&) noexcept = delete;

		bool IsEmpty() const;

		
	};

	class DOOM_API /*D_CLASS*/ DObjectManager
	{
		//GENERATE_BODY()

		friend class DObject;
		friend class gc::GarbageCollectorManager;

	private:

		inline static std::atomic<UINT64> mDObjectCounter = 0;

		/// <summary>
		/// this is need to be optimized
		///	because searching is too slow.
		/// </summary>
		inline static DObjectsContainer mDObjectsContainer{};

		static UINT64 GenerateNewDObejctID();

		static void InsertDObjectID(DObject* const dObject, const UINT64 dObjectID);

		static bool AddNewDObject(DObject* const dObject);
		static bool ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject);
		static bool RemoveDObject(DObject* const dObject);

	public:

		inline static std::recursive_mutex DObjectListMutex{};

		static void DestroyAllDObjects(const bool force);
		static void ClearConatiner();

		/*
		/// <summary>
		/// Check if DObject address is valid
		///	this function check if passed pointer is null and if passed address is alive dObject address
		/// </summary>
		/// <param name="dObject"></param>
		/// <returns></returns>
		static bool IsDObjectLowLevelValid(const DObject* const dObject, const bool lock = false, const std::memory_order memoryOrder = std::memory_order_relaxed);
		*/

		// TODO : implement this
		//static bool IsDObjectFastLowLevelValid(const DObject* const dObject, const bool lock = true);
		static bool IsDObjectExist(const DObject* const dObject, const bool lock = false);

		static bool IsEmpty();

		static size_t GetDObjectCount();

		static std::vector<DObject*>& GetDObjectList();
	};
}
