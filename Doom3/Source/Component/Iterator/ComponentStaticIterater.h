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
		using container_type = typename std::vector<T*>;
	private:

		static inline container_type mComponents{};

		constexpr virtual void AddComponentToStaticContainer()
		{
			this_type::mComponents.push_back(reinterpret_cast<T*>(this));
		}

		virtual void RemoveComponentToStaticContainer()
		{
			auto iter = std::find(this_type::mComponents.begin(), this_type::mComponents.end(), reinterpret_cast<T*>(this));

			D_ASSERT(iter != this_type::mComponents.end());
			std::vector_swap_erase(this_type::mComponents, iter);
		}

	protected:

		constexpr ComponentStaticIterater()
		{
			this->AddComponentToStaticContainer();
		}

		~ComponentStaticIterater()
		{
			this->RemoveComponentToStaticContainer();
		}

	public:

		/// <summary>
		/// const_iterator can't call not const member function
		/// </summary>
		/// <param name="layerIndex"></param>
		/// <returns></returns>
		[[nodiscard]] static constexpr std::pair<typename container_type::iterator, typename container_type::iterator> GetIter()
		{
			return std::make_pair(this_type::mComponents.begin(), this_type::mComponents.end());
		}

	
	};

}