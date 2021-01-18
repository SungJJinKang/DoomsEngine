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