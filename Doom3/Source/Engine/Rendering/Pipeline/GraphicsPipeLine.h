#pragma once

#include <Core.h>
#include <future>

#include <SingleTon/Singleton.h>
#include "PipeLines/eGraphicsPipeLineType.h"

#include "GraphicsPipeLine.reflection.h"
namespace dooms
{
	class Camera;
	namespace graphics
	{
		class Graphics_Server;
		class DeferredRenderingDrawer;
		class GraphicsPipeLineCamera;

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

			virtual eGraphicsPipeLineType GetGraphicsPipeLineType() const = 0;
			virtual GraphicsPipeLineCamera* CreateGraphicsPipeLineCamera() const = 0;
		};
	}
}

