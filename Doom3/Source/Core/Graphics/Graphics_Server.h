#pragma once

#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"


#include "FrameBuffer/FrameBuffer.h"
#include "Buffer/UniformBufferObject/UniformBufferObjectManager.h"
#include "Light/LightManager.h"
#include <Rendering/PictureInPicture/PIPManager.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include "Misc/AccelerationContainer/BVH/BVH.h"
#include <Rendering/RenderingDebugger/RenderingDebugger.h>
#include "Pipeline/GraphicsPipeLine.h"

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
			

			

		private:
			

			D_PROPERTY()
			UINT32 mCullingCameraCount;

			D_PROPERTY()
			RendererComponentStaticIterator mRendererStaticContainer{};
			
			void PreRenders();
			void Renders();
			void PostRenders();
			
		public:

			D_PROPERTY()
			BVHAABB3D mRendererColliderBVH{ RENDERER_BVH_MAX_NODE_COUNT };

			D_PROPERTY()
			GraphicsPipeLine mGraphicsPipeLine;

			D_PROPERTY()
			UniformBufferObjectManager mUniformBufferObjectManager;

			D_PROPERTY()
			graphics::LightManager mLightManager;

			D_PROPERTY()
			graphics::PIPManager mPIPManager;
			
			bool InitializeGraphicsAPI(GraphicsAPI::eGraphicsAPIType graphicsAPIType);

			virtual void Init(const int argc, char* const* const argv) final;
			virtual void LateInit() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			

			Graphics_Server();
			~Graphics_Server();

			
			//void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

