#pragma once
#include "../../Core.h"

#include "BVH_Node.h"

namespace doom
{
	namespace physics
	{
		class Collider;
		class Ray;
	}

	template <typename AABB>
	class BVH_Node;

	template <typename AABB>
	class BVH_Node_Container
	{
	private:

		BVH_Node<AABB>* mBVH_NODE{ nullptr };

	protected:

		void InsertBVHLeafNode(BVH<AABB>& BVH, const AABB& AABB, doom::physics::Collider* collider);

		/// <summary>
		/// UpdateBVH_Node(const typename AABB::component_type& movedVector) is recommended than this function
		/// </summary>
		/// <param name="AABB"></param>
		void UpdateBVH_Node(const AABB& AABB);
		/// <summary>
		/// This function is recommended
		/// </summary>
		/// <param name="movedVector"></param>
		void UpdateBVH_Node(const typename AABB::component_type& movedVector);
		void RemoveBVH_Node();

	public:
		
		BVH_Node_Container() {}
		~BVH_Node_Container();

		BVH_Node_Container(const BVH_Node_Container&) = delete;
		BVH_Node_Container(BVH_Node_Container&&) noexcept = delete;
		BVH_Node_Container& operator=(const BVH_Node_Container&) = delete;
		BVH_Node_Container& operator=(BVH_Node_Container&&) noexcept = delete;

		bool RaycastToBVHNode(const physics::Ray& ray);
	};



	using BVH_Node_Container2D = typename BVH_Node_Container<doom::physics::AABB2D>;
	using BVH_Node_Container3D = typename BVH_Node_Container<doom::physics::AABB3D>;

	extern template class BVH_Node_Container<doom::physics::AABB2D>;
	extern template class BVH_Node_Container<doom::physics::AABB3D>;
}
