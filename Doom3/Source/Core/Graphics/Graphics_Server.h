#pragma once

#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"

#include "GraphicsAPI/GraphicsAPIManager.h"

#include "FrameBuffer/FrameBuffer.h"
#include "DeferredRenderingDrawer.h"
#include "Buffer/UniformBufferObjectManager.h"
#include "LightManager.h"
#include "PictureInPicture/PIPManager.h"

#include "DebugGraphics/DebugDrawer.h"

#include <Rendering/Renderer/RendererStaticIterator.h>
#include <EngineGUI/EngineGUIServer.h>

#include "utility/BVH/BVH.h"

#include "DebugGraphics/RenderingDebugger.h"


#define RENDERER_BVH_MAX_NODE_COUNT 3000

struct GLFWwindow;

namespace culling
{
	class EveryCulling;
}

#include "Graphics_Server.reflection.h"
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

#ifdef DEBUG_DRAWER
			void DebugGraphics();
			D_PROPERTY()
			DebugDrawer mDebugGraphics {};
#endif

			size_t mCullingCameraCount;

			D_PROPERTY()
			GraphicsAPIManager mGraphicsAPIManager{};

			RendererComponentStaticIterator mRendererStaticContainer{};
			D_PROPERTY()
			DeferredRenderingDrawer mDeferredRenderingDrawer{};
			
			//CullDistance mCullDistance{};
			void PreRenderRenderer();
			void UpdateCameraIndexInCullingSystemOfCameraComponent();
			void UpdateSortedEntityInfoListInCullingSystem();
			
			void InitializeGraphicsAPI();

			void PreRender();
			void Render();
			void ProfilingCullingSystem();
			void PostRender();

			void UpdateOverDrawVisualization(dooms::Camera* const targetCamera, const size_t cameraIndex);

			void RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex);
		
			void PreCullJob();
			void CameraCullJob(dooms::Camera* const camera);
			//void PreUpdateEntityBlocks();
			
			
		public:

			BVHAABB3D mRendererColliderBVH{ RENDERER_BVH_MAX_NODE_COUNT };

			std::unique_ptr<culling::EveryCulling> mCullingSystem;

			
			virtual void Init() final;
			virtual void LateInit() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			
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

			
			//void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

