#pragma once

#include "../Core/Core.h"
#include "../Core/Game/IGameFlow.h"

namespace doom
{
	class Entity;
	class Transform;
	class World;
	class Component : IGameFlow
	{
		friend class Entity;
		friend class World;
		friend class vector;

		struct Deleter
		{
			void operator()(Component* component) const
			{
				delete component;
			}
		};
	private:
		bool bIsAddedToEntity;



		Entity* mOwnerEntity;
		/// <summary>
		/// Cache
		/// </summary>
		Transform* mTransform;
		
		bool mIsActivated;

	protected:

		Component();

		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~Component();

		
		/// <summary>
		/// This function will be called before Component object is attached to entity
		/// </summary>
		/// <param name="entity"></param>
		void Init_Internal(Entity& entity); // Never put final to _InternalFunction 
	
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
		constexpr void Update_Internal(){}
		virtual void Update() override
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}

		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		constexpr void OnDestroy_Internal(){}
		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnDestroy()
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}


		/// <summary>
		/// This function will be called after activated
		/// </summary>
		constexpr void OnActivated_Internal(){}
		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnActivated()
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}


		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		constexpr void OnDeActivated_Internal(){}
		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnDeActivated()
		{
			//DONT PUT ANYTHING HERE, PUT AT _Internal
		}

	public:

	
		constexpr inline Entity* OwnerEntity()
		{
			return mOwnerEntity;
		}

		constexpr inline Transform* Transform()
		{
			return mTransform;
		}

		

		
		

		//virtual void OnPreUpdateComponent() {}

		

		//virtual void OnPostUpdateComponent() {}
	};
}