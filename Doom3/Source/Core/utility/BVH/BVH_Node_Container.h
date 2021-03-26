#pragma once
#include "../../Core.h"

#include "BVH_Core.h"
#include "BVH_Node.h"
#include "BVH_Node_View.h"

namespace doom
{
	namespace physics
	{
		class Collider;
		class Ray;
	}

	template <typename ColliderType>
	class BVH_Node;

	template <typename ColliderType>
	class BVH_Node_Container
	{
		using node_view_type = typename BVH_Node_View<ColliderType>;

	private:

		

	protected:

		node_view_type mBVH_Node_View{};

		void InsertBVHLeafNode(BVH<ColliderType>& BVH, const ColliderType& Collider, doom::physics::Collider* collider);

		/// <summary>
		/// UpdateBVH_Node(const typename ColliderType::component_type& movedVector) is recommended than this function
		/// </summary>
		/// <param name="ColliderType"></param>
		void UpdateBVH_Node(const ColliderType& Collider);
		/// <summary>
		/// This function is recommended
		/// </summary>
		/// <param name="movedVector"></param>
		//void UpdateBVH_Node(const typename ColliderType::component_type& movedVector);
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
	using BVH_Node_ContainerSphere = typename BVH_Node_Container<doom::physics::Sphere>;

	extern template class BVH_Node_Container<doom::physics::AABB2D>;
	extern template class BVH_Node_Container<doom::physics::AABB3D>;
	extern template class BVH_Node_Container<doom::physics::Sphere>;
}
