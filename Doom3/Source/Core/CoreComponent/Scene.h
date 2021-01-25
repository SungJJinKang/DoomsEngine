#pragma once

#include <vector>


#include "../Core.h"
#include "Entity.h"

namespace doom
{
	class Scene
	{
	private:
		std::vector<Entity> mSpawnedEntities;
		
		Entity& AddEntity();
		void RemoveEntity(const Entity& entity);
	public:

		
	};
}