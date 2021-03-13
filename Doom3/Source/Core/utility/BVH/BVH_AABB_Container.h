#pragma once

#include "../../Core.h"

#include <Matrix4x4.h>

#include "Physics/Collider/AABB.h"
#include <EasyDirtyChecker/DirtyReceiver.h>

namespace doom
{
	/// <summary>
	/// If you have object having BVH_Node
	/// maybe the object should have AABB variable locally 
	/// ( because Directly Updating aabb to bvh node is really idiot, BVH_Tree will be reconstructed  everytime when you update aabb )
	/// </summary>
	/// <typeparam name="AABB"></typeparam>
	template <typename AABB>
	class BVH_AABB_Container
	{
	private:

		AABB mLocal_BVH_AABB{};
		/// <summary>
		/// Entity's Model Matrix * Local AABB
		/// </summary>
		AABB mWorld_BVH_AABB{};
	
		void ApplyModelMatrixToWorld_BVH_AABB();

	protected:
		
		DirtyReceiver IsWorld_BVH_AABBDirty{ true };
		
		/// <summary>
		/// Local AABB should be updated instantly. 
		/// this function doesn't change BVH_TREE, just be stored locally. this is fine
		/// </summary>
		/// <param name="aabb3d"></param>
		void UpdateLocalAABB3D(const physics::AABB3D& aabb3d);
		virtual const math::Matrix4x4& GetModelMatrix() const = 0;

	public:
		
		physics::AABB3D GetLocalAABB3D();
		const physics::AABB3D& GetLocalAABB3D() const;
		physics::AABB3D GetWorldAABB3D();
		const physics::AABB3D& GetWorldAABB3D() const;
	};
	
	extern template class BVH_AABB_Container<doom::physics::AABB2D>;
	extern template class BVH_AABB_Container<doom::physics::AABB3D>;
}


