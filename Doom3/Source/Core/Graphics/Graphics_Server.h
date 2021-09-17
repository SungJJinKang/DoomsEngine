#pragma once

#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"

#include <vector>
#include <memory>
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"

#include "FrameBuffer/FrameBuffer.h"

#include "Buffer/UniformBufferObjectManager.h"
#include "LightManager.h"
#include "PictureInPicture/PIPManager.h"

#include "Material.h"
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

			friend class GameCore;
			friend class UniformBufferObjectManager;
			friend class RenderBuffer;
			friend class ::doom::userinput::UserInput_Server;

			friend class ::doom::Transform;
			friend class ::doom::Renderer;

			enum class eRenderingMode
			{
				ForwardRendering,
				DeferredRendering
			};

		private:

			static inline int AVAILIABLE_TEXTURE_UNIT_COUNT{};

			bool bmIsGLFWInitialized{ false };

			virtual void Init() final;
			virtual void LateInit() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			void Renderder_InitComponent();
			void Renderder_UpdateComponent();
			void Renderder_OnEndOfFrameComponent();
			void Renderder_DrawRenderingBoundingBox();
			
			std::unique_ptr<culling::EveryCulling> mCullingSystem;
			//CullDistance mCullDistance{};

			DebugGraphics mDebugGraphics{};

			eRenderingMode mCurrentRenderingMode{ eRenderingMode::ForwardRendering };
			
			/// <summary>
			/// Gbuffer drawer material.
			/// this will be used in Quad Mesh
			/// </summary>
			Material mGbufferDrawerMaterial{};
		
			std::shared_ptr<Mesh> mQuadMesh{ };

			void InitGLFW();

			void InitFrameBufferForDeferredRendering();
			void DeferredRendering();

			void RenderObject(doom::Camera* const camera);
			void RenderObjects();

			void DoCullJob();

			void PreUpdateEntityBlocks();


			
		public:

			RenderingDebugger mRenderingDebugger;
			UniformBufferObjectManager mUniformBufferObjectManager;
			graphics::LightManager mLightManager;
			graphics::PIPManager mPIPManager;

			Graphics_Server();
			~Graphics_Server();

			bool GetIsGLFWInitialized();

			
			
			void SetRenderingMode(eRenderingMode renderingMode);
		};
	}
}

