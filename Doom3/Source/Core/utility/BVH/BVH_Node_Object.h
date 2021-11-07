#pragma once

#include "BVH_Core.h"
#include "../ColliderUpdater.h"
#include "BVH_Node_Container.h"

namespace dooms
{
	/// <summary>
	/// Inherit this class
	/// This Class will help you manage BVH Node
	/// </summary>
	/// <typeparam name="ColliderType"></typeparam>
	template <typename ColliderType>
	class BVH_Node_Object : public dooms::ColliderUpdater<ColliderType>, public dooms::BVH_Node_Container<ColliderType>
	{
	private:

	protected:

		void UpdateBVH_Node();

	public:

		virtual ~BVH_Node_Object();

	};

	

	//using BVH_AABB2D_Node_Object = typename BVH_Node_Object<physics::AABB2D>;
	using BVH_AABB3D_Node_Object = typename BVH_Node_Object<physics::AABB3D>;
	using BVH_Sphere_Node_Object = typename BVH_Node_Object<physics::Sphere>;

	//extern template class BVH_Node_Object<dooms::physics::AABB2D>;
	extern template class BVH_Node_Object<dooms::physics::AABB3D>;
	extern template class BVH_Node_Object<dooms::physics::Sphere>;
}
