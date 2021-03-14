#pragma once

#include <Vector2.h>
#include <Vector3.h>


#include "BVH_AABB_Container.h"
#include "BVH_Node_Container.h"

namespace doom
{
	/// <summary>
	/// Inherit this class
	/// This Class will help you manage BVH Node
	/// </summary>
	/// <typeparam name="AABB"></typeparam>
	template <typename AABB>
	class BVH_Node_Object : public doom::BVH_AABB_Container<AABB>, public doom::BVH_Node_Container<AABB>
	{
	private:

	protected:

		void UpdateBVH_Node();

	};

	

	using BVH2D_Node_Object = typename BVH_Node_Object<physics::AABB2D>;
	using BVH3D_Node_Object = typename BVH_Node_Object<physics::AABB3D>;

	extern template class BVH_Node_Object<doom::physics::AABB2D>;
	extern template class BVH_Node_Object<doom::physics::AABB3D>;
}
