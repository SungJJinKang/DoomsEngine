#pragma once

#include <Core.h>
#include <future>

#include <Simple_SingleTon/Singleton.h>
#include "RenderingCullingManager.h"
#include "DeferredRenderingDrawer.h"
#include "Graphics/RenderingDebugger/RenderingDebugger.h"

#include "GraphicsPipeLine.reflection.h"
namespace dooms
{
	class Camera;
	namespace graphics
	{
		class Graphics_Server;
		class DeferredRenderingDrawer;

		class D_CLASS GraphicsPipeLine : public DObject, public ISingleton<GraphicsPipeLine>
		{
			GENERATE_BODY()

		private:

			dooms::graphics::Graphics_Server& mGraphicsServer;


			void PreRenderRenderer();			
			void RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex);
			void RenderCamera(dooms::Camera* const targetCamera, const size_t cameraIndex);

			std::future<void> PushFrontToBackSortJobToJobSystem(dooms::Camera* const targetCamera, const UINT32 cameraIndex);

		public:

			D_PROPERTY()
			RenderingCullingManager mRenderingCullingManager;

			D_PROPERTY()
			DeferredRenderingDrawer mDeferredRenderingDrawer;

			D_PROPERTY()
			RenderingDebugger mRenderingDebugger;

			GraphicsPipeLine() = delete;
			GraphicsPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			void Initialize();
			void LateInitialize();

			void PreRender();
			void Render();
			void PostRender();

		};
	}
}

