#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <functional>
#include <utility>
#include <typeinfo>

#include "../Core.h"
#include "../../Component/Core/Component.h"
#include "../../Component/Core/ServerComponent.h"

#include "../../Component/Transform.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"
#include "../Game/FrameDirtyChecker.h"

namespace doom
{
	class Scene;

	namespace resource
	{
		template <typename T>
		class ObjectPool;
	}

	class DOOM_API Entity : public DObject, public FrameDirtyChecker
	{
		friend class Scene;
		template <typename T>
		friend class resource::ObjectPool;
	
		struct Deleter
		{
			void operator()(Entity* entity) const
			{
				if (IsValid(entity) == true)
				{
					delete entity;
				}
			}
		};

	public:

		enum eEntityMobility
		{
			Static,
			Dynamic
		};

		enum eEntityFlags : UINT32
		{
			OcculuderStatic = 1,
			OcculudeeStatic = 1 << 1
		};

		


	private:
		
		SIZE_T mEntityID;
		

		

		std::string mEntityName;
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };

		//TODO : Every Entity has Transform Component, Just put Transform Component as member variable
	

		UINT32 mLayerIndex;
	

		Entity* mParent = nullptr;
		std::vector<Entity*> mChilds;

		std::unordered_map<SIZE_T, std::vector<Component*>> mComponents;

		/// <summary>
		/// Plain component (not core component ) is stored at this variable
		/// </summary>
		std::vector<std::unique_ptr<PlainComponent, Component::Deleter>> mPlainComponents;

		Transform mTransform;

		/// <summary>
		/// Core component is stored at this variable
		/// </summary>
		std::vector<std::unique_ptr<ServerComponent, Component::Deleter>> mServerComponents;


		void InitializeComponent(Component* const newComponent);

		template<typename T>
		constexpr static bool IsServerComponent()
		{
			return std::is_base_of_v<ServerComponent, T>;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		void _AddComponentAndInitialize(T* const newComponent) noexcept
		{
			D_ASSERT(newComponent != nullptr);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			if constexpr (Entity::IsServerComponent<T>() == true)
			{
				mServerComponents.emplace_back(newComponent);
			}
			else
			{
				mPlainComponents.emplace_back(newComponent);
			}

			mComponents[newComponent->TYPE_ID()].push_back(newComponent);


			InitializeComponent(static_cast<Component*>(newComponent));
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="component"></param>
		/// <returns></returns>
		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		T* _AddComponent(Args... args) noexcept
		{
			static_assert(std::is_same_v<T, doom::Transform> == false);

			T* newComponent = CreateDObject<T>(std::forward<Args>(args)...);
			D_ASSERT(newComponent != nullptr);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			_AddComponentAndInitialize(newComponent);
			

			return newComponent;

		}

		template<typename T>
		bool _DestroyComponent(std::unique_ptr<T, Component::Deleter>& component)
		{
// 			for (auto& serverComponents : mServerComponents)
// 			{
// 				auto removedComponent = component.get();
// 				if (serverComponents.get() != component.get())
// 				{
// 					serverComponents->OnComponentDettachedToOwnerEntity(removedComponent);
// 				}
// 			}
// 
// 			for (auto& plainComponent : mPlainComponents)
// 			{
// 				auto removedComponent = component.get();
// 				if (plainComponent.get() != component.get())
// 				{
// 					plainComponent->OnComponentDettachedToOwnerEntity(removedComponent);
// 				}
// 			}

			if (doom::IsValid(static_cast<doom::DObject*>(component.get())) == true)
			{
				component->OnDestroy_Internal();
				component->OnDestroy();
				component.reset();
			}

		
			return true;
		}

		/// <summary>
		/// only called through Destructor
		/// </summary>
		void ClearComponents();

		void InitEntity() ;
		void UpdateEntity();
		void OnEndOfFramePlainComponentsAndEntity();

		void FixedUpdate_PlainComponent();
		void Update_PlainComponent();
		void EndOfFrame_PlainComponent();

		
	public:

		eEntityMobility mEntityMobility{ eEntityMobility::Dynamic };
		UINT32 mEntityFlag{ eEntityFlags::OcculuderStatic | eEntityFlags::OcculudeeStatic };

		/// <summary>
		/// Entity Constructor should be called through Scene class
		///  To Protect User create entity not thourgh Scene class
		/// </summary>
		Entity(SIZE_T entityID, Entity* parent);

		/// <summary>
		/// Entity destructor should be called through Entity::Destory function
		/// To Protect User call delete entity not thourgh Scene or Entity class
		/// </summary>
		~Entity();

		Entity(const Entity& newEntity) = delete;
		Entity(Entity&&) noexcept = delete;

		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity&&) noexcept = delete;


		static void CopyEntity(const Entity& fromCopyedEnitty, Entity& toCopyedEntity);


		template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		T* AddComponent(Args... args) noexcept
		{
			return _AddComponent<T>(std::forward<Args>(args)...);
		}

		/* THIS function can make mistake, Don't make this function(passing argumnet)
		template<typename T, typename... arguments>
		constexpr std::enable_if_t<std::is_base_of_v<Component, T>, T&> AddComponent(arguments&&... a) noexcept
		{
			return _AddComponent<T>(new T(std::forward<arguments>(a)...));
		}
		*/
		
		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] T* GetComponent() // never return unique_ptr reference, just return pointer
		{
			static_assert(std::is_abstract_v<T> == false, "You can call GetComponent only with not abstrct class");

			T* returnedComponent = nullptr;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				returnedComponent = &mTransform;
			}
			else
			{
				const std::vector<Component*>& targetComponents = mComponents[TYPE_ID_HASH_CODE(T)];
				if(targetComponents.empty() == false)
				{
					returnedComponent = static_cast<T*>(targetComponents[0]);
					D_ASSERT(dynamic_cast<T*>(targetComponents[0]) != nullptr);
				}
			}

			if(returnedComponent != nullptr)
			{
				D_ASSERT(IsValid(returnedComponent));
			}

			return returnedComponent;
		}

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] const T* GetComponent() const // never return unique_ptr reference, just return pointer
		{
			static_assert(std::is_abstract_v<T> == false, "You can call GetComponent only with not abstrct class");

			T* returnedComponent = nullptr;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				returnedComponent = &mTransform;
			}
			else
			{
				const std::vector<Component*>& targetComponents = mComponents[TYPE_ID_HASH_CODE(T)];
				if (targetComponents.empty() == false)
				{
					returnedComponent = static_cast<T*>(targetComponents[0]);
					D_ASSERT(dynamic_cast<T*>(targetComponents[0]) != nullptr);
				}
			}

			if (returnedComponent != nullptr)
			{
				D_ASSERT(IsValid(returnedComponent));
			}

			return returnedComponent;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] std::vector<T*> GetComponents()
		{
			static_assert(std::is_abstract_v<T> == false, "You can call GetComponent only with not abstrct class");

			std::vector<T*> components;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				components.push_back(&mTransform);
			}
			else
			{
				const std::vector<Component*>& targetComponents = mComponents[TYPE_ID_HASH_CODE(T)];
				if (targetComponents.empty() == false)
				{
					components.reserve(targetComponents.size());
					for(Component* comp : targetComponents)
					{
						components.push_back(static_cast<T*>(comp));
						D_ASSERT(dynamic_cast<T*>(comp) != nullptr);
					}
				}
			}

			for (size_t i = 0; i < components.size(); i++)
			{
				D_ASSERT(IsValid(components[i]));  // This will be removed from release build
			}

		


			return components;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] std::vector<const T*> GetComponents() const
		{
			static_assert(std::is_abstract_v<T> == false, "You can call GetComponent only with not abstrct class");

			std::vector<const T*> components;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				components.push_back(&mTransform);
			}
			else
			{
				const std::vector<Component*>& targetComponents = mComponents[TYPE_ID_HASH_CODE(T)];
				if (targetComponents.empty() == false)
				{
					components.reserve(targetComponents.size());
					for (Component* comp : targetComponents)
					{
						components.push_back(static_cast<T*>(comp));
						D_ASSERT(dynamic_cast<T*>(comp) != nullptr);
					}
				}
			}

			for (size_t i = 0; i < components.size(); i++)
			{
				D_ASSERT(IsValid(components[i]));  // This will be removed from release build
			}




			return components;
		}



		/*
		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T">if there is removed component</typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		bool RemoveComponent()
		{
			static_assert(!std::is_same_v<T, Transform>);

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (SIZE_T i = 0; i < mServerComponents.size(); i++)
				{
					if(mServerComponents[i])
					{
						T* componentPtr = dynamic_cast<T*>(mServerComponents[i].get());
						if (componentPtr != nullptr)
						{//Check is sub_class of Component
							_DestroyComponent(mServerComponents[i]);

							std::vector_swap_popback(mServerComponents, i);
							return true;
						}
					}
				}
			}
			else
			{// when component is plainComponent
				for (SIZE_T i = 0; i < mPlainComponents.size(); i++)
				{
					if(mPlainComponents[i])
					{
						T* componentPtr = dynamic_cast<T*>(mPlainComponents[i].get());
						if (componentPtr != nullptr)
						{//Check is sub_class of Component
							_DestroyComponent(mServerComponents[i]);

							std::vector_swap_popback(mPlainComponents, i);
							return true;
						}
					}
				}
			}
		
			

			return false;
		}
		*/

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		bool RemoveComponents()
		{
			static_assert(std::is_abstract_v<T> == false, "You can call RemoveComponents only with not abstrct class");

			static_assert(!std::is_same_v<T, Transform>);

			bool isRemoveSuccess{ false };


			const std::vector<Component*>& targetComponents = mComponents[TYPE_ID_HASH_CODE(T)];
			if (targetComponents.empty() == false)
			{
				targetComponents.clear();
			}

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (SIZE_T i = 0; i < mServerComponents.size(); i++)
				{
					if(mServerComponents[i])
					{
						T* componentPtr = dynamic_cast<T*>(mServerComponents[i].get());
						if (componentPtr != nullptr)
						{//Check is sub_class of Component
							_DestroyComponent(mServerComponents[i]);

							std::vector_swap_popback(mServerComponents, i);
							--i;

							isRemoveSuccess = true;
						}
					}
				}
			}
			else
			{// when component is plainComponent
				for (SIZE_T i = 0; i < mPlainComponents.size(); i++)
				{
					if(mPlainComponents[i])
					{
						T* componentPtr = dynamic_cast<T*>(mPlainComponents[i].get());
						if (componentPtr != nullptr)
						{//Check is sub_class of Component
							_DestroyComponent(mServerComponents[i]);

							std::vector_swap_popback(mPlainComponents, i);
							--i;

							isRemoveSuccess = true;
						}
					}
				}
			}

		
			return isRemoveSuccess;
		}

		
		void Destroy();

		//Event
		void OnSpawned(){}
		void OnDestroyed() {}

		void OnActivated();
		void OnDeActivated() {}

		void OnPreUpdate() {}
		void OnPostUpdate() {}

		[[nodiscard]] std::string_view GetEntityName() const;
		void SetEntityName(const std::string& entityName);

		[[nodiscard]] FORCE_INLINE Transform* GetTransform()
		{
			return &mTransform;
		}
		[[nodiscard]] FORCE_INLINE const Transform* GetTransform() const
		{
			return &mTransform;
		}

		void SetLayerIndex(UINT32 layerIndex);
		[[nodiscard]] FORCE_INLINE UINT32 GetLayerIndex() const
		{
			return mLayerIndex;
		}

		FORCE_INLINE eEntityMobility GetEntityMobility() const
		{
			return mEntityMobility;
		}
		FORCE_INLINE void SetEntityMobility(eEntityMobility entityMobility)
		{
			mEntityMobility = entityMobility;
		}
		FORCE_INLINE UINT32 GetEntityFlag() const
		{	
			return mEntityFlag;
		}
		FORCE_INLINE void SetEntityFlag(eEntityFlags flag)
		{
			mEntityFlag |= flag;
		}
		FORCE_INLINE void ClearEntityFlag()
		{
			mEntityFlag &= 0;
		}
	};


}

