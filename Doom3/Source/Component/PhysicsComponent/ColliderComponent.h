#pragma once
#include "../Core/ServerComponent.h"
#include <StaticContainer/StaticContainer.h>

#include "Physics/Collider/AABB.h"
#include "utility/BVH/BVH_Node_Object.h"

namespace doom
{
	namespace physics 
	{
		class Physics_Server;
	}

	class ColliderComponent : public ServerComponent, public StaticContainer<ColliderComponent>, public BVH_AABB3D_Node_Object
	{
		friend class physics::Physics_Server;

	public:

		

	private:

		void ResetAllCollisionState();
	
		void UpdateLocalColliderAndLocalBVhAABBCache();

		void OnPreUpdatePhysics();
		void UpdatePhysics();
		void OnPostUpdatePhysics();

		/// <summary>
		/// Set Collider variable depending on Renderer's mesh
		/// </summary>
		void AutoColliderSetting();

	protected:

		DirtyReceiver bmIsWorldColliderDirty{ true };
		DirtyReceiver bmIsLocalColliderDirty{ true };
		void SetIsLocalColliderDirty();

		bool bmIsTrigger{ false };

		bool mbIsColliderEnter{ false };
		bool mbIsColliderExit{ false };
		bool mbIsColliderStay{ false };
		
		bool mbIsTriggerEnter{ false };
		bool mbIsTriggerExit{ false };
		bool mbIsTriggerStay{ false };
		
		void InitComponent() override;
		void UpdateComponent() final;
		virtual void FixedUpdateComponent() override;
		void OnEndOfFrame_Component() override;
		void OnDestroy() override;
		void OnActivated() override;
		void OnDeActivated() override;

		/// <summary>
		/// Never Update collider(like AABB3D, Circle2D, Ray) directly!!!
		/// Store collider information 
		/// </summary>
		virtual void UpdateWorldCollider() = 0;
		virtual void UpdateLocalCollider() = 0;

		/// <summary>
		/// Local AABB of Local Collider
		/// AABB is tighted to Local Collider
		/// 
		/// Returned AABB3D contain offset of Collider
		/// </summary>
		/// <returns></returns>
		virtual doom::physics::AABB3D ExtractLocalAABB3D() = 0;
		/// <summary>
		/// Call this function : UpdateLocalBVhColliderCache
		/// </summary>
		void UpdateLocalBVhAABBCacheFromLocalCollider();
		
		virtual math::Vector3 GetOffsetVector3() const = 0;
		
		virtual void AutoColliderSettingFromAABB3D(const physics::AABB3D & aabb3dFromMesh) = 0;
		/// <summary>
		/// return true if There is Renderer and have AABB3D
		/// </summary>
		/// <param name="aabb3D">aabb will be set by reference</param>
		/// <returns></returns>
		bool GetMeshAABB3D(physics::AABB3D& aabb3D);

		virtual physics::Collider* GetWorldCollider() = 0;

		const math::Matrix4x4& GetModelMatrix() const final;

	public:

	

		bool GetIsColliderEnter()
		{
			return this->mbIsColliderEnter;
		}

		bool GetIsColliderExit()
		{
			return this->mbIsColliderExit;
		}

		bool GetIsColliderStay()
		{
			return this->mbIsColliderStay;
		}


		bool GetIsTriggerEnter()
		{
			return this->mbIsTriggerEnter;
		}

		bool GetIsTriggerExit()
		{
			return this->mbIsTriggerExit;
		}

		bool GetIsTriggerStay()
		{
			return this->mbIsTriggerStay;
		}

		

	};
}
