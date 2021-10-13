#pragma once

#include "RenderCollider.h"
#include <StaticContainer/StaticContainer.h>
#include "ColliderType.h"

namespace doom
{
	namespace physics
	{
		class DOOM_API Collider : public RenderCollider, public StaticContainer<Collider>
		{
		private:

			
			
		protected:

		public:

		
			Collider() {}
			virtual ~Collider() {}

			virtual ColliderType GetColliderType() const = 0;

			virtual void* data() = 0;
			virtual const void* data() const = 0;


		};

	

	}
}