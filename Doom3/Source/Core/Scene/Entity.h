#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <functional>
#include <utility>

#include "../Core.h"
#include "../../Component/Core/Component.h"
#include "../../Component/Core/ServerComponent.h"

#include "../../Component/Transform.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"
#include "../Game/IGameFlow.h"
#include "../Game/FrameDirtyChecker.h"

#include "../API/UUID.h"

namespace doom
{
	class Scene;

	namespace resource
	{
		template <typename T>
		class ObjectPool;
	}

	class Entity : public DObject, public FrameDirtyChecker
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

		enum eEntityFlags : unsigned int
		{
			OcculuderStatic = 1,
			OcculudeeStatic = 1 << 1
		};

		


	private:
		
		size_t mEntityID;
		

		

		std::string mEntityName;
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };

		//TODO : Every Entity has Transform Component, Just put Transform Component as member variable
	

		unsigned int mLayerIndex;
		/// <summary>
		/// https://isocpp.org/wiki/faq/pointers-to-members#memfnptr-vs-fnptr
		/// The type of this function is different depending on whether it is an ordinary function or a non-static member function of some class:
		// 
		// 	Its type is ��int(*)(char, float)�� if an ordinary function
		// 	Its type is ��int(Fred::*)(char, float)�� if a non - static member function of class Fred
		// 	
		//	Read here ---> Note : if it��s a static member function of class Fred, its type is the same as if it were an ordinary function : ��int(*)(char, float)��.
		//
		//	This callback variable can store only static function of class or global function
		//  Call back function should have this function type ( void(Entity&) )
		/// 
		/// </summary>
		std::vector<void(*)(Entity&)> mLayerIndexChangedCallback{};

		Entity* mParent;
		std::vector<Entity*> mChilds{};

		
		/// <summary>
		/// Plain component (not core component ) is stored at this variable
		/// </summary>
		std::vector<std::unique_ptr<Component, Component::Deleter>> mPlainComponents;

		Transform mTransform;

		/// <summary>
		/// Core component is stored at this variable
		/// </summary>
		std::vector<std::unique_ptr<ServerComponent, Component::Deleter>> mServerComponents;


		FORCE_INLINE void InitializeComponent(Component* const newComponent)
		{
			newComponent->SetOwnerDObject(this);

			newComponent->InitComponent_Internal(this);
			newComponent->InitComponent();

			newComponent->OnActivated_Internal();
			newComponent->OnActivated();
		}

		template<typename T>
		constexpr static bool IsServerComponent()
		{
			return std::is_base_of_v<ServerComponent, T>;
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
			T* newComponent = CreateDObject<T>(std::forward<Args>(args)...);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			if constexpr (Entity::IsServerComponent<T>() == true)
			{
				mServerComponents.emplace_back(newComponent);
			}
			else
			{
				mPlainComponents.emplace_back(newComponent);
			}
		

			InitializeComponent(static_cast<Component*>(newComponent));


			//Why need this?
			//Too slow
// 			for (auto& serverComponents : mServerComponents)
// 			{
// 				if (serverComponents.get() != newComponent_com)
// 				{
// 					serverComponents->OnComponentAttachedToOwnerEntity(newComponent_com);
// 				}
// 			}
// 
// 			for (auto& plainComponent : mPlainComponents)
// 			{
// 				if (plainComponent.get() != newComponent_com)
// 				{
// 					plainComponent->OnComponentAttachedToOwnerEntity(newComponent_com);
// 				}
// 			}
			

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
		unsigned int mEntityFlag{ eEntityFlags::OcculuderStatic | eEntityFlags::OcculudeeStatic };

		/// <summary>
		/// Entity Constructor should be called through Scene class
		///  To Protect User create entity not thourgh Scene class
		/// </summary>
		Entity(size_t entityID, Entity* parent);

		/// <summary>
		/// Entity destructor should be called through Entity::Destory function
		/// To Protect User call delete entity not thourgh Scene or Entity class
		/// </summary>
		~Entity();

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


		// TODO : cached component can be destroyed component 
		mutable Component* mComponentPtrCache;

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] T* GetComponent() // never return unique_ptr reference, just return pointer
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

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (auto& ServerComponent : mServerComponents)
				{
					T* componentPtr = dynamic_cast<T*>(ServerComponent.get());
					if (componentPtr != nullptr)
					{
						mComponentPtrCache = ServerComponent.get();
						return componentPtr;
					}
				}
			}
			else
			{// when component is plainComponent
				for (auto& plainComponent : mPlainComponents)
				{
					T* componentPtr = dynamic_cast<T*>(plainComponent.get());
					if (componentPtr != nullptr)
					{
						mComponentPtrCache = plainComponent.get();
						return componentPtr;
					}
				}
			}
			

			return nullptr;
		}

		/// <summary>
		/// GetComponent is expesive, so cache it
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] const T* GetComponent() const // never return unique_ptr reference, just return pointer
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

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (auto& ServerComponent : mServerComponents)
				{
					T* componentPtr = dynamic_cast<T*>(ServerComponent.get());
					if (componentPtr != nullptr)
					{
						mComponentPtrCache = ServerComponent.get();
						return componentPtr;
					}
				}
			}
			else
			{// when component is plainComponent
				for (auto& plainComponent : mPlainComponents)
				{
					T* componentPtr = dynamic_cast<T*>(plainComponent.get());
					if (componentPtr != nullptr)
					{
						mComponentPtrCache = plainComponent.get();
						return componentPtr;
					}
				}
			}


			return nullptr;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] std::vector<T*> GetComponents()
		{
			std::vector<T*> components;

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (auto& ServerComponent : mServerComponents)
				{
					T* componentPtr = dynamic_cast<T*>(ServerComponent.get());
					if (componentPtr != nullptr)
					{
						components.push_back(componentPtr);
					}
				}
			}
			else
			{// when component is plain component
				for (auto& plainComponent : mPlainComponents)
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

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] std::vector<const T*> GetComponents() const
		{
			std::vector<const T*> components;

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (auto& ServerComponent : mServerComponents)
				{
					T* componentPtr = dynamic_cast<T*>(ServerComponent.get());
					if (componentPtr != nullptr)
					{
						components.push_back(componentPtr);
					}
				}
			}
			else
			{// when component is plain component
				for (auto& plainComponent : mPlainComponents)
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
		bool RemoveComponent()
		{
			static_assert(!std::is_same_v<T, Transform>);

			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (size_t i = 0; i < mServerComponents.size(); i++)
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
			else
			{// when component is plainComponent
				for (size_t i = 0; i < mPlainComponents.size(); i++)
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
		
			

			return false;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		bool RemoveComponents()
		{
			static_assert(!std::is_same_v<T, Transform>);

			bool isRemoveSuccess{ false };
			if constexpr (Entity::IsServerComponent<T>() == true)
			{// when component is ServerComponent
				for (size_t i = 0; i < mServerComponents.size(); i++)
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
			else
			{// when component is plainComponent
				for (size_t i = 0; i < mPlainComponents.size(); i++)
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

		void SetLayerIndex(unsigned int layerIndex);
		[[nodiscard]] FORCE_INLINE unsigned int GetLayerIndex() const
		{
			return mLayerIndex;
		}

		void AddLayerChangedCallback(void(*callback_ptr)(Entity&));
		void RemoveLayerChangedCallback(void(*callback_ptr)(Entity&));

		FORCE_INLINE eEntityMobility GetEntityMobility() const
		{
			return mEntityMobility;
		}
		FORCE_INLINE void SetEntityMobility(eEntityMobility entityMobility)
		{
			mEntityMobility = entityMobility;
		}
		FORCE_INLINE unsigned int GetEntityFlag() const
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

