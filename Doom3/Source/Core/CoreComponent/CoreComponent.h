#pragma once
#include "../../Component/Component.h"

namespace doom
{
	/// <summary>
	/// All CoreComponents should inherit this Class
	/// 
	/// WHAT IS CoreComponent??
	/// CoreComponent will be looped differently
	/// CoreComponent will be processed first 
	/// and PlainComponent is processed after that
	/// </summary>
	class CoreComponent : public Component
	{
		friend class Entity;
		friend class World;
	private:

		CoreComponent(const CoreComponent&) = delete;
		CoreComponent(CoreComponent&&) noexcept = delete;
		CoreComponent& operator=(const CoreComponent&) = delete;
		CoreComponent& operator=(CoreComponent&&) noexcept = delete;

	protected:

		CoreComponent();
		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~CoreComponent();

		/// <summary>
	/// This function will be called before Component object is attached to entity
	/// </summary>
	/// <param name="entity"></param>
		void Init_Internal(Entity& entity);
		/// <summary>
		/// This function will be called before Component object is attached to entity
		/// </summary>
		virtual void Init() override
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}

		/// <summary>
		/// This is called before OnUpdateComponent
		/// </summary>
		constexpr void Update_Internal()
		{
			Component::Update_Internal();
		}
		virtual void Update() override
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}

		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		constexpr void OnDestroy_Internal()
		{
			Component::OnDestroy_Internal();
		}
		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnDestroy() override
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}


		/// <summary>
		/// This function will be called after activated
		/// </summary>
		constexpr void OnActivated_Internal()
		{
			Component::OnActivated_Internal();
		}
		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnActivated() override
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}


		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		constexpr void OnDeActivated_Internal()
		{
			Component::OnDeActivated_Internal();
		}
		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnDeActivated() override
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}

	public:
	
	};
}
