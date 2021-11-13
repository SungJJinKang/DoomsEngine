#pragma once
#include "../../Component/Core/Component.h"

#include "PlainComponent.reflection.h"
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
	/// </summary>
	class DOOM_API D_CLASS PlainComponent : public Component
	{
		GENERATE_BODY()

		friend class Entity;
		friend class Scene;

		
		

	protected:

		

		/// Dont put public to Internal Function For Protect use call Internal Function
		virtual void InitComponent_Internal(Entity* entity) final;
		virtual void InitComponent()
		{
			//DON'T PUT ANYTHING AT HERE
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

// 		virtual void OnComponentAttachedToOwnerEntity(Component* newComponent) override {}
// 		virtual void OnComponentDettachedToOwnerEntity(Component* newComponent) override {}


		public:

			PlainComponent();
			/// <summary>
			/// Pure virtual destructor for make this class virtual cass
			/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
			/// </summary>
			/// <returns></returns>
			virtual ~PlainComponent();
			PlainComponent(const PlainComponent&) = default;
			PlainComponent(PlainComponent&&) noexcept = delete;
			PlainComponent& operator=(const PlainComponent&) = default;
			PlainComponent& operator=(PlainComponent&&) noexcept = delete;


	};

}