#pragma once

#include "RenderCollider.h"
#include <StaticContainer/StaticContainer.h>
#include "ColliderType.h"

namespace dooms
{
	namespace physics
	{
		class DOOM_API D_CLASS Collider : public RenderCollider //, public StaticContainer<Collider> Don't put this ( too slow )
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