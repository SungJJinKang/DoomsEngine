#pragma once

#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"

#include "FrameBuffer/FrameBuffer.h"
#include "DeferredRenderingDrawer.h"
#include "Buffer/UniformBufferObjectManager.h"
#include "LightManager.h"
#include "PictureInPicture/PIPManager.h"

#include "DebugGraphics/DebugDrawer.h"

#include <Rendering/Renderer/RendererStaticIterator.h>
#include <EngineGUI/EngineGUIServer.h>


#include "Graphics_Server.reflection.h"
struct GLFWwindow;

namespace culling
{
	class EveryCulling;
}

namespace dooms
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

	D_NAMESPACE(dooms::graphics)
	namespace graphics
	{
		class DOOM_API D_CLASS Graphics_Server : public IGameFlow, public ISingleton<Graphics_Server>
		{
			GENERATE_BODY()
			

			enum class D_ENUM eRenderingMode
			{
				ForwardRendering,
				DeferredRendering
			};

		private:
			
			RendererComponentStaticIterator mRendererStaticContainer{};
			D_PROPERTY()
			DeferredRenderingDrawer mDeferredRenderingDrawer{};
			
			//CullDistance mCullDistance{};

#ifdef DEBUG_DRAWER
			D_PROPERTY()
			DebugDrawer mDebugGraphics{};
#endif

			eRenderingMode mCurrentRenderingMode{ eRenderingMode::ForwardRendering };
			
			void PreRender();
			void Render();
			void PostRender();

			void UpdateOverDrawVisualization(dooms::Camera* const targetCamera, const size_t cameraIndex);

			void RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex);
		
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
			D_PROPERTY()
			RenderingDebugger mRenderingDebugger{};
#endif
			D_PROPERTY()
			UniformBufferObjectManager mUniformBufferObjectManager{};
			D_PROPERTY()
			graphics::LightManager mLightManager{};
			D_PROPERTY()
			graphics::PIPManager mPIPManager{};

			Graphics_Server();
			~Graphics_Server();

			
			void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

