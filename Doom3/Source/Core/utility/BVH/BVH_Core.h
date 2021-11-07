#pragma once

#include <Core.h>

namespace dooms
{
	constexpr inline INT32 NULL_NODE_INDEX{ -1 };

	template <typename ColliderType>
	class BVH;
	
	template <typename ColliderType>
	struct BVH_Node;

	template <typename ColliderType>
	class ColliderUpdater;

	template <typename ColliderType>
	class BVH_Node_Container;

	template <typename ColliderType>
	class BVH_Node_Object;

	template <typename ColliderType>
	class BVH_Node_View;


}