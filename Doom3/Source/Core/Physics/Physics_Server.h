#pragma once
#include "../Core.h"

#include "../Game/IGameFlow.h"

#include "Picking.h"
#include "PhysicsDebugger.h"

#include "Physics_Setting.h"

#include "utility/BVH/BVH.h"

#define PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT 3000 // this include all internal node, leaf node

namespace doom
{
	class ColliderComponent;
	namespace physics
	{
		class DOOM_API Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{
			DOBJECT_CLASS_BODY(Physics_Server, doom::eDOBJECT_ClassFlags::NonCopyable);

		private:

			void LoadPhysicsSetting();
			void ResetCollisionData();

		public:
			
			BVHAABB3D mPhysicsColliderBVH{ PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT };

			virtual void Init() final;
			virtual void Update() final;
			virtual void FixedUpdate() final;
			void FixedUpdateCollision();
			


			void SolveColliderComponents();

			virtual void OnEndOfFrame() final;

			void QueryCollision();


		};

	}
}

