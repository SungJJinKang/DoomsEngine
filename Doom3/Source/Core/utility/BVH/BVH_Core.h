#pragma once

#include "Core.h"

namespace doom
{
	constexpr inline int NULL_NODE_INDEX{ -1 };

	template <typename ColliderType>
	class BVH;
	
	template <typename ColliderType>
	class BVH_Node;

	template <typename ColliderType>
	class BVH_Collider_Container;

	template <typename ColliderType>
	class BVH_Node_Container;

	template <typename ColliderType>
	class BVH_Node_Object;

	template <typename ColliderType>
	class BVH_Node_View;


}