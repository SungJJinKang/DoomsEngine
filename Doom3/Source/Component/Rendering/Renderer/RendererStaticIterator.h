#pragma once

#include <array>

#include <StaticContainer/StaticContainer.h>
#include <Entity.h>
#include "../Core/Scene/Layer.h"
#include <Graphics/Graphics_Core.h>
#include <Rendering/Camera.h>




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

		inline static UINT32 mWorkingRendererListIndex = 0;
		inline static std::array<std::array<std::array<std::vector<Renderer*>, MAX_LAYER_COUNT>, 2>, MAX_CAMERA_COUNT> mRenderersInLayer{};
		
	protected:

		void AddRendererToStaticContainer();
		void RemoveRendererToStaticContainer();

		/// <summary>
		/// Component constructor should be called before StaticIterator constructor
		/// </summary>
		StaticContainer();
		virtual ~StaticContainer();

		StaticContainer(const StaticContainer&);
		StaticContainer& operator=(const StaticContainer&);
		StaticContainer(StaticContainer&&) noexcept;
		StaticContainer& operator=(StaticContainer&&) noexcept;

		virtual void OnEntityLayerChanged(Entity& entity);

	public:

		[[nodiscard]] static std::vector<Renderer*>& GetWorkingRendererInLayer(const size_t cameraIndex, const size_t layerIndex);
		[[nodiscard]] static std::vector<Renderer*>& GetSortingRendererInLayer(const size_t cameraIndex, const size_t layerIndex);

		static void ChangeWorkingIndexRenderers();
	};

	using RendererComponentStaticIterator = StaticContainer<Renderer>;
}

