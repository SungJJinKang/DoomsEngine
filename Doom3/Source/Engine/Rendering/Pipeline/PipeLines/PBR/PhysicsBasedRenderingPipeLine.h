#pragma once

#include <Core.h>

#include "../DefaultGraphcisPipeLine.h"

namespace dooms
{
	namespace graphics
	{
		class D_CLASS PhysicsBasedRenderingPipeLine : public DefaultGraphcisPipeLine
		{

		private:

		public:

			PhysicsBasedRenderingPipeLine(dooms::graphics::Graphics_Server& graphicsServer);

			virtual void Initialize() final;
			virtual void LateInitialize() final;

			virtual void PreRender() final;
			virtual void Render() final;
			virtual void PostRender() final;


		};
	}
}

