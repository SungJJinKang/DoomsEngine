#pragma once

#include <Core.h>

#include "../DefaultGraphcisPipeLine.h"
#include "DeferredRenderingDrawer.h"

#include "DeferredRenderingPipeLine.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS DeferredRenderingPipeLine : public DefaultGraphcisPipeLine
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			DeferredRenderingDrawer mDeferredRenderingDrawer;

			void CameraRender(dooms::Camera* const targetCamera, const size_t cameraIndex) override;

		public:

			DeferredRenderingPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			virtual void Initialize() final;
			virtual void LateInitialize() final;

			virtual void PreRender() final;
			virtual void Render() final;
			virtual void PostRender() final;

			virtual eGraphicsPipeLineType GetGraphicsPipeLineType() const override;
			GraphicsPipeLineCamera* CreateGraphicsPipeLineCamera() const override;
		};
	}
}

