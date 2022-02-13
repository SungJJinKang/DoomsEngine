#pragma once

#include <Core.h>

#include "../DefaultGraphcisPipeLine.h"

namespace dooms
{
	namespace graphics
	{
		class D_CLASS DeferredRenderingPipeLine : public DefaultGraphcisPipeLine
		{

		private:

			D_PROPERTY()
			DeferredRenderingDrawer mDeferredRenderingDrawer;

			void PreRenderRenderer();
			void RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex);
			void RenderCamera(dooms::Camera* const targetCamera, const size_t cameraIndex);

		public:

			DeferredRenderingPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			virtual void Initialize() final;
			virtual void LateInitialize() final;

			virtual void PreRender() final;
			virtual void Render() final;
			virtual void PostRender() final;

		};
	}
}

