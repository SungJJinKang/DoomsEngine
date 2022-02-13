#pragma once

#include <Core.h>

#include "../GraphicsPipeLine.h"

#include "../RenderingCullingManager.h"
#include "Rendering/RenderingDebugger/RenderingDebugger.h"

#include "DefaultGraphcisPipeLine.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS DefaultGraphcisPipeLine : public GraphicsPipeLine
		{
			GENERATE_BODY()

		private:

		protected:

			void PreRenderRenderer();
			std::future<void> PushFrontToBackSortJobToJobSystem(dooms::Camera* const targetCamera, const UINT32 cameraIndex);

		public:

			D_PROPERTY()
			RenderingCullingManager mRenderingCullingManager;

			D_PROPERTY()
			RenderingDebugger mRenderingDebugger;

			DefaultGraphcisPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			void Initialize() override;
			void LateInitialize() override;
			void PreRender() override;
			void Render() override;
			void PostRender() override;
		};
	}
}
