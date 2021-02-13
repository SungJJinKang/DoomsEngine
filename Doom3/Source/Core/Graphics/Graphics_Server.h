#pragma once
#include "Graphics_Core.h"
#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"

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

		private:

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			
			static inline GLFWwindow* Window{};
			static inline int SCREEN_WIDTH{};
			static inline int SCREEN_HEIGHT{};
			static inline bool Is_MULTI_SAMPLE{};
				
			static void OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);
		public:

			static int GetScreenWidth();
			static int GetScreenHeight();

		};
	}
}

