#pragma once

#include <Graphics/Graphics_Core.h>

#include "../Game/IGameFlow.h"
#include <Simple_SingleTon/Singleton.h>
#include "Buffer/UniformBufferObject/UniformBufferObjectManager.h"
#include <Rendering/Light/LightManager.h>
#include <Rendering/PictureInPicture/PIPManager.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include "Misc/AccelerationContainer/BVH/BVH.h"
#include <Rendering/Pipeline/GraphicsPipeLine.h>
#include <Rendering/Batch/BatchRenderingManager.h>

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
			RendererComponentStaticIterator mRendererStaticContainer;

			void GenerateGraphicsPipeLine();

			void PreRenders();
			void Renders();
			void PostRenders();
			
		public:

			D_PROPERTY()
			BVHAABB3D mRendererColliderBVH;

			D_PROPERTY()
			GraphicsPipeLine* mGraphicsPipeLine;

			D_PROPERTY()
			UniformBufferObjectManager mUniformBufferObjectManager;

			D_PROPERTY()
			BatchRenderingManager mBatchRenderingManager;

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
			void PostSceneInit() override;


			//void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

