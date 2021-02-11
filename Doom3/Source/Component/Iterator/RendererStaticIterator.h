#pragma once

#include <array>
#include <utility>

#include "ComponentStaticIterater.h"
#include "../Core/Scene/Layer.h"





namespace doom
{
	namespace graphics
	{
		class SceneGraphics;
	}
	class Renderer;

	
	template <>
	class ComponentStaticIterater<Renderer>
	{
		friend class graphics::SceneGraphics;

		using this_type = typename ComponentStaticIterater<Renderer>;
		using layer_container_type = typename std::vector<Renderer*>;
		using container_type = typename std::array<layer_container_type, MAX_LAYER_COUNT>;
		
	private:

		Renderer* mRenderer_ptr;

		static inline container_type mComponentsInLayer{};
		
	protected:

		void AddRendererToStaticContainer();
		void RemoveRendererToStaticContainer();

		/// <summary>
		/// Component constructor should be called before StaticIterator constructor
		/// </summary>
		ComponentStaticIterater();
		~ComponentStaticIterater();

		virtual void OnEntityLayerChanged(Entity& entity);

	public:

		[[nodiscard]] static std::pair<Renderer**, size_t> GetAllComponentsWithLayerIndex(unsigned int layerIndex);

	};

	using RendererComponentStaticIterator = ComponentStaticIterater<Renderer>;
}

