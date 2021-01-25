#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <optional>

#include "../Core.h"
#include "../../Component/Component.h"

namespace doom
{
	class Transform;
	class Entity
	{
	private:

		std::string mEntityName;
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };
		Transform* mTransform;

		std::vector<std::unique_ptr<Component>> mComponents;

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(T* component) noexcept
		{
			D_ASSERT(component->bIsAddedToEntity == false);

			this->mComponents.emplace(component);
			
			component->OnComponentAttached_Internal(*this);
			component->OnComponentActivated_Internal();
			//component->Init();
			//component->Start();
			return *component;
		}

	public:

		Entity();

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
		Component* mComponentCache = nullptr;

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		std::enable_if_t<std::is_base_of_v<Component, T>, T&> GetComponent()
		{
			if (mComponentCache != nullptr)
			{
				T* component = dynamic_cast<T*>(mComponentCache);
				if (component != nullptr)
				{
					DEBUG_LOG("Component Cache hit");
					return component;
				}
			}

			for (auto& component : this->mComponents)
			{
				component = dynamic_cast<T*>(component);
				if (component != nullptr)
				{
					return component;
				}

			}

			D_ASSERT(false);
			return nullptr;


		}


		template<typename T>
		std::vector<std::enable_if_t<std::is_base_of_v<Component, T>, std::vector<T&>>> GetComponents()
		{
			std::vector<T&> components;

			for (auto component : this->mComponents)
			{
				T* component = dynamic_cast<T*>(component);
				if (component != nullptr)
				{
					components.push_back(*component);
				}

			}

			return components;
		}

		template<typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of_v<Component, T>);

			for (auto iter = this->mComponents.begin() ; iter != this->mComponents.end() ; ++iter)
			{
				T* component = dynamic_cast<T*>(*iter);
				if (component != nullptr)
				{
					this->mComponents.erase(iter);
					return;
				}
			}

			return;
		}

		template<typename T>
		void RemoveComponents()
		{
			static_assert(std::is_base_of_v<Component, T>);

			for (auto iter = this->mComponents.begin(); iter != this->mComponents.end(); ++iter)
			{
				T* component = dynamic_cast<T*>(*iter);
				if (component != nullptr)
				{
					this->mComponents.erase(iter);
					--iter;
				}
			}

			return;
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

