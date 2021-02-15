#pragma once
#include "Graphics_Core.h"

#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"

#include <vector>
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Math/LightMath_Cpp/Vector4.h"
#include "Buffer/Mesh.h"


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
		class Material;
		class Graphics_Server : public IGameFlow, public ISingleton<Graphics_Server>
		{

			friend class GameCore;
			friend class UniformBufferObjectManager;
			friend class RenderBuffer;
			friend class ::doom::userinput::UserInput_Server;

			struct DebugMesh
			{
				math::Vector4 mColor;
				Mesh mMesh;
			};

		private:

			static inline const std::string DEBUG_SHADER{ "DebugLineShader.glsl" };

			virtual void Init() final;
			virtual void LateInit() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			
			static inline GLFWwindow* Window{};
			static inline math::Vector<2, int> ScreenSize{};
			static inline bool Is_MULTI_SAMPLE{};

			std::vector<DebugMesh> mDebugMeshes{};
			unsigned int mDebugMeshCount;
				
			static void OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);
		public:

			static int GetScreenWidth();
			static int GetScreenHeight();
			static math::Vector2 GetScreenSize();
			static const math::Vector2& GetScreenSize_const();

			Material* mDebugMaterial;
			/// <summary>
			/// Draw Debug Line
			/// You should call this every frame
			/// </summary>
			/// <param name="startWorldPos"></param>
			/// <param name="endWorldPos"></param>
			/// <param name="color"></param>
			void DebugDrawLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, const math::Vector4& color);
			/// <summary>
			///	Draw Debug Sphere
			/// You should call this every frame
			/// </summary>
			/// <param name="centerWorldPos"></param>
			/// <param name="radius"></param>
			/// <param name="color"></param>
			void DebugDrawSphere(const math::Vector3& centerWorldPos, float radius, const math::Vector4& color);
		};
	}
}

