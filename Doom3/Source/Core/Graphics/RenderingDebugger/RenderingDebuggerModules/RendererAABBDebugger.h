#pragma once

#include <Core.h>
#include "RenderingDebuggerModule.h"

#include "RendererAABBDebugger.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS RendererAABBDebugger : public RenderingDebuggerModule
		{
			GENERATE_BODY()

		private:

		public:

			void Initialize() override;
			void PreRender() override;
			void Render() override;
			void PostRender() override;
			const char* GetRenderingDebuggerModuleName() override;
		};
	}
}

