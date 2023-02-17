#pragma once

#include <array>
#include <vector>

#include <Core.h>
#include <Misc/StaticContainer/StaticContainer.h>
#include "../MaxCameraCount.h"
#include <SingleTon/Singleton.h>

#include "RendererStaticIterator.reflection.h"
namespace dooms
{
	class Renderer;
	class Camera;

	struct D_ENUM RendererListSwapContainer
	{
		GENERATE_BODY_RendererListSwapContainer()

		D_PROPERTY()
		std::vector<Renderer*> mRendererList1;
		D_PROPERTY()
		std::vector<Renderer*> mRendererList2;
	};
	
	class DOOM_API D_CLASS RendererComponentStaticIterator : public DObject, public ISingleton<RendererComponentStaticIterator>
	{
		GENERATE_BODY()
	private:

		D_PROPERTY()
		UINT32 mWorkingRendererListIndex;
		D_PROPERTY()
		RendererListSwapContainer mRendererList;

	public:

		/// <summary>
		/// Component constructor should be called before StaticIterator constructor
		/// </summary>
		RendererComponentStaticIterator();
		virtual ~RendererComponentStaticIterator() = default;
		RendererComponentStaticIterator(const RendererComponentStaticIterator&) = default;
		RendererComponentStaticIterator& operator=(const RendererComponentStaticIterator&) = default;
		RendererComponentStaticIterator(RendererComponentStaticIterator&&) noexcept = default;
		RendererComponentStaticIterator& operator=(RendererComponentStaticIterator&&) noexcept = default;

		void AddRendererToStaticContainer(Renderer* const renderer);
		void RemoveRendererToStaticContainer(const Renderer* const renderer);
		virtual void OnEntityLayerChanged(Renderer* const renderer);

		NO_DISCARD std::vector<Renderer*>& GetSortedRendererInLayer();
		NO_DISCARD std::vector<Renderer*>& GetSortingRendererInLayer();

		void ChangeWorkingIndexRenderers();
	};
}

