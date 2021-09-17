#pragma once

#include <Matrix4x4.h>

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include <EasyDirtyChecker/DirtyReceiver.h>
#include "Graphics/Color.h"


namespace doom
{
	/// <summary>
	/// If you have object having BVH_Node
	/// maybe the object should have ColliderType variable locally 
	/// ( because Directly Updating aabb to bvh node is really idiot, BVH_Tree will be reconstructed  everytime when you update aabb )
	/// </summary>
	/// <typeparam name="ColliderType"></typeparam>
	template <typename ColliderType>
	class ColliderUpdater
	{
	private:

		ColliderType mLocalColliderCache{};
		/// <summary>
		/// Entity's Model Matrix * Local ColliderType
		/// </summary>
		ColliderType mWorldColliderCache{};
	
	

	protected:
		
		DirtyReceiver IsWorldColliderCacheDirty{ true };
		
		/// <summary>
		/// Local ColliderType should be updated instantly. 
		/// this function doesn't change BVH_TREE, just be stored locally. this is fine
		/// </summary>
		/// <param name="aabb3d"></param>
		void UpdateLocalColliderCache(const ColliderType& aabb);
		virtual const math::Matrix4x4& GetModelMatrix() = 0;

	public:
		
		ColliderType GetLocalColliderCache();
		const ColliderType* GetLocalColliderCache() const;

		const ColliderType* GetWorldColliderCache();
		void UpdateWorldColliderCache(bool clearDirty);

		void DrawWorldColliderCache(eColor color = eColor::Green, bool drawInstantly = false);
	};
	
	extern template class ColliderUpdater<doom::physics::AABB2D>;
	extern template class ColliderUpdater<doom::physics::AABB3D>;
	extern template class ColliderUpdater<doom::physics::Sphere>;
}


