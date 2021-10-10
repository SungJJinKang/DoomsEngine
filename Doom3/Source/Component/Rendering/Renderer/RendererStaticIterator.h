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
		
		static void CacheDistanceFromRenderersToCamera(std::vector<Renderer*>& renderersInLayer, const std::vector<Camera*>& cameras);

		//For Rendering front to back
		static void SortByDistanceToCamera(const size_t layerIndex, const size_t cameraIndex);
	
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

		[[nodiscard]] static const std::vector<Renderer*>& GetRendererInLayer(const unsigned int layerIndex);

	
		static void CacheDistanceFromRenderersToCamera(const std::vector<Camera*> cameras);
		
		static void SortByDistanceToCamera(const Camera* const camera, const size_t cameraIndex);
	};

	using RendererComponentStaticIterator = StaticContainer<Renderer>;
}

