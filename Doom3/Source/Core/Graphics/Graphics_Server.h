#pragma once
#include "Graphics_Core.h"

#include "../Game/IGameFlow.h"

#include <vector>
#include <memory>
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"

#include "FrameBuffer/FrameBuffer.h"
#include "FrameBuffer/utility/PicktureInPickture.h"

#include "Material.h"
#include "DebugGraphics.h"
#include "Acceleration/CullDistance/CullDistance.h"


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
			
			static inline GLFWwindow* Window{};
			static inline math::Vector<2, int> ScreenSize{};
			/// <summary>
			/// ScreenSize Width / ScreenSize Height
			/// </summary>
			static inline float ScreenRatio{};
			static inline unsigned int MultiSamplingNum;

			std::unique_ptr<culling::EveryCulling> mCullingSystem;
			//CullDistance mCullDistance{};

#ifdef DEBUG_MODE
			DebugGraphics mDebugGraphics{};
#endif

			eRenderingMode mCurrentRenderingMode{ eRenderingMode::ForwardRendering };
			
			/// <summary>
			/// Gbuffer drawer material.
			/// this will be used in Quad Mesh
			/// </summary>
			Material mGbufferDrawerMaterial{};
			/// <summary>
			/// Default Gbuffer Writer material
			/// </summary>
			Material mGbufferWriterMaterial{};
			std::shared_ptr<Mesh> mQuadMesh{ };

			/// <summary>
			/// Pips will drawed before gbuffer screen mesh
			/// </summary>
			std::vector<std::shared_ptr<PicktureInPickture>> mAutoDrawedPIPs{};
			void DrawPIPs();

			void InitGLFW();

			void InitFrameBufferForDeferredRendering();
			void DeferredRendering();

			void RenderObject(doom::Camera* const camera);
			void RenderObjects();

			void DoCullJob();

			void PreUpdateEntityBlocks();


			static void OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);
		public:

			Graphics_Server();
			~Graphics_Server();

			bool GetIsGLFWInitialized();

			static int GetScreenWidth();
			static int GetScreenHeight();
			static math::Vector2 GetScreenSize();
			static float GetScreenRatio();
			
			const FrameBuffer& GetGBuffer() const;
			FrameBuffer& GetGBuffer();

			void SetRenderingMode(eRenderingMode renderingMode);

			void AddAutoDrawedPIPs(const std::shared_ptr<PicktureInPickture>& pip);
		};
	}
}

