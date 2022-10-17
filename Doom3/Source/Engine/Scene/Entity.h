#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <memory>
#include <utility>

#include "Scene.h"
#include "../Core.h"
#include <Core/Component.h>
#include <Transform.h>
#include <Misc/FrameDirtyChecker/FrameDirtyChecker.h>
#include "eEntityMobility.h"

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

	class Scene;
	class Component;
	class DOOM_API D_CLASS Entity : public DObject, public FrameDirtyChecker
	{
		GENERATE_BODY()
		
		friend class Component;

	public:

		

		enum D_ENUM eEntityFlags : UINT32
		{
			OcculuderStatic = 1,
			OcculudeeStatic = 1 << 1
		};

		


	private:

		D_PROPERTY(READONLY)
		size_t mEntityID;
		
		D_PROPERTY()
		static const inline std::string DEFAULT_ENTITY_NAME{ "Entity" };

		//TODO : Every Entity has Transform Component, Just put Transform Component as member variable
	

		D_PROPERTY()
		UINT32 mLayerIndex{0};
	

		D_PROPERTY()
		eEntityMobility mEntityMobility { eEntityMobility::Dynamic };
		D_PROPERTY(READONLY)
		UINT32 mEntityFlag { eEntityFlags::OcculuderStatic | eEntityFlags::OcculudeeStatic };

		D_PROPERTY(INVISIBLE)
		Entity* mParentEntity = nullptr;

		D_PROPERTY()
		Scene* mInvolvedScene = nullptr;

		D_PROPERTY(READONLY)
		std::vector<Entity*> mChilds;
		
		D_PROPERTY(INVISIBLE)
		std::vector<Component*> mComponents;

		D_PROPERTY(INVISIBLE)
		Transform mTransform;
		
		void OnEntityMobilityChanged() const;

		void InitializeComponent(Component* const newComponent);

		
		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		void _AddComponentAndInitialize(T* const newComponent) noexcept
		{
			D_ASSERT(IsValid(newComponent) == true);
			D_ASSERT(newComponent->bIsAddedToEntity == false);

			mComponents.emplace_back(newComponent);

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

		bool _RemoveComponent(Component* const component, const size_t index);


		/// <summary>
		/// only called through Destructor
		/// </summary>
		void ClearComponents();

	

		void FixedUpdateComponents();
		void UpdateComponents();
		void EndOfFrameComponents();

		
	public:

		D_PROPERTY()
		bool IsEnabled = true;

		Entity() = delete;
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

		void InitEntity();
		void FixedUpdateEntity();
		void UpdateEntity();
		void EndOfFrameEntity();

		void SetInvoledScene(Scene* const scene);

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
			static_assert(std::is_pointer<T>::value == false);


			const T* returnedComponent = nullptr;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				returnedComponent = &mTransform;
			}

			if(returnedComponent == nullptr)
			{
				for (Component* component : mComponents)
				{
					D_ASSERT(IsValid(component) == true);
					if (component->IsChildOf<T>())
					{
						returnedComponent = CastToUnchecked<T*>(component);
					}
				}
			}
		
			return returnedComponent;
		}

		template<typename T>
		NO_DISCARD T* GetComponent() // never return unique_ptr reference, just return pointer
		{
			static_assert(std::is_base_of_v<Component, T> == true);
			static_assert(std::is_pointer<T>::value == false);


			T* returnedComponent = nullptr;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				returnedComponent = &mTransform;
			}
			else
			{
				for (Component* component : mComponents)
				{
					D_ASSERT(IsValid(component) == true);
					if (component->IsChildOf<T>())
					{
						returnedComponent = CastToUnchecked<T*>(component);
					}
				}
			}
			

			return returnedComponent;
		}

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		NO_DISCARD std::vector<T*> GetComponents() const
		{
			static_assert(std::is_base_of_v<Component, T> == true);

			std::vector<T*> components;

			if constexpr (std::is_same_v<T, Transform> == true)
			{
				components.push_back(&mTransform);
			}
			else
			{
				for (Component* component : mComponents)
				{
					D_ASSERT(IsValid(component) == true);
					if (component->IsChildOf<T>())
					{
						components.push_back(CastToUnchecked<T*>(component));
					}
				}
			}
			
			return components;
		}

		bool RemoveComponent(Component* const component);

		template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
		bool RemoveComponents()
		{
			static_assert(std::is_same_v<T, Transform> == false);
			static_assert(std::is_base_of_v<Component, T> == true);

			bool isAnyComponentRemoved{ false };

			
			for (std::ptrdiff_t i = 0; i < mComponents.size(); i++)
			{
				if (mComponents[i]->IsChildOf<T>())
				{
					_RemoveComponent(mComponents[i], i);
					i--;
					isAnyComponentRemoved = true;
				}
			}

			
			return isAnyComponentRemoved;
		}

		const std::vector<Component*>& GetAllComponents() const;

		void Destroy();
		
		void OnDestroyed();
		virtual void OnSetPendingKill() override;
		void OnActivated();

		D_FUNCTION()
		void DestroyEntitySelf();

		D_FUNCTION()
		NO_DISCARD const std::string& GetEntityName() const;

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
		
		FORCE_INLINE eEntityMobility GetEntityMobility() const
		{
			return mEntityMobility;
		}
		void SetEntityMobility(eEntityMobility entityMobility);

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

		D_FUNCTION(INVISIBLE)
		FORCE_INLINE void ClearEntityFlag()
		{
			mEntityFlag = 0;
		}

		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) override;
	};

	
	
}

