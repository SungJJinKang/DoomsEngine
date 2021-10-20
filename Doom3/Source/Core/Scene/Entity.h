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
#include "../../Component/Core/PlainComponent.h"
#include "../../Component/Core/ComponentHelper.h"

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

		DOBJECT_CLASS_BODY(Entity, doom::eDOBJECT_ClassFlags::NonCopyable);
		DOBJECT_CLASS_BASE_CHAIN(DObject)

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

		
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		void _AddComponentAndInitialize(T* const newComponent) noexcept
		{
			D_ASSERT(IsValid(newComponent) == true);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			if constexpr (doom::IsServerComponentStatic<T>() == true)
			{
				mServerComponents.emplace_back(newComponent);
			}
			else
			{
				mPlainComponents.emplace_back(newComponent);
			}

			mComponents[newComponent->GetClassTypeID()].push_back(newComponent);


			InitializeComponent(static_cast<Component*>(newComponent));
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="component"></param>
		/// <returns></returns>
		template<typename T, typename... Args>
		T* _AddComponent(Args... args) noexcept
		{
			static_assert(std::is_abstract_v<T> == false, "You can call GetComponent only with not abstrct class");
			static_assert(std::is_same_v<T, doom::Transform> == false);
			static_assert(std::is_base_of_v<Component, T> == true);

			T* newComponent = CreateDObject<T>(std::forward<Args>(args)...);

			D_ASSERT(IsValid(newComponent) == true);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			_AddComponentAndInitialize(newComponent);
			

			return newComponent;

		}


		bool _DestroyComponentCallBack(Component* const component)
		{
			if (doom::IsValid(component) == true)
			{
				component->OnDestroy_Internal();
				component->OnDestroy();
			}
			
			return true;
		}
		
		bool _RemoveComponent(Component* const component)
		{
			D_ASSERT(IsValid(component));
			D_ASSERT(component->IsChildOf<Transform>() == false);

			bool isRemoveSuccess{ false };
			
			std::vector<Component*>& targetComponents = mComponents[component->GetClassTypeID()];
			D_ASSERT(targetComponents.size() > 0);
			for(SIZE_T i = targetComponents.size() - 1; i >= 0 ; i--)
			{
				if(targetComponents[i] == component)
				{
					targetComponents.erase(targetComponents.begin() + i);
					break;
				}
			}
			Component* removedComp = nullptr;

			if (IsServerComponent(component) == true)
			{// when component is ServerComponent
				D_ASSERT(mServerComponents.size() > 0);
				for (SIZE_T i = mServerComponents.size() - 1; i >= 0; i--)
				{
					if (mServerComponents[i] && mServerComponents[i].get() == component)
					{
						removedComp = mServerComponents[i].release();
						mServerComponents.erase(mServerComponents.begin() + i);
						_DestroyComponentCallBack(removedComp);
							

						isRemoveSuccess = true;
						break;
					}
				}
			}
			else
			{// when component is plainComponent
				D_ASSERT(mPlainComponents.size() > 0);
				for (SIZE_T i = mPlainComponents.size() - 1; i >= 0; i--)
				{
					if (mPlainComponents[i] && mPlainComponents[i].get() == component)
					{
						removedComp = mPlainComponents[i].release();
						mPlainComponents.erase(mPlainComponents.begin() + i);
						_DestroyComponentCallBack(removedComp);

						isRemoveSuccess = true;
						break;
					}
				}
			}

			D_ASSERT(IsValid(removedComp) == true);
			delete removedComp;


			return isRemoveSuccess;
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


		template<typename T, typename... Args>
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
		template<typename T>
		[[nodiscard]] T* GetComponent() const // never return unique_ptr reference, just return pointer
		{
			static_assert(std::is_base_of_v<Component, T> == true);


			T* returnedComponent = nullptr;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				returnedComponent = &mTransform;
			}
			else if (std::is_abstract_v<T> == false)
			{
				auto iter = mComponents.find(TYPE_ID_HASH_CODE(T));
				if(iter != mComponents.end())
				{
					const std::vector<Component*>& targetComponents = iter->second;
					if (targetComponents.empty() == false)
					{
						returnedComponent = CastToUnchecked<T*>(targetComponents[0]);
					}
				}
				
			}
			else
			{
				if(IsServerComponentStatic<T>() == true)
				{
					for (auto& serverComponent : mServerComponents)
					{
						if (serverComponent && serverComponent->IsChildOf<T>())
						{
							returnedComponent = CastToUnchecked<T*>(serverComponent.get());
						}
					}
				}
				else
				{
					for (auto& plainComponent : mPlainComponents)
					{
						if (plainComponent && plainComponent->IsChildOf<T>())
						{
							returnedComponent = CastToUnchecked<T*>(plainComponent.get());
						}
					}
				}
			}

			if (returnedComponent != nullptr)
			{
				D_ASSERT(IsValid(returnedComponent));
				D_ASSERT(CastTo<T*>(returnedComponent) != nullptr);
			}

			return returnedComponent;
		}
		

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		[[nodiscard]] std::vector<T*> GetComponents() const
		{
			static_assert(std::is_base_of_v<Component, T> == true);

			std::vector<T*> components;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				components.push_back(&mTransform);
			}
			else if (std::is_abstract_v<T> == false)
			{
				auto iter = mComponents.find(TYPE_ID_HASH_CODE(T));
				if (iter != mComponents.end())
				{
					const std::vector<Component*>& targetComponents = iter->second;
					if (targetComponents.empty() == false)
					{
						components.reserve(targetComponents.size());
						for (Component* comp : targetComponents)
						{
							components.push_back(static_cast<T*>(comp));
						}
					}
				}
			}
			else
			{
				if (IsServerComponentStatic<T>() == true)
				{
					for (auto& serverComponent : mServerComponents)
					{
						if (serverComponent && serverComponent->IsChildOf<T>())
						{
							components.push_back(CastToUnchecked<T*>(serverComponent.get()));
						}
					}
				}
				else
				{
					for (auto& plainComponent : mPlainComponents)
					{
						if (plainComponent && plainComponent->IsChildOf<T>())
						{
							components.push_back(CastToUnchecked<T*>(plainComponent.get()));
						}
					}
				}
			}

			for (size_t i = 0; i < components.size(); i++)
			{
				D_ASSERT(IsValid(components[i]));  // This will be removed from release build
				D_ASSERT(CastTo<T*>(components[i]) != nullptr);
			}

			
			return components;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		bool RemoveComponents()
		{
			static_assert(std::is_abstract_v<T> == false, "You can call RemoveComponents only with not abstrct class");
			static_assert(!std::is_same_v<T, Transform>);
			static_assert(std::is_base_of_v<Component, T> == true);

			bool isRemoveSuccess{ false };


			const std::vector<Component*>& targetComponents = mComponents[TYPE_ID_HASH_CODE(T)];
			if (targetComponents.empty() == false)
			{
				for(Component* targetComp : targetComponents)
				{
					_RemoveComponent(targetComp);
				}
				targetComponents.clear();

				isRemoveSuccess = true;
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

