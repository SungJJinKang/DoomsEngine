#pragma once
#include "Graphics_Core.h"
#include "../../Helper/Singleton.h"
#include "../Game/GameFlow.h"
#include "Buffer/UniformBufferObjectManager.h"

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
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			static inline GLFWwindow* Window{};
			static inline int SCREEN_WIDTH{};
			static inline int SCREEN_HEIGHT{};
			static inline bool Is_MULTI_SAMPLE{};
				

		public:
		};
	}
}

