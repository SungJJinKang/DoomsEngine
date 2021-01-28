#pragma once

#include "../Core/Core.h"
namespace doom
{
	class Entity;
	class Transform;
	class Component
	{
		friend class Entity;

	private:
		bool bIsAddedToEntity;



		Entity* mOwnerEntity;
		/// <summary>
		/// Cache
		/// </summary>
		Transform* mTransform;
		
		bool mIsActivated;

	protected:

		/// <summary>
		/// Pure virtual destructor for make this class virtual cass
		/// Destructor should be called only from RemoveConponent(or clear component) of Entity class
		/// </summary>
		/// <returns></returns>
		virtual ~Component();
		Component();
	public:

		inline Entity& OwnerEntity()
		{
			return *mOwnerEntity;
		}

		inline Transform& Transform()
		{
			return *mTransform;
		}

		

		
		/// <summary>
		/// This function will be called before Component object is attached to entity
		/// </summary>
		/// <param name="entity"></param>
		void OnComponentAttached_Internal(Entity& entity);
		/// <summary>
		/// This function will be called before Component object is attached to entity
		/// </summary>
		virtual void OnComponentAttached() {}


		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		void OnComponentDestroyed_Internal();
		/// <summary>
		/// This function will be called before Component object is destroyed
		/// </summary>
		virtual void OnComponentDestroyed() {}


		/// <summary>
		/// This function will be called after activated
		/// </summary>
		void OnComponentActivated_Internal();
		/// <summary>
		/// This function will be called after activated
		/// </summary>
		virtual void OnComponentActivated() {}


		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		void OnComponentDeActivated_Internal();
		/// <summary>
		/// This function will be called after deactivated
		/// </summary>
		virtual void OnComponentDeActivated() {}

		//virtual void OnPreUpdateComponent() {}

		/// <summary>
		/// This is called before OnUpdateComponent
		/// </summary>
		void OnUpdateComponent_Internal();
		virtual void OnUpdateComponent() {}

		//virtual void OnPostUpdateComponent() {}
	};
}