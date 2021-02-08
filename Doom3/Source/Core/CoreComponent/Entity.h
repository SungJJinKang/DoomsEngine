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
#include "CoreComponent.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"
#include "../Game/IGameFlow.h"


namespace doom
{
	class Transform;
	class World;
	class Entity : IGameFlow
	{
		friend class World;

		struct Deleter
		{
			void operator()(Entity* entity) const
			{
				delete entity;
			}
		};
	private:
		
		/// <summary>
		/// Entity Constructor should be called through World class
		/// </summary>
		Entity(Entity* parent);
		/// <summary>
		/// Entity destructor should be called through Entity::Destory function
		/// </summary>
		~Entity();

		std::string mEntityName;
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };
		Transform* mTransform;

		Entity* mParent;
		std::vector<Entity*> mChilds;

		/// <summary>
		/// Plain component (not core component ) is stored at this variable
		/// </summary>
		std::vector<std::unique_ptr<Component, Component::Deleter>> mPlainComponents;
		/// <summary>
		/// Core component is stored at this variable
		/// </summary>
		std::vector<std::unique_ptr<CoreComponent, Component::Deleter>> mCoreComponents;

		template<typename T>
		static constexpr bool IsCoreComponent()
		{
			return std::is_base_of_v<CoreComponent, T>;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="component"></param>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		constexpr T* _AddComponent() noexcept
		{
			T* newComponent = new T();
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			if constexpr (Entity::IsCoreComponent<T>() == true)
			{
				this->mCoreComponents.emplace_back(newComponent);
			}
			else
			{
				this->mPlainComponents.emplace_back(newComponent);
			}
		

			newComponent->Init_Internal(*this);
			newComponent->OnActivated_Internal();

			return newComponent;

		}

		template<typename T>
		constexpr bool _RemoveComponent(std::unique_ptr<T>& component)
		{
			component->OnDestroy_Internal();
			component->OnDestroy();
			component.reset();
		}

		/// <summary>
		/// only called through Destructor
		/// </summary>
		void ClearComponents()
		{
			this->mPlainComponents.clear(); // destroy entities
			this->mCoreComponents.clear();
		}

	protected:

		virtual void Init() final {}
		virtual void Update() final
		{
			this->OnUpdate();
		}

	public:

		

		std::string_view GetEntityName() const;
		Transform* GetTransform() const;
		

		//TODO : Prevent Programmer Add TransformComponent.
		//TODO : Because All entity should have only one Transform Component

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		constexpr T* AddComponent() noexcept
		{
			return this->_AddComponent<T>();
		}

		/* THIS function can make mistake, Don't make this function(passing argumnet)
		template<typename T, typename... arguments>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(arguments&&... a) noexcept
		{
			return this->_AddComponent<T>(new T(std::forward<arguments>(a)...));
		}
		*/


		// TODO : cached component can be destroyed component 
		Component* mComponentPtrCache;

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] constexpr T* GetComponent() // never return unique_ptr reference, just return pointer
		{
			if (mComponentPtrCache != nullptr)
			{
				T* componentPtr = dynamic_cast<T*>(mComponentPtrCache);
				if (componentPtr != nullptr)
				{
					D_DEBUG_LOG("Component Cache hit");
					return componentPtr;
				}
			}

			if constexpr (Entity::IsCoreComponent<T>() == true)
			{// when component is coreComponent
				for (auto& coreComponent : this->mCoreComponents)
				{
					T* componentPtr = dynamic_cast<T*>(coreComponent.get());
					if (componentPtr != nullptr)
					{
						mComponentPtrCache = coreComponent;
						return componentPtr;
					}
				}
			}
			else
			{// when component is plainComponent
				for (auto& plainComponent : this->mPlainComponents)
				{
					T* componentPtr = dynamic_cast<T*>(plainComponent.get());
					if (componentPtr != nullptr)
					{
						mComponentPtrCache = plainComponent;
						return componentPtr;
					}
				}
			}
			

			return nullptr;
		}


		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] constexpr std::vector<T*> GetComponents()
		{
			std::vector<T*> components;

			if constexpr (Entity::IsCoreComponent<T>() == true)
			{// when component is coreComponent
				for (auto& coreComponent : this->mCoreComponents)
				{
					T* componentPtr = dynamic_cast<T*>(coreComponent.get());
					if (componentPtr != nullptr)
					{
						components.push_back(componentPtr);
					}
				}
			}
			else
			{// when component is plain component
				for (auto& plainComponent : this->mPlainComponents)
				{
					T* componentPtr = dynamic_cast<T*>(plainComponent.get());
					if (componentPtr != nullptr)
					{
						components.push_back(componentPtr);
					}
				}
			}

		

			return components;
		}

		

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T">if there is removed component</typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		constexpr bool RemoveComponent()
		{
			static_assert(!std::is_same_v<T, Transform>);

			if constexpr (Entity::IsCoreComponent<T>() == true)
			{// when component is coreComponent
				for (size_t i = 0; i < this->mCoreComponents.size(); i++)
				{
					T* componentPtr = dynamic_cast<T*>(this->mCoreComponents[i].get());
					if (componentPtr != nullptr)
					{//Check is sub_class of Component
						this->_RemoveComponent(this->mCoreComponents[i]);

						std::vector_swap_erase(this->mCoreComponents, i);
						return true;
					}
				}
			}
			else
			{// when component is plainComponent
				for (size_t i = 0; i < this->mPlainComponents.size(); i++)
				{
					T* componentPtr = dynamic_cast<T*>(this->mPlainComponents[i].get());
					if (componentPtr != nullptr)
					{//Check is sub_class of Component
						this->_RemoveComponent(this->mCoreComponents[i]);

						std::vector_swap_erase(this->mPlainComponents, i);
						return true;
					}
				}
			}
		
			

			return false;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		constexpr bool RemoveComponents()
		{
			static_assert(!std::is_same_v<T, Transform>);

			bool isRemoveSuccess{ false };
			if constexpr (Entity::IsCoreComponent<T>() == true)
			{// when component is coreComponent
				for (size_t i = 0; i < this->mCoreComponents.size(); i++)
				{
					T* componentPtr = dynamic_cast<T*>(this->mCoreComponents[i].get());
					if (componentPtr != nullptr)
					{//Check is sub_class of Component
						this->_RemoveComponent(this->mCoreComponents[i]);

						std::vector_swap_erase(this->mCoreComponents, i);
						--i;

						isRemoveSuccess = true;
					}
				}
			}
			else
			{// when component is plainComponent
				for (size_t i = 0; i < this->mPlainComponents.size(); i++)
				{
					T* componentPtr = dynamic_cast<T*>(this->mPlainComponents[i].get());
					if (componentPtr != nullptr)
					{//Check is sub_class of Component
						this->_RemoveComponent(this->mCoreComponents[i]);

						std::vector_swap_erase(this->mPlainComponents, i);
						--i;

						isRemoveSuccess = true;
					}
				}
			}
			

			return isRemoveSuccess;
		}

		
		void Destroy();

		//Event
		void OnSpawned(){}
		void OnDestroyed() {}

		void OnActivated() {}
		void OnDeActivated() {}

		void OnPreUpdate() {}
		void OnUpdate();
		void OnPostUpdate() {}
	};


}

