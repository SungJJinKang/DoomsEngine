#pragma once
#include "../../Component/Core/Component.h"

namespace doom
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
	class ServerComponent : public Component
	{
		friend class Entity;
		friend class Scene;
	private:

		ServerComponent(const ServerComponent&) = delete;
		ServerComponent(ServerComponent&&) noexcept = delete;
		ServerComponent& operator=(const ServerComponent&) = delete;
		ServerComponent& operator=(ServerComponent&&) noexcept = delete;

	protected:

		ServerComponent();
		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~ServerComponent();

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
