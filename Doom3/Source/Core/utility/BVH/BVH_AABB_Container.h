#pragma once

#include "../../Core.h"

#include <Matrix4x4.h>

#include "Physics/Collider/AABB.h"
#include <EasyDirtyChecker/DirtyReceiver.h>
#include "Graphics/Color.h"

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

		AABB mLocalBVhAABBCache{};
		/// <summary>
		/// Entity's Model Matrix * Local AABB
		/// </summary>
		AABB mWorldBVhAABBCache{};
	
		void ApplyModelMatrixToWorldBVhAABBCache();

	protected:
		
		DirtyReceiver IsWorldBVhAABBCacheDirty{ true };
		
		/// <summary>
		/// Local AABB should be updated instantly. 
		/// this function doesn't change BVH_TREE, just be stored locally. this is fine
		/// </summary>
		/// <param name="aabb3d"></param>
		void UpdateLocalBVhAABBCache(const AABB& aabb);
		virtual const math::Matrix4x4& GetModelMatrix() const = 0;

	public:
		
		AABB GetLocalBVhAABB3DCache();
		const AABB& GetLocalBVhAABB3DCache() const;
		const AABB& GetWorldBVhAABB3DCacheByReference();

		void DrawWorldBVhAABBCache(eColor color = eColor::Green);
	};
	
	extern template class BVH_AABB_Container<doom::physics::AABB2D>;
	extern template class BVH_AABB_Container<doom::physics::AABB3D>;
}


