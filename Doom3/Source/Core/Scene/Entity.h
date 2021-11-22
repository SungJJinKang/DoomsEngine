#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <functional>
#include <utility>
#include <typeinfo>

#include "Scene.h"
#include "../Core.h"
#include "../../Component/Core/Component.h"
#include "../../Component/Core/ServerComponent.h"
#include "../../Component/Core/PlainComponent.h"
#include "../../Component/Core/ComponentHelper.h"

#include "../../Component/Transform.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"
#include "../Game/FrameDirtyChecker.h"

#include "Entity.reflection.h"
namespace dooms
{
	class Scene;

	namespace resource
	{
		template <typename T>
		class ObjectPool;
	}

	class Entity;
	template <>
	inline dooms::Entity* CreateDObject<dooms::Entity>()
	{
		return dooms::Scene::GetSingleton()->CreateNewEntity();
	}

	class DOOM_API D_CLASS Entity : public DObject, public FrameDirtyChecker
	{
		GENERATE_BODY()
		
		

		friend class Scene;
		template <typename T>
		friend class resource::ObjectPool;

	public:

		enum D_ENUM eEntityMobility
		{
			Static,
			Dynamic
		};

		enum D_ENUM eEntityFlags : UINT32
		{
			OcculuderStatic = 1,
			OcculudeeStatic = 1 << 1
		};

		


	private:

		D_PROPERTY()
		size_t mEntityID;
		
		D_PROPERTY()
		std::string mEntityName;

		D_PROPERTY()
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };

		//TODO : Every Entity has Transform Component, Just put Transform Component as member variable
	

		D_PROPERTY()
		UINT32 mLayerIndex{0};
	

		D_PROPERTY()
		Entity* mParent = nullptr;

		D_PROPERTY()
		std::vector<Entity*> mChilds;

		//D_PROPERTY()
		std::unordered_map<size_t, std::vector<Component*>> mComponents;
		
		std::vector<std::unique_ptr<PlainComponent, Component::Deleter>> mPlainComponents;

		D_PROPERTY()
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

			if constexpr (dooms::IsServerComponentStatic<T>() == true)
			{
				mServerComponents.emplace_back(newComponent);
			}
			else
			{
				mPlainComponents.emplace_back(newComponent);
			}

			//TODO : BaseChain Ÿ�� ���鼭 ��� ������� typeid���ٰ� �� ��������.
			mComponents[static_cast<size_t>(newComponent->GetTypeHashVlue())].push_back(newComponent);


			InitializeComponent(static_cast<Component*>(newComponent));
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="component"></param>
		/// <returns></returns>
		template<typename T, typename... Args>
		T* _AddComponent(Args&&... args) noexcept
		{
			static_assert(std::is_abstract_v<T> == false, "You can call GetComponent only with not abstrct class");
			static_assert(std::is_same_v<T, dooms::Transform> == false);
			static_assert(std::is_base_of_v<Component, T> == true);

			T* newComponent = CreateDObject<T>(std::forward<Args>(args)...);

			D_ASSERT(IsValid(newComponent) == true);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			_AddComponentAndInitialize(newComponent);
			

			return newComponent;

		}


		bool _DestroyComponentCallBack(Component* const component)
		{
			if (dooms::IsValid(component) == true)
			{
				component->OnDestroy_Internal();
				component->OnDestroy();
			}
			
			return true;
		}
		
		bool _RemoveComponent(Component* const component, const size_t index)
		{
			D_ASSERT(IsValid(component));
			D_ASSERT(component->IsChildOf<Transform>() == false);

			bool isRemoveSuccess{ false };
			
			std::vector<Component*>& targetComponents = mComponents[static_cast<size_t>(component->GetTypeHashVlue())];
			for(std::ptrdiff_t i = targetComponents.size() - 1; i >= 0 ; i--)
			{
				if(targetComponents[i] == component)
				{
					targetComponents.erase(targetComponents.begin() + i);
					isRemoveSuccess = true;
					break;
				}
			}

			D_ASSERT(isRemoveSuccess == true);
			isRemoveSuccess = false;

			std::unique_ptr<Component> removedComp = nullptr;

			if (IsServerComponent(component) == true)
			{// when component is ServerComponent
				D_ASSERT(mServerComponents.size() > 0);
				D_ASSERT(mServerComponents[index]);
				D_ASSERT(mServerComponents[index].get() == component);
				
				removedComp = std::unique_ptr<Component>(mServerComponents[index].release());
				mServerComponents.erase(mServerComponents.begin() + index);
				_DestroyComponentCallBack(removedComp.get());

				isRemoveSuccess = true;
			}
			else
			{// when component is plainComponent
				D_ASSERT(mPlainComponents.size() > 0);
				D_ASSERT(mPlainComponents[index]);
				D_ASSERT(mPlainComponents[index].get() == component);

				removedComp = std::unique_ptr<Component>(mPlainComponents[index].release());
				mPlainComponents.erase(mPlainComponents.begin() + index);
				_DestroyComponentCallBack(removedComp.get());

				isRemoveSuccess = true;
			}

			D_ASSERT(removedComp);
			D_ASSERT(IsValid(removedComp.get()) == true);
			D_ASSERT(isRemoveSuccess == true);

			removedComp.reset();


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

		D_PROPERTY()
		eEntityMobility mEntityMobility{ eEntityMobility::Dynamic };
		D_PROPERTY()
		UINT32 mEntityFlag{ eEntityFlags::OcculuderStatic | eEntityFlags::OcculudeeStatic };

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

		Entity(const Entity& newEntity) = delete;
		Entity(Entity&&) noexcept = delete;

		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity&&) noexcept = delete;


		static void CopyEntity(const Entity& fromCopyedEnitty, Entity& toCopyedEntity);


		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) noexcept
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
		NO_DISCARD T* GetComponent() const // never return unique_ptr reference, just return pointer
		{
			static_assert(std::is_base_of_v<Component, T> == true);
			static_assert(std::is_same_v<T, PlainComponent> == false);
			static_assert(std::is_same_v<T, ServerComponent> == false);


			T* returnedComponent = nullptr;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				returnedComponent = &mTransform;
			}
			else
			{
				auto iter = mComponents.find(static_cast<size_t>(T::TYPE_FULL_NAME_HASH_VALUE));
				if (iter != mComponents.end())
				{
					const std::vector<Component*>& targetComponents = iter->second;
					if (targetComponents.empty() == false)
					{
						returnedComponent = CastToUnchecked<T*>(targetComponents[0]);
					}
				}
			}

			if(returnedComponent == nullptr)
			{
				if (IsServerComponentStatic<T>() == true)
				{
					for (auto& serverComponent : mServerComponents)
					{
						D_ASSERT(serverComponent);
						if (serverComponent->IsChildOf<T>())
						{
							returnedComponent = CastToUnchecked<T*>(serverComponent.get());
						}
					}
				}
				else
				{
					for (auto& plainComponent : mPlainComponents)
					{
						D_ASSERT(plainComponent);
						if (plainComponent->IsChildOf<T>())
						{
							returnedComponent = CastToUnchecked<T*>(plainComponent.get());
						}
					}
				}
			}
		
			return returnedComponent;
		}
		

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		NO_DISCARD std::vector<T*> GetComponents() const
		{
			static_assert(std::is_base_of_v<Component, T> == true);
			static_assert(std::is_same_v<T, PlainComponent> == false);
			static_assert(std::is_same_v<T, ServerComponent> == false);

			std::vector<T*> components;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				components.push_back(&mTransform);
			}
			else
			{
				if (IsServerComponentStatic<T>() == true)
				{
					for (auto& serverComponent : mServerComponents)
					{
						D_ASSERT(serverComponent);
						if (serverComponent->IsChildOf<T>())
						{
							components.push_back(CastToUnchecked<T*>(serverComponent.get()));
						}
					}
				}
				else
				{
					for (auto& plainComponent : mPlainComponents)
					{
						D_ASSERT(plainComponent);
						if (plainComponent->IsChildOf<T>())
						{
							components.push_back(CastToUnchecked<T*>(plainComponent.get()));
						}
					}
				}
			}
			
			return components;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		bool RemoveComponents()
		{
			static_assert(std::is_same_v<T, Transform> == false);
			static_assert(std::is_base_of_v<Component, T> == true);
			static_assert(std::is_same_v<T, PlainComponent> == false);
			static_assert(std::is_same_v<T, ServerComponent> == false);

			bool isAnyComponentRemoved{ false };

			
			if (IsServerComponentStatic<T>() == true)
			{
				for (std::ptrdiff_t i = 0; i < mServerComponents.size(); i++)
				{
					if (mServerComponents[i]->IsChildOf<T>())
					{
						_RemoveComponent(mServerComponents[i], i);
						i--;
						isAnyComponentRemoved = true;
					}
				}
			}
			else
			{
				for (std::ptrdiff_t i = 0; i < mPlainComponents.size(); i++)
				{
					if (mPlainComponents[i]->IsChildOf<T>())
					{
						_RemoveComponent(mPlainComponents[i], i);
						i--;
						isAnyComponentRemoved = true;
					}
				}
			}

			
			return isAnyComponentRemoved;
		}

		FORCE_INLINE const std::vector<std::unique_ptr<PlainComponent, Component::Deleter>>& GetAllPlainComponents() const
		{
			return mPlainComponents;
		}
		FORCE_INLINE const std::vector<std::unique_ptr<ServerComponent, Component::Deleter>>& GetAllServerComponents() const
		{
			return mServerComponents;
		}
		
		void Destroy();

		//Event
		void OnSpawned(){}
		void OnDestroyed() {}

		void OnActivated();
		void OnDeActivated() {}

		void OnPreUpdate() {}
		void OnPostUpdate() {}


		D_FUNCTION()
		NO_DISCARD std::string_view GetEntityName() const;

		D_FUNCTION()
		void SetEntityName(const std::string& entityName);


		D_FUNCTION()
		NO_DISCARD FORCE_INLINE Transform* GetTransform()
		{
			return &mTransform;
		}

		D_FUNCTION()
		NO_DISCARD FORCE_INLINE const Transform* GetTransform() const
		{
			return &mTransform;
		}


		D_FUNCTION()
		void SetLayerIndex(UINT32 layerIndex);

		D_FUNCTION()
		NO_DISCARD FORCE_INLINE UINT32 GetLayerIndex() const
		{
			return mLayerIndex;
		}

		D_FUNCTION()
		FORCE_INLINE eEntityMobility GetEntityMobility() const
		{
			return mEntityMobility;
		}

		D_FUNCTION()
		FORCE_INLINE void SetEntityMobility(eEntityMobility entityMobility)
		{
			mEntityMobility = entityMobility;
		}

		D_FUNCTION()
		FORCE_INLINE UINT32 GetEntityFlag() const
		{	
			return mEntityFlag;
		}

		D_FUNCTION()
		FORCE_INLINE void SetEntityFlag(eEntityFlags flag)
		{
			mEntityFlag |= flag;
		}

		D_FUNCTION()
		FORCE_INLINE void ClearEntityFlag()
		{
			mEntityFlag &= 0;
		}
	};

	
	
}

