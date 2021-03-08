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
		private :
			bool bmIsCollision{ false };
			void ClearCollision();

		protected:

			

		public:
			
			virtual ColliderType GetColliderType() const = 0;

			virtual void DrawPhysicsDebug() final;
		};

	

	}
}