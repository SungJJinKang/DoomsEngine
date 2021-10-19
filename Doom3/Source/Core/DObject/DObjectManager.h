#pragma once

#include <unordered_map>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>

namespace doom
{
	class DObject;
	class DOOM_API DObjectManager
	{	
		friend class DObject;

	private:

		inline static UINT64 mDObjectCounter = 0;

		inline static std::unordered_map<DObject*, UINT64> mDObjectsList{};

		static UINT64 GenerateNewDObejctID();

		static std::unordered_map<DObject*, UINT64>::iterator InsertDObjectIDIfExist(DObject* const dObject, const UINT64 dObjectID);
		static std::unordered_map<DObject*, UINT64>::iterator InsertDObjectID(DObject* const dObject, const UINT64 dObjectID);

		static bool AddNewDObject(DObject* const dObject);
		static bool ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject);
		static bool RemoveDObject(DObject* const dObject);

	public:

		static void DestroyAllDObjects(const bool force);
		static void ClearConatiner();

		static bool IsDObjectValid(const DObject* const dObject);

		static bool IsEmpty();

		static SIZE_T GetDObjectCount();

	};
}
