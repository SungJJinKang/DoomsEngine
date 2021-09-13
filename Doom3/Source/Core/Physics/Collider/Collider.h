#pragma once
#include "RenderPhysics.h"
#include <StaticContainer/StaticContainer.h>
#include "ColliderType.h"

namespace doom
{
	namespace physics
	{
		class Collider : public RenderPhysics, public StaticContainer<Collider>
		{
			friend class ColliderPickingTestRoom;
			friend class Physics_Server;
		private:
			bool bmIsCollision{ false };
			void ClearCollision();

			

		protected:



		public:
			Collider() {}

			virtual ColliderType GetColliderType() const = 0;

#ifdef DEBUG_MODE
			virtual void DrawPhysicsDebug(bool drawInstantly = false) final;
#endif

			virtual void* data() = 0;
			virtual const void* data() const = 0;
		};

	

	}
}