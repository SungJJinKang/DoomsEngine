#pragma once

#include <vector>


#include "../Core.h"
#include "Entity.h"

namespace doom
{
	class World;
	/// <summary>
	/// user can't access to this class,
	/// only be accessed through World class
	/// </summary>
	class Scene
	{
		friend class World;
	private:
		std::vector<Entity> mSpawnedEntities;
		
	public:

		
	};
}