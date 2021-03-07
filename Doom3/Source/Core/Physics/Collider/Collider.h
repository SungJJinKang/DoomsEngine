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
		private :
			bool bmIsCollision{ false };
			void ClearCollision();

		protected:

			

		public:
			
			virtual ColliderType GetColliderType() const = 0;
			void CheckCollision(Collider* collider);

			virtual void DrawPhysicsDebug() final;
		};

	

	}
}