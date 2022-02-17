#pragma once

#include <Core.h>
#include <Misc/FrameDirtyChecker/FrameDirtyChecker.h>
#include <Scene/eEntityMobility.h>

#include "Component.reflection.h"
class DirtyReceiver;
D_NAMESPACE(dooms)
namespace dooms
{
	class Entity;
	class Transform;
	class Scene;
	
	/// <summary>
	/// Component Of Entity
	/// 
	/// HOW TO CREATE MY OWN COMPONENT :
	/// Don't inherit Component class
	/// Inherit ServerComponent Or PlainComponent
	/// 
	/// Never make Constructor with argument, Component Constructor should not have argument
	/// 
	/// Both ones have different 
	/// </summary>
	class DOOM_API D_CLASS Component : public DObject, public FrameDirtyChecker // : public GameFlow
	{
		GENERATE_BODY()

		friend class Entity;
		friend class Scene;
		
	private:

		//For Prevent Component copied or moved
		

		bool bIsAddedToEntity;
		Entity* mOwnerEntity;
		/// <summary>
		/// Cache
		/// </summary>
		Transform* mTransform;
		
		D_FUNCTION(INVISIBLE)
		void UpdateComponentEnabled();

		D_PROPERTY(CALLBACK = "UpdateComponentEnabled")
		bool IsComponentEnabled = true;
	
	protected:

		

		void AddLocalDirtyToTransformDirtyReceiver(DirtyReceiver& localDirty);

		/// Dont put public to Internal Function For Protect use call Internal Function
		virtual void InitComponent_Internal(Entity* entity);
		virtual void InitComponent()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}
		virtual void LateInitComponent()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}
		virtual void UpdateComponent_Internal();
		virtual void UpdateComponent()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}

		virtual void FixedUpdateComponent_Internal();
		virtual void FixedUpdateComponent()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}

		virtual void OnEndOfFrame_Component_Internal();
		virtual void OnEndOfFrame_Component()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}

		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnDestroy_Internal();
		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnDestroy()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}
		virtual void OnDestroyLate();

		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnActivated_Internal();
		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnActivated()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}


		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnDeActivated_Internal();
		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnDeActivated()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}


		/* can't do this because of recursive dependent
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		NO_DISCARD const T* GetComponent() // never return unique_ptr reference, just return pointer
		{
			return GetOwnerEntity()->GetComponent<T>();
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		NO_DISCARD const std::vector<T*> GetComponents()
		{
			return GetOwnerEntity()->GetComponents<T>();
		}
		*/

// 		virtual void OnComponentAttachedToOwnerEntity(Component* newComponent) {}
// 		virtual void OnComponentDettachedToOwnerEntity(Component* newComponent) {}

		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField)
		{
			Base::OnChangedByGUI(dFieldOfChangedField);
		}

	public:

		

		virtual void OnSetPendingKill() override;

		Component();

		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~Component();
		Component(const Component&);
		Component(Component&&) noexcept = delete;
		Component& operator=(const Component&);
		Component& operator=(Component&&) noexcept = delete;

		UINT32 GetOwnerEntityLayerIndex() const;

		void SetComponentEnabled(const bool isEnabled);
		FORCE_INLINE bool GetIsComponentEnabled() const
		{
			return IsComponentEnabled;
		}

		FORCE_INLINE Entity* GetOwnerEntity()
		{
			D_ASSERT(mOwnerEntity != nullptr); // mOwnerEntity is set at InitComponent_Internal ( not Constructor )
			return mOwnerEntity;
		}
		FORCE_INLINE const Entity* GetOwnerEntity() const
		{
			D_ASSERT(mOwnerEntity != nullptr); // mOwnerEntity is set at InitComponent_Internal ( not Constructor )
			return mOwnerEntity;
		}

		FORCE_INLINE Transform* GetTransform()
		{
			return mTransform;
		}
		FORCE_INLINE const Transform* GetTransform() const
		{
			return mTransform;
		}
		

		
		
		// TODO : Add Preupdate
		//virtual void OnPreUpdateComponent() {}
		//virtual void OnPostUpdateComponent() {}

		D_FUNCTION()
		void DestroyThisComponent();

		virtual void OnEntityMobilityChanged(const eEntityMobility entityMobility){}

	};
}