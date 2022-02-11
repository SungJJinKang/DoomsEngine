#pragma once

#include <Core.h>
#include <Graphics/Graphics_Core.h>
#include "../RenderingDebuggerModule.h"
#include <Simple_SingleTon/Singleton.h>

#include "OverDrawVisualization.reflection.h"
namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
	}

	namespace graphics
	{
		class Material;
		class FrameBuffer;
		class PicktureInPickture;

		class D_CLASS OverDrawVisualization : public RenderingDebuggerModule, public ISingleton<OverDrawVisualization>
		{
			GENERATE_BODY()

		private:

			bool bmIsOverDrawVisualizationInitialized{ false };
			dooms::graphics::Material* mOverDrawVisualizationObjectDrawMaterial{ nullptr };
			dooms::graphics::FrameBuffer* mOverDrawVisualizationFrameBuffer{ nullptr };
			dooms::graphics::PicktureInPickture* OverDrawVisualizationPIP{ nullptr };

			void SetOverDrawVisualizationRenderingState(const bool isSet);
			void ShowOverDrawVisualizationPIP(const bool isPIPDrawed);

		public:

			void Initialize() override;
			void PreRender() override;
			void Render() override;
			void PostRender() override;
			const char* GetRenderingDebuggerModuleName() override;
		};
	}
}

