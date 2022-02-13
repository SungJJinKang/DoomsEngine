#pragma once

#include <Core.h>
#include <future>

#include <Simple_SingleTon/Singleton.h>

#include "GraphicsPipeLine.reflection.h"
namespace dooms
{
	class Camera;
	namespace graphics
	{
		class Graphics_Server;
		class DeferredRenderingDrawer;

		class D_CLASS GraphicsPipeLine : public DObject, public ISingleton<GraphicsPipeLine>
		{
			GENERATE_BODY()

		protected:

			dooms::graphics::Graphics_Server& mGraphicsServer;
			
		public:

			GraphicsPipeLine() = delete;
			GraphicsPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			virtual void Initialize();
			virtual void LateInitialize();

			virtual void PreRender() = 0;
			virtual void Render() = 0;
			virtual void PostRender() = 0;

		};
	}
}

