#pragma once
#include "../../Component/Core/Component.h"

namespace doom
{
	/// <summary>
	/// All CoreComponents should inherit this Class
	/// 
	/// WHAT IS CoreComponent??
	/// 
	/// 1. CoreComponent will be looped differently
	/// CoreComponent will be processed first 
	/// and PlainComponent is processed after that
	/// 
	/// </summary>
	class PlainComponent : public Component
	{
		friend class Entity;
		friend class Scene;
	private:

		PlainComponent(const PlainComponent&) = delete;
		PlainComponent(PlainComponent&&) noexcept = delete;
		PlainComponent& operator=(const PlainComponent&) = delete;
		PlainComponent& operator=(PlainComponent&&) noexcept = delete;

	protected:

		PlainComponent();
		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~PlainComponent();

		/// Dont put public to Internal Function For Protect use call Internal Function
		virtual void InitComponent_Internal(Entity& entity) final;
		virtual void InitComponent()
		{
			//DON'T PUT ANYTHING AT HERE
		}
		virtual void UpdateComponent_Internal() final;
		virtual void UpdateComponent()
		{
			//DON'T PUT ANYTHING AT HERE
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

	public:
	};

}