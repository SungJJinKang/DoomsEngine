#pragma once

#include <cassert>
#include <vector>
#include "../vector_erase_move_lastelement/vector_swap_popback.h"

#include <Core.h>

#define INVALID_STATIC_CONTAINER_INDEX (size_t)(-1)

namespace dooms
{
	/// <summary>
	/// Why I made ComponentIterater
	/// 
	/// Think if you wanna Iterate over specific component of spawned entity
	/// You should do like this
	/// for(auto& entity : GetAllSpawnedEntity)
	/// {
	///		Renderer* renderer = entity.GetComponent<Renderer>();
	///		renderer->Draw();
	/// }
	/// 
	/// So Slow!!!!!!!!!!!!!
	/// 
	/// So We Do like this
	/// for(auto& renderer : RendererStaticInterator)
	/// {
	///		renderer->Draw();
	/// }
	/// 
	/// This is super fast
	/// Why this is fast?
	/// 1. This way don't use GetComponent, Call is decreased
	/// 
	/// 2. StaticIterator's elements is stored in vector, Vector is random access container.
	///	   This will make iterating much faster ( random access, Cache hit!!!! )
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T>
	class DOOM_API D_CLASS StaticContainer //Never inherit Component
	{

	private:

		static inline std::vector<T*> mElements{};

		/// <summary>
		/// why don't use iterator.
		/// iterator can be invalidated when vector's size is over capacity
		/// </summary>
		size_t mComponentStaticIndex;

		void AddToStaticContainer()
		{
			StaticContainer<T>::mElements.push_back(static_cast<T*>(this));
			mComponentStaticIndex = StaticContainer<T>::mElements.size() - 1;
		}

		void ReplaceFromStaticContainer(const size_t index, T* const object)
		{
			assert(index != INVALID_STATIC_CONTAINER_INDEX && object != nullptr);

			if (index != INVALID_STATIC_CONTAINER_INDEX && object != nullptr)
			{
				StaticContainer<T>::mElements[index]->mComponentStaticIndex = INVALID_STATIC_CONTAINER_INDEX;

				StaticContainer<T>::mElements[index] = object;
				StaticContainer<T>::mElements[index]->mComponentStaticIndex = index;
			}
		}

		void RemoveFromStaticContainer(const size_t index)
		{
			if (index != INVALID_STATIC_CONTAINER_INDEX)
			{

				if (StaticContainer<T>::mElements.size() - 1 == index)
				{
					StaticContainer<T>::mElements.back()->mComponentStaticIndex = INVALID_STATIC_CONTAINER_INDEX;

					StaticContainer<T>::mElements.pop_back();
				}
				else
				{
					ReplaceFromStaticContainer(index, StaticContainer<T>::mElements.back());
					StaticContainer<T>::mElements.pop_back();
				}
			}
			
		}

		void RemoveFromStaticContainer()
		{
			RemoveFromStaticContainer(mComponentStaticIndex);
		}

	protected:
		
		
		size_t GetStaticElementIndex() const
		{
			return mComponentStaticIndex;
		}

		static size_t GetStaticElementCount()
		{
			return StaticContainer<T>::mElements.size();
		}
		
	public:

		StaticContainer()
			: mComponentStaticIndex(INVALID_STATIC_CONTAINER_INDEX)
		{
			AddToStaticContainer();
		}

		virtual ~StaticContainer()
		{
			RemoveFromStaticContainer();
		}

		StaticContainer(const StaticContainer& container)
			: mComponentStaticIndex(INVALID_STATIC_CONTAINER_INDEX)
		{
			AddToStaticContainer();
		}
		StaticContainer(StaticContainer&& container) noexcept
			: mComponentStaticIndex(INVALID_STATIC_CONTAINER_INDEX)
		{
			ReplaceFromStaticContainer(container.mComponentStaticIndex, this);
			container.mComponentStaticIndex = INVALID_STATIC_CONTAINER_INDEX;
		}
		StaticContainer& operator=(const StaticContainer& container)
		{
			AddToStaticContainer();
			return *this;
		}
		StaticContainer& operator=(StaticContainer&& container) noexcept
		{
			RemoveFromStaticContainer();
			ReplaceFromStaticContainer(container.mComponentStaticIndex, this);
			container.mComponentStaticIndex = INVALID_STATIC_CONTAINER_INDEX;
			return *this;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		NO_DISCARD static const std::vector<T*>& GetAllStaticComponents()
		{
			return StaticContainer<T>::mElements;
		}

		NO_DISCARD static T* GetComponentWithIndex(unsigned int index)
		{
			assert(index >= 0);
			if (index < StaticContainer<T>::mElements.size())
			{
				return StaticContainer<T>::mElements[index];
			}
			else
			{
				return nullptr;
			}
		}

		/// <summary>
		/// return foremost component except for passed argumnet component
		/// </summary>
		/// <param name="excludedObject"></param>
		/// <returns></returns>
		NO_DISCARD static T* GetForemostComponentWithHint(T* excludedObject)
		{
			T* formostComponent = nullptr;

			for (unsigned int i = 0; i < StaticContainer<T>::mElements.size(); i++)
			{
				if (StaticContainer<T>::mElements[i] != excludedObject)
				{
					formostComponent = StaticContainer<T>::mElements[i];
					break;
				}
			}
			
			return formostComponent;
		}

		static void ClearContainer()
		{
			StaticContainer<T>::mElements.~vector();
		}
	
	};

}