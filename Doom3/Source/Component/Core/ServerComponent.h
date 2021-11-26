#pragma once
#include "../../Component/Core/Component.h"

#include "ServerComponent.reflection.h"
namespace dooms
{
	/// <summary>
	/// All ServerComponents should inherit this Class
	/// 
	/// WHAT IS ServerComponent??
	/// 
	/// 1. ServerComponent will be looped differently
	/// ServerComponent will be processed first 
	/// and PlainComponent is processed after that
	/// 
	/// 2. !!!!!! ServerComponent is updated by ~_Server class
	/// 
	/// </summary>
	class DOOM_API D_CLASS ServerComponent : public Component
	{
		GENERATE_BODY()

		friend class Entity;
		friend class Scene;

		
		

	private:


	protected:

	

		/// Dont put public to Internal Function For Protect use call Internal Function
		virtual void InitComponent_Internal(Entity* entity) final;
		virtual void InitComponent()
		{
			//DON'T PUT ANYTHING AT HERE
		}
		virtual void LateInitComponent()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}
		virtual void UpdateComponent_Internal() final;
		virtual void UpdateComponent()
		{
			//DON'T PUT ANYTHING AT HERE
		}

		virtual void FixedUpdateComponent_Internal() final;
		virtual void FixedUpdateComponent()
		{
			//DONT PUT ANYTHING HERE, PUT AT HERE
		}

		virtual void OnEndOfFrame_Component_Internal() final;
		virtual void OnEndOfFrame_Component()
		{
			//DON'T PUT ANYTHING AT HERE
		}

		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnDestroy_Internal() final;
		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnDestroy() override
		{
			//DON'T PUT ANYTHING AT HERE
		}


		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnActivated_Internal() final;
		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnActivated() override
		{
			//DON'T PUT ANYTHING AT HERE
		}


		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnDeActivated_Internal() final;
		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnDeActivated() override
		{
			//DON'T PUT ANYTHING AT HERE
		}

		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField)
		{
			Base::OnChangedByGUI(dFieldOfChangedField);
		}

// 		virtual void OnComponentAttachedToOwnerEntity(Component* newComponent) override {}
// 		virtual void OnComponentDettachedToOwnerEntity(Component* newComponent) override {}

	public:

		ServerComponent();
		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~ServerComponent();

		ServerComponent(const ServerComponent&) = default;
		ServerComponent(ServerComponent&&) noexcept = delete;
		ServerComponent& operator=(const ServerComponent&) = default;
		ServerComponent& operator=(ServerComponent&&) noexcept = delete;
	
	};
}
