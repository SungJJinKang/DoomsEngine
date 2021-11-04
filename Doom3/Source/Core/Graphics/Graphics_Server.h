#pragma once

#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"

#include "FrameBuffer/FrameBuffer.h"
#include "DeferredRenderingDrawer.h"
#include "Buffer/UniformBufferObjectManager.h"
#include "LightManager.h"
#include "PictureInPicture/PIPManager.h"

#include "DebugGraphics/DebugDrawer.h"




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
		class DOOM_API Graphics_Server : public IGameFlow, public ISingleton<Graphics_Server>
		{
			DOBJECT_CLASS_BODY(Graphics_Server, doom::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(IGameFlow)

			enum class eRenderingMode
			{
				ForwardRendering,
				DeferredRendering
			};

		private:

			DeferredRenderingDrawer mDeferredRenderingDrawer{};
			
			//CullDistance mCullDistance{};

#ifdef DEBUG_DRAWER
			DebugDrawer mDebugGraphics{};
#endif

			eRenderingMode mCurrentRenderingMode{ eRenderingMode::ForwardRendering };
			
			void Render();

			void UpdateOverDrawVisualization(doom::Camera* const targetCamera, const size_t cameraIndex);

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

#ifdef DEBUG_DRAWER
			RenderingDebugger mRenderingDebugger{};
#endif
			UniformBufferObjectManager mUniformBufferObjectManager{};
			graphics::LightManager mLightManager{};
			graphics::PIPManager mPIPManager{};

			Graphics_Server();
			~Graphics_Server();

			
			void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

