#pragma once

#include "../Core/Core.h"
namespace Doom
{
	class Entity;
	class Transform;
	class Component
	{
		friend class Entity;

	private:
		Entity* _OwnerEntity;
		/// <summary>
		/// Cache
		/// </summary>
		Transform* _Transform;
		bool isAddedToEntity;

		void InitComponent(Entity& entity);

	protected:

		virtual void OnInit() {}
		virtual void OnStart() {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}

	public:

		inline Entity& OwnerEntity()
		{
			return *_OwnerEntity;
		}

		inline Transform& Transform()
		{
			return *_Transform;
		}

		Component() : _OwnerEntity{}, _Transform{}, isAddedToEntity{}
		{

		}

		virtual ~Component()
		{

		}
	};
}