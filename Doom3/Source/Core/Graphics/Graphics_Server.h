#pragma once
#include "Graphics_Core.h"

#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"

#include <vector>
#include <memory>
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"

#include "Buffer/Mesh.h"
#include "FrameBuffer/FrameBuffer.h"
#include "Material.h"
#include "DebugGraphics.h"

struct GLFWwindow;

namespace doom
{
	namespace userinput
	{
		class UserInput_Server;
	}

	class GameCore;
	class Renderer;
	namespace graphics
	{
		class Graphics_Server : public IGameFlow, public ISingleton<Graphics_Server>
		{

			friend class GameCore;
			friend class UniformBufferObjectManager;
			friend class RenderBuffer;
			friend class ::doom::userinput::UserInput_Server;

			

			enum class eRenderingMode
			{
				ForwardRendering,
				DeferredRendering
			};

		private:

		

			virtual void Init() final;
			virtual void LateInit() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			
			static inline GLFWwindow* Window{};
			static inline math::Vector<2, int> ScreenSize{};
			static inline unsigned int MultiSamplingNum;

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
			FrameBuffer mFrameBufferForDeferredRendering{};
			void InitFrameBufferForDeferredRendering();
			void DeferredRendering();
				
			static void OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);
		public:

			static int GetScreenWidth();
			static int GetScreenHeight();
			static math::Vector2 GetScreenSize();
			static const math::Vector2& GetScreenSize_const();
			
			const FrameBuffer& GetGBuffer() const;
			FrameBuffer& GetGBuffer();

			void SetRenderingMode(eRenderingMode renderingMode);

			
	
		};
	}
}

