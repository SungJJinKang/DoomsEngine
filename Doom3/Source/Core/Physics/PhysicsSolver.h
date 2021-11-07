#pragma once

#include <vector>
#include <utility/BVH/BVH.h>
namespace dooms
{
	namespace physics
	{
		class Collider;

		namespace PhysicsSolver
		{
			

			/// <summary>
			/// return Hit BVH Leaf Node Index List
			/// </summary>
			const std::vector<dooms::physics::Collider*> GetCollideColliders
			(
				const dooms::BVHAABB3D* bvhTree, const dooms::physics::Collider* const col,  size_t& stackReservationCount
			);
			const std::vector<dooms::physics::Collider*> GetCollideColliders
			(
				const dooms::BVHAABB3D* bvhTree, const dooms::physics::Collider* const col, 
				const typename BVHAABB3D::node_type* const BVHNode, size_t& stackReservationCount
			);
			const std::vector<const typename BVHAABB3D::node_type*> GetCollideBVHNodes
			(
				const dooms::BVHAABB3D* bvhTree, const dooms::physics::Collider* const col, size_t& stackReservationCount
			);

			const std::vector<dooms::physics::Collider*> GetCollideColliders
			(
				const typename BVHAABB3D::node_type* const leafBVHNode
			);

			const std::vector<const typename BVHAABB3D::node_type*> GetCollideBVHNodes
			(
				const typename BVHAABB3D::node_type* const leafBVHNode
			);


			const std::vector<dooms::physics::Collider*> GetCollideCollidersHillClimb
			(
				const dooms::physics::Collider* const targetCollider,
				const typename BVHAABB3D::node_type* const targetColliderBVHNode,
				size_t& stackReservationCount
			);
		}
	}
}