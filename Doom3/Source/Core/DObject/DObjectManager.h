#pragma once

#include <unordered_map>

namespace doom
{
	class DObject;
	class DObjectManager
	{	
		friend class DObject;

	private:

		inline static unsigned long long mDObjectCounter = 0;
		inline static std::unordered_map<DObject*, unsigned long long> mDObjectsList{};

		static size_t GenerateNewDObejctID();

		static std::unordered_map<DObject*, unsigned long long>::iterator SetDObjectID(DObject* const dObject, const unsigned long long dObjectID);

		static bool AddNewDObject(DObject* const dObject);
		static bool ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject);
		static bool RemoveDObject(DObject* const dObject);

	public:

		static void DestroyAllDObjects(const bool force);

		static bool IsDObjectValid(DObject* const dObject);

		static bool IsEmpty();

		static size_t GetDObjectCount();

	};
}
