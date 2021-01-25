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
		Entity* mOwnerEntity;
		/// <summary>
		/// Cache
		/// </summary>
		Transform* mTransform;
		bool bIsAddedToEntity;

	protected:

	

	public:

		inline Entity& OwnerEntity()
		{
			return *mOwnerEntity;
		}

		inline Transform& Transform()
		{
			return *mTransform;
		}

		Component();

		virtual ~Component();

		void OnComponentAttached_Internal(Entity& entity);
		virtual void OnComponentAttached() {}

		void OnComponentDestroyed_Internal();
		virtual void OnComponentDestroyed() {}

		void OnComponentActivated_Internal();
		virtual void OnComponentActivated() {}

		void OnComponentDeActivated_Internal();
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