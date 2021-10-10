#pragma once

#include "BVH_Core.h"
#include "../ColliderUpdater.h"
#include "BVH_Node_Container.h"

namespace doom
{
	/// <summary>
	/// Inherit this class
	/// This Class will help you manage BVH Node
	/// </summary>
	/// <typeparam name="ColliderType"></typeparam>
	template <typename ColliderType>
	class BVH_Node_Object : public doom::ColliderUpdater<ColliderType>, public doom::BVH_Node_Container<ColliderType>
	{
	private:

	protected:

		void UpdateBVH_Node();

	};

	

	using BVH_AABB2D_Node_Object = typename BVH_Node_Object<physics::AABB2D>;
	using BVH_AABB3D_Node_Object = typename BVH_Node_Object<physics::AABB3D>;
	using BVH_Sphere_Node_Object = typename BVH_Node_Object<physics::Sphere>;

	extern template class BVH_Node_Object<doom::physics::AABB2D>;
	extern template class BVH_Node_Object<doom::physics::AABB3D>;
	extern template class BVH_Node_Object<doom::physics::Sphere>;
}
