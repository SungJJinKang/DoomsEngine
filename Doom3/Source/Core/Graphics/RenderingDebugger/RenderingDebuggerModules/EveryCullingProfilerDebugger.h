#pragma once

#include "RenderingDebuggerModule.h"

#include "EveryCullingProfilerDebugger.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS EveryCullingProfilerDebugger : public RenderingDebuggerModule
		{
			GENERATE_BODY()

		private:

		public:

			void Initialize() override;
			void PreRender() override;
			void Render() override;
			void PostRender() override;

		};
	}
}

