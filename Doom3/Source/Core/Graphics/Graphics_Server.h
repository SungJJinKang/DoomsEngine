#pragma once

#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"

#include "FrameBuffer/FrameBuffer.h"
#include "DeferredRenderingDrawer.h"
#include "Buffer/UniformBufferObjectManager.h"
#include "LightManager.h"
#include "PictureInPicture/PIPManager.h"
#include "DeferredRenderingDrawer.h"

#include "DebugGraphics.h"




struct GLFWwindow;

namespace culling
{
	class EveryCulling;
}


namespace doom
{
	namespace userinput
	{
		class UserInput_Server;
	}

	class GameCore;
	class Renderer;
	class Transform;
	class Mesh;
	class Camera;

	namespace graphics
	{
		class Graphics_Server : public IGameFlow, public ISingleton<Graphics_Server>
		{
			enum class eRenderingMode
			{
				ForwardRendering,
				DeferredRendering
			};

		private:

			DeferredRenderingDrawer mDeferredRenderingDrawer;
			
			//CullDistance mCullDistance{};

#ifdef DEBUG_MODE
			DebugGraphics mDebugGraphics{};
#endif

			eRenderingMode mCurrentRenderingMode{ eRenderingMode::ForwardRendering };
			
			void DeferredRendering();

			void RenderObject(doom::Camera* const targetCamera, const size_t cameraIndex);
		
			void DoCullJob();

			void PreUpdateEntityBlocks();


			
		public:

			std::unique_ptr<culling::EveryCulling> mCullingSystem;

			virtual void Init() final;
			virtual void LateInit() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			void Renderder_InitComponent();
			void Renderder_UpdateComponent();
			void Renderder_OnEndOfFrameComponent();
			void Renderder_DrawRenderingBoundingBox();

			RenderingDebugger mRenderingDebugger;
			UniformBufferObjectManager mUniformBufferObjectManager;
			graphics::LightManager mLightManager;
			graphics::PIPManager mPIPManager;

			Graphics_Server();
			~Graphics_Server();

			
			void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

