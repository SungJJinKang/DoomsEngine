#pragma once

#include <unordered_map>
#include <vector>
#include <mutex>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include <CompilerMacros.h>

#include "DObject_Constant.h"

//#include "DObjectManager.reflection.h"
namespace dooms
{
	class DObject;
	class DOOM_API /*D_CLASS*/ DObjectManager
	{
		//GENERATE_BODY()

		friend class DObject;

	private:

		inline static std::atomic<UINT64> mDObjectCounter = 0;

		inline static std::unordered_map<DObject*, UINT64> mDObjectsHashmap{};

		static UINT64 GenerateNewDObejctID();

		inline static std::recursive_mutex DObjectListMutex{};
		static std::unordered_map<DObject*, UINT64>::iterator InsertDObjectIDIfExist(DObject* const dObject, const UINT64 dObjectID);
		static std::unordered_map<DObject*, UINT64>::iterator InsertDObjectID(DObject* const dObject, const UINT64 dObjectID);

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
