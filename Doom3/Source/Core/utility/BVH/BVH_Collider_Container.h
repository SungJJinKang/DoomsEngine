#pragma once

#include <Matrix4x4.h>

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include <EasyDirtyChecker/DirtyReceiver.h>
#include "Graphics/Color.h"

#include "BVH_Core.h"

namespace doom
{
	/// <summary>
	/// If you have object having BVH_Node
	/// maybe the object should have ColliderType variable locally 
	/// ( because Directly Updating aabb to bvh node is really idiot, BVH_Tree will be reconstructed  everytime when you update aabb )
	/// </summary>
	/// <typeparam name="ColliderType"></typeparam>
	template <typename ColliderType>
	class BVH_Collider_Container
	{
	private:

		ColliderType mLocalBVhColliderCache{};
		/// <summary>
		/// Entity's Model Matrix * Local ColliderType
		/// </summary>
		ColliderType mWorldBVhColliderCache{};
	
	

	protected:
		
		DirtyReceiver IsWorldBVhColliderCacheDirty{ true };
		
		/// <summary>
		/// Local ColliderType should be updated instantly. 
		/// this function doesn't change BVH_TREE, just be stored locally. this is fine
		/// </summary>
		/// <param name="aabb3d"></param>
		void UpdateLocalBVhColliderCache(const ColliderType& aabb);
		virtual const math::Matrix4x4& GetModelMatrix() const = 0;

	public:
		
		ColliderType GetLocalBVhColliderCache();
		const ColliderType& GetLocalBVhColliderCache() const;

		const ColliderType& GetWorldBVhColliderCacheByReference();
		void UpdateWorldBVhColliderCache(bool force);

		void DrawWorldBVhColliderCache(eColor color = eColor::Green, bool drawInstantly = false);
	};
	
	extern template class BVH_Collider_Container<doom::physics::AABB2D>;
	extern template class BVH_Collider_Container<doom::physics::AABB3D>;
	extern template class BVH_Collider_Container<doom::physics::Sphere>;
}


