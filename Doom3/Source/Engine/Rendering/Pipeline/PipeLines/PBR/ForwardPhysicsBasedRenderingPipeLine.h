#pragma once

#include <Core.h>

#include "../DefaultGraphcisPipeLine.h"

#include "ForwardPhysicsBasedRenderingPipeLine.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS ForwardPhysicsBasedRenderingPipeLine : public DefaultGraphcisPipeLine
		{
			GENERATE_BODY()

		private:

		public:

			ForwardPhysicsBasedRenderingPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			virtual void Initialize() final;
			virtual void LateInitialize() final;

			virtual void PreRender() final;
			virtual void Render() final;
			virtual void PostRender() final;

			virtual eGraphicsPipeLineType GetGraphicsPipeLineType() const override;
		};
	}
}

