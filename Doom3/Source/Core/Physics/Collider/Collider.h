#pragma once
#include "RenderPhysics.h"
#include <StaticContainer/StaticContainer.h>
#include "ColliderType.h"
namespace doom
{
	namespace physics
	{
		class Collider : public RenderPhysics
		{
		public:
			

			virtual ColliderType GetColliderType() const = 0;
		};

	

	}
}