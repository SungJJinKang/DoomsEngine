#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include "../Core.h"
#include "../../Component/Component.h"

namespace Doom
{
	class Transform;
	class Entity
	{
	private:

		std::string _EntityName;
		Transform* _Transform;

		std::vector<Component*> Components;

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T*> AddComponent(T* component) noexcept
		{
#ifdef DEBUG_MODE
			if (component->isAddedToEntity == true)
			{
				DEBUG_LOG("Component is alread added", LogType::ERROR);
				return nullptr;
			}
#endif
			this->Components.push_back(component);
			component->InitComponent(*this);
			
			//component->Init();
			//component->Start();
			return component;
		}

	public:

		Entity();

		std::string_view EntityName()
		{
			return this->_EntityName;
		}

		Transform& Transform()
		{
			return *this->_Transform;
		}

		template<typename T>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T*> AddComponent() noexcept
		{
			return AddComponent(new T());
		}

		template<typename T, typename... arguments>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T*> AddComponent(arguments&&... a) noexcept
		{
			return AddComponent(new T(std::forward<arguments>(a)...));
		}

		// TODO : cached component can be destroyed component 
		Component* componentCache = nullptr;

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		std::enable_if_t<std::is_base_of_v<Component, T>, T*> GetComponent()
		{
			if (componentCache != nullptr)
			{
				T* component = dynamic_cast<T*>(component);
				if (component != nullptr)
				{
					DEBUG_LOG("Component Cache hit");
					return component;
				}
			}

			for (auto component : this->Components)
			{
				T* component = dynamic_cast<T*>(component);
				if (component != nullptr)
				{
					return component;
				}

			}
			return nullptr;


		}


		template<typename T>
		std::vector<std::enable_if_t<std::is_base_of_v<Component, T>, T*>> GetComponents()
		{
			std::vector<T*> components;

			for (auto component : this->Components)
			{
				T* component = dynamic_cast<T*>(component);
				if (component != nullptr)
				{
					components.push_back(component);
				}

			}

			return components;
		}

		template<typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of_v<Component, T>);

			for (auto iter = this->Components.begin() ; iter != this->Components.end() ; ++iter)
			{
				T* component = dynamic_cast<T*>(*iter);
				if (component != nullptr)
				{
					this->Components.erase(iter);
					return;
				}
			}

			return;
		}

		template<typename T>
		void RemoveComponents()
		{
			static_assert(std::is_base_of_v<Component, T>);

			for (auto iter = this->Components.begin(); iter != this->Components.end(); ++iter)
			{
				T* component = dynamic_cast<T*>(*iter);
				if (component != nullptr)
				{
					this->Components.erase(iter);
					--iter;
					return;
				}
			}

			return;
		}

		void UpdateComponents();

	};


}

