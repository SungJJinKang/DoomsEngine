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
		private:

			void LoadPhysicsSetting();
			
		public:

			PhysicsDebugger mPhysicsDebugger;

			Picking mPicking{};
			BVHAABB3D mPhysicsColliderBVH{ PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT };

			virtual void Init() final;
			virtual void Update() final;
			virtual void FixedUpdate() final;
			void FixedUpdateCollision();

			/// <summary>
			/// return Hit BVH Leaf Node Index List
			/// </summary>
			const std::vector<doom::physics::Collider*> GetCollideColliders(const doom::physics::Collider* const col, size_t& stackReservationCount) const;
			const std::vector<const typename BVHAABB3D::node_type*> GetCollideBVHNodes(const doom::physics::Collider* const col, size_t& stackReservationCount) const;

			const std::vector<doom::physics::Collider*> GetCollideColliders(const typename BVHAABB3D::node_type* const leafBVHNode) const;
			const std::vector<const typename BVHAABB3D::node_type*> GetCollideBVHNodes(const typename BVHAABB3D::node_type* const leafBVHNode) const;


			void SolveColliderComponents();

			virtual void OnEndOfFrame() final;

			void QueryCollision();


		};

	}
}

