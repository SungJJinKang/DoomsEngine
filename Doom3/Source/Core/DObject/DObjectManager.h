#pragma once

#include <Core.h>
#include <unordered_map>

namespace doom
{
	class DObject;
	class DObjectManager : public ISingleton<DObjectManager>
	{	
		friend class DObject;

	private:

		size_t mDObjectCounter = 0;
		std::unordered_map<size_t, DObject*> mDObjectsHashMap;

		size_t GenerateNewDObejctID();
		bool AddDObject(DObject* const dObject);
		bool ReplaceDObject(DObject& originalDObject, DObject* const newDObject);
		bool RemoveDObject(DObject* const dObject);

	public:

		DObject* GetDObject(const size_t dObjectID);
	
		DObjectManager();
		~DObjectManager();

	};
}
