#pragma once

#include <Core.h>
#include <vector>

namespace doom
{
	class DObject;
	class DObjectManager
	{	
		friend class DObject;

	private:

		inline static size_t mDObjectCounter = 0;
		inline static std::vector<DObject*> mDObjectsList{ std::vector<DObject*>(10000, nullptr) };

		static size_t GenerateNewDObejctID();
		static bool AddDObject(DObject* const dObject);
		static bool ReplaceDObject(DObject& originalDObject, DObject* const newDObject);
		static bool RemoveDObject(DObject* const dObject);

	public:

		static DObject* GetDObject(const size_t dObjectID);
		static void DestroyAllDObjects();
	};
}
