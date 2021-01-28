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

		std::vector<Component*> mComponents;

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(T* component) noexcept
		{
			D_ASSERT(component->bIsAddedToEntity == false);

			this->mComponents.push_back(component);
			
			component->OnComponentAttached_Internal(*this);
			component->OnComponentActivated_Internal();
	
			return *component;
		}

		/// <summary>
		/// only called through Destructor
		/// </summary>
		void ClearComponents()
		{
			for (auto component : this->mComponents)
			{
				D_ASSERT(component != nullptr);
				delete component;
			}
		}
	public:

		

		std::string_view EntityName()
		{
			return this->mEntityName;
		}

		Transform& Transform()
		{
			return *this->mTransform;
		}

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent() noexcept
		{
			return AddComponent<T>(new T());
		}

		template<typename T, typename... arguments>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(arguments&&... a) noexcept
		{
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

			for (auto component : this->mComponents)
			{
				T* componentPtr = dynamic_cast<T*>(component);
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

			for (auto component : this->mComponents)
			{
				T* componentPtr = dynamic_cast<T*>(component);
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
			for (auto iter = this->mComponents.begin() ; iter != this->mComponents.end() ; ++iter)
			{
				T* componentPtr = dynamic_cast<T*>(*iter));
				if (componentPtr != nullptr)
				{//Check is sub_class of Component
					this->mComponents.erase(iter);
					delete componentPtr;
					return;
				}
			}

			return;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		void RemoveComponents()
		{
			for (auto iter = this->mComponents.begin(); iter != this->mComponents.end(); ++iter)
			{
				T* componentPtr = dynamic_cast<T*>((*iter).get());
				if (componentPtr != nullptr)
				{//Check is sub_class of Component
					this->mComponents.erase(iter);
					delete componentPtr;
					--iter;
				}
			}

			return;
		}

		void Destroy() 
		{
			delete this;
		}

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

