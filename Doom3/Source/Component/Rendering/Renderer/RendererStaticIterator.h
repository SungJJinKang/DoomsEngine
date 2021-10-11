#pragma once

#include <array>

#include <StaticContainer/StaticContainer.h>
#include <Entity.h>
#include "../Core/Scene/Layer.h"





namespace doom
{
	class Renderer;
	class Camera;
	
	template <>
	class DOOM_API StaticContainer<Renderer>
	{
		using this_type = typename StaticContainer<Renderer>;

	private:

		Renderer* mRenderer_ptr;

		static inline std::array<std::vector<Renderer*>, MAX_LAYER_COUNT> mRenderersInLayer{};
		
	protected:

		void AddRendererToStaticContainer();
		void RemoveRendererToStaticContainer();

		/// <summary>
		/// Component constructor should be called before StaticIterator constructor
		/// </summary>
		StaticContainer();
		virtual ~StaticContainer();

		virtual void OnEntityLayerChanged(Entity& entity);

	public:

		[[nodiscard]] static std::vector<Renderer*>& GetRendererInLayer(const size_t layerIndex);

	
	};

	using RendererComponentStaticIterator = StaticContainer<Renderer>;
}

