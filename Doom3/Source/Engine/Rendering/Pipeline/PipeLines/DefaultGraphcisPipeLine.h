#pragma once

#include <Core.h>

#include "../GraphicsPipeLine.h"

#include "../RenderingCullingManager.h"
#include "Rendering/RenderingDebugger/RenderingDebugger.h"

#include "DefaultGraphcisPipeLine.reflection.h"
namespace dooms
{
	class Renderer;
	namespace graphics
	{
		class Material;

		class D_CLASS DefaultGraphcisPipeLine : public GraphicsPipeLine
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			graphics::Material* DepthOnlyMaterial;

		protected:

			void PreRenderRenderer();
			std::future<void> PushFrontToBackSortJobToJobSystem(dooms::Camera* const targetCamera, const UINT32 cameraIndex);

			void DrawRenderersWithDepthOnly(dooms::Camera* const targetCamera, const size_t cameraIndex) const;
			void DrawRenderers(dooms::Camera* const targetCamera, const size_t cameraIndex) const;
			void ConditionalDrawRenderers
			(
				dooms::Camera* const targetCamera, 
				const size_t cameraIndex, 
				const std::function<bool(const dooms::Renderer* const)>& ConditionFunc
			) const;
			void DrawBatchedRenderers() const;
			virtual void CameraRender(dooms::Camera* const targetCamera, const size_t cameraIndex)  = 0;

			graphics::Material* GetDepthOnlyMaterial() const;

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
