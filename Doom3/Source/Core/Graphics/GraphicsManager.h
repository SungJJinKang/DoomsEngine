#pragma once
#include "Graphics_Core.h"
#include "../../Helper/Singleton.h"
#include "../Game/GameFlow.h"
#include "Buffer/UniformBufferObjectManager.h"
#include "GraphicsAPI.h"
#include "SceneGraphics.h"

struct GLFWwindow;

namespace doom
{
	class GameCore;
	namespace graphics
	{
		class GraphicsManager : public GameFlow, public ISingleton<GraphicsManager>
		{

			friend class GameCore;
			friend class UniformBufferObjectManager;
			friend class RenderBuffer;
		private:
			virtual void Init() final;
			virtual void Update() final
			{
				GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

				auto sceneGraphics = SceneGraphics::GetSingleton();

				sceneGraphics->mUniformBufferObjectManager.Update_Internal();
				sceneGraphics->mUniformBufferObjectManager.Update();

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				// -------------------------------------------------------------------------------
				glfwSwapBuffers(GraphicsManager::Window);
				glfwPollEvents();

			}
			virtual void OnEndOfFrame() final
			{
				auto sceneGraphics = SceneGraphics::GetSingleton();

				sceneGraphics->mUniformBufferObjectManager.OnEndOfFrame_Internal();
				sceneGraphics->mUniformBufferObjectManager.OnEndOfFrame();
			}


			static inline GLFWwindow* Window{};
			static inline int SCREEN_WIDTH{};
			static inline int SCREEN_HEIGHT{};
			static inline bool Is_MULTI_SAMPLE{};
				

		public:
		};
	}
}

