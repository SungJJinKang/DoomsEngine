#pragma once

#include <vector>
#include <utility/BVH/BVH.h>
namespace doom
{
	namespace physics
	{
		class Collider;

		namespace PhysicsSolver
		{
			

			/// <summary>
			/// return Hit BVH Leaf Node Index List
			/// </summary>
			const std::vector<doom::physics::Collider*> GetCollideColliders
			(
				const doom::BVHAABB3D* bvhTree, const doom::physics::Collider* const col,  size_t& stackReservationCount
			);
			const std::vector<doom::physics::Collider*> GetCollideColliders
			(
				const doom::BVHAABB3D* bvhTree, const doom::physics::Collider* const col, 
				const typename BVHAABB3D::node_type* const BVHNode, size_t& stackReservationCount
			);
			const std::vector<const typename BVHAABB3D::node_type*> GetCollideBVHNodes
			(
				const doom::BVHAABB3D* bvhTree, const doom::physics::Collider* const col, size_t& stackReservationCount
			);

			const std::vector<doom::physics::Collider*> GetCollideColliders
			(
				const typename BVHAABB3D::node_type* const leafBVHNode
			);

			const std::vector<const typename BVHAABB3D::node_type*> GetCollideBVHNodes
			(
				const typename BVHAABB3D::node_type* const leafBVHNode
			);


			const std::vector<doom::physics::Collider*> GetCollideCollidersHillClimb
			(
				const doom::physics::Collider* const targetCollider,
				const typename BVHAABB3D::node_type* const targetColliderBVHNode,
				size_t& stackReservationCount
			);
		}
	}
}