#pragma once

#include <array>

#include <Core.h>

#include <StaticContainer/StaticContainer.h>
#include <Entity.h>
#include "../Core/Scene/Layer.h"
#include <Rendering/Camera.h>




namespace dooms
{
	class Renderer;
	class Camera;
	
	
	template <>
	class DOOM_API StaticContainer<Renderer> : public DObject, public ISingleton<StaticContainer<Renderer>>
	{
		DOBJECT_CLASS_BODY(StaticContainer<Renderer>)
		DOBJECT_CLASS_BASE_CHAIN(DObject)

		using this_type = typename StaticContainer<Renderer>;

	private:

		inline static UINT32 mWorkingRendererListIndex = 0;
		inline static std::array<std::array<std::array<std::vector<Renderer*>, MAX_LAYER_COUNT>, 2>, MAX_CAMERA_COUNT> mRenderersInLayer{};
		
	protected:

		

	

	public:

		/// <summary>
		/// Component constructor should be called before StaticIterator constructor
		/// </summary>
		StaticContainer() = default;
		virtual ~StaticContainer() = default;
		StaticContainer(const StaticContainer&) = default;
		StaticContainer& operator=(const StaticContainer&) = default;
		StaticContainer(StaticContainer&&) noexcept = default;
		StaticContainer& operator=(StaticContainer&&) noexcept = default;

		void AddRendererToStaticContainer(Renderer* const renderer);
		void RemoveRendererToStaticContainer(const Renderer* const renderer);
		virtual void OnEntityLayerChanged(Renderer* const renderer);

		NO_DISCARD std::vector<Renderer*>& GetWorkingRendererInLayer(const size_t cameraIndex, const size_t layerIndex);
		NO_DISCARD std::vector<Renderer*>& GetSortingRendererInLayer(const size_t cameraIndex, const size_t layerIndex);

		static void ChangeWorkingIndexRenderers();
	};

	using RendererComponentStaticIterator = StaticContainer<Renderer>;
}

