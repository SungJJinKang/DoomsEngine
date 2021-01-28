#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <optional>
#include <functional>

#include "../Core.h"
#include "../../Component/Component.h"
#include "World.h"
#include "../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"

namespace doom
{
	class Transform;
	class World;
	class Entity
	{
		friend class World;
	private:
		
		/// <summary>
		/// Entity Constructor should be called through World class
		/// </summary>
		Entity();
		/// <summary>
		/// Entity destructor should be called through Entity::Destory function
		/// </summary>
		~Entity();

		std::string mEntityName;
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };
		Transform* mTransform;

		std::vector<std::unique_ptr<Component, Component::Deleter>> mComponents;

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(T* component) noexcept
		{
			D_ASSERT(component->bIsAddedToEntity == false);

			this->mComponents.emplace_back(component);
			
			component->OnComponentAttached_Internal(*this);
			component->OnComponentActivated_Internal();
	
			return *component;
		}

		/// <summary>
		/// only called through Destructor
		/// </summary>
		void ClearComponents()
		{
			this->mComponents.clear();
		}

		/// <summary>
		/// AddComponent Internally
		/// Threre is no limitation on T
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent_Internal() noexcept
		{
			return AddComponent<T>(new T());
		}
	public:

		

		std::string_view EntityName()
		{
			return this->mEntityName;
		}

		Transform& _Transform()
		{
			return *this->mTransform;
		}

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent() noexcept
		{
			static_assert(!std::is_same_v<T, Transform>);
			return AddComponent<T>(new T());
		}

		template<typename T, typename... arguments>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(arguments&&... a) noexcept
		{
			static_assert(!std::is_same_v<T, Transform>);
			return AddComponent<T>(new T(std::forward<arguments>(a)...));
		}

		// TODO : cached component can be destroyed component 
		Component* mComponentPtrCache;

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		[[nodiscard]] std::enable_if_t<std::is_base_of_v<Component, T>, T*> GetComponent()
		{
			if (mComponentPtrCache != nullptr)
			{
				T* componentPtr = dynamic_cast<T*>(mComponentPtrCache);
				if (componentPtr != nullptr)
				{
					DEBUG_LOG("Component Cache hit");
					return componentPtr;
				}
			}

			for (auto& component : this->mComponents)
			{
				T* componentPtr = dynamic_cast<T*>(component.get());
				if (componentPtr != nullptr)
				{
					mComponentPtrCache = component;
					return componentPtr;
				}

			}

			D_ASSERT(false);
			return nullptr;
		}


		template<typename T>
		[[nodiscard]] std::vector<std::enable_if_t<std::is_base_of_v<Component, T>, std::vector<T*>>> GetComponents()
		{
			std::vector<T*> components;

			for (auto& component : this->mComponents)
			{
				T* componentPtr = dynamic_cast<T*>(component.get());
				if (componentPtr != nullptr)
				{
					components.push_back(componentPtr);
				}
			}

			return components;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		void RemoveComponent()
		{
			static_assert(!std::is_same_v<T, Transform>);
			for (size_t i = 0 ; i < this->mComponents.size() ; i++)
			{
				T* componentPtr = dynamic_cast<T*>(this->mComponents[i].get());
				if (componentPtr != nullptr)
				{//Check is sub_class of Component
					std::vector_swap_erase(this->mComponents, i);
					return;
				}
			}

			return;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		void RemoveComponents()
		{
			static_assert(!std::is_same_v<T, Transform>);
			for (size_t i = 0; i < this->mComponents.size(); i++)
			{
				T* componentPtr = dynamic_cast<T*>(this->mComponents[i].get());
				if (componentPtr != nullptr)
				{//Check is sub_class of Component
					std::vector_swap_erase(this->mComponents, i);
					--i;
				}
			}

			return;
		}

		
		void Destroy();

		//Event
		virtual void OnEntitySpawned(){}
		virtual void OnEntityDestroyed() {}

		virtual void OnEntityActivated() {}
		virtual void OnEntityDeActivated() {}

		virtual void OnPreUpdateComponents() {}
		void UpdateComponents();
		virtual void OnPostUpdateComponents() {}
	};


}

