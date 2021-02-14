#pragma once

#include <vector>
#include "../Core/Core.h"
#include "../Core/Component.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_erase.h"

namespace doom
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
	class ComponentStaticIterater //Never inherit Component
	{
		using this_type = typename ComponentStaticIterater<T>;
	
	private:

		static inline std::vector<T*> mComponents{};

		/// <summary>
		/// why don't use iterator
		/// iterator can be invalidated when vector's size is over capacity
		/// </summary>
		size_t mComponentStaticIndex;

	protected:
		
		constexpr virtual void AddComponentToStaticContainer()
		{
			this_type::mComponents.push_back(reinterpret_cast<T*>(this));
			this->mComponentStaticIndex = this_type::mComponents.size() - 1;
		}

		virtual void RemoveComponentToStaticContainer()
		{
			typename std::vector<T*>::iterator swapedElementIter = std::vector_swap_erase(this_type::mComponents, this->mComponentStaticIndex);
			if (swapedElementIter != this_type::mComponents.end())
			{
				(*swapedElementIter)->mComponentStaticIndex = this->mComponentStaticIndex;
			}
		}

		size_t GetComponentStaticIndex()
		{
			return this->mComponentStaticIndex;
		}

		size_t GetComponentStaticCount()
		{
			return this_type::mComponents.size();
		}
	protected:

		

		constexpr ComponentStaticIterater()
		{
			this->AddComponentToStaticContainer();
		}

		virtual ~ComponentStaticIterater()
		{
			this->RemoveComponentToStaticContainer();
		}

	public:

		
		[[nodiscard]] static constexpr std::pair<T**, size_t> GetAllComponents()
		{
			return std::make_pair(this_type::mComponents.data(), this_type::mComponents.size());
		}

	
	};

}