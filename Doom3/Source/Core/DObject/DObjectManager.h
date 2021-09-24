#pragma once

#include <Core.h>
#include <unordered_map>

namespace doom
{
	class DObject;
	class DObjectManager
	{	
		friend class DObject;

	private:

		inline static size_t mDObjectCounter = 0;
		inline static std::unordered_map<size_t, DObject*> mDObjectsHashMap{};

		static size_t GenerateNewDObejctID();
		static bool AddDObject(DObject* const dObject);
		static bool ReplaceDObject(DObject& originalDObject, DObject* const newDObject);
		static bool RemoveDObject(DObject* const dObject);

	public:

		static DObject* GetDObject(const size_t dObjectID);
		static void DestroyAllDObjects();
	};
}
