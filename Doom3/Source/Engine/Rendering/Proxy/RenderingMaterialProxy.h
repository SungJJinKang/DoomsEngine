#pragma once

#include <Core.h>

#include <array>

#include "RenderingProxy.h"
#include <Graphics/Graphics_Core.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "../Buffer/BufferID.h"
#include "../Buffer/UniformBufferObject/UniformBufferObjectView.h"

namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
		class TextureAsset;
	}

	namespace graphics
	{
		class UniformBufferObject;
		class TextureView;

		class RenderingMaterialProxy : public RenderingProxy
		{

		public:

			FORCE_INLINE UniformBufferObjectView* GetUniformBufferObjectViewFromUBOIndex(const size_t uboIndex)
			{
				UniformBufferObjectView* uboView = nullptr;
				D_ASSERT(uboIndex < mTargetUniformBufferObjectViews.size());

				if (uboIndex < mTargetUniformBufferObjectViews.size())
				{
					uboView = mTargetUniformBufferObjectViews.data() + uboIndex;
				}

				return uboView;
			}
			UniformBufferObjectView* GetUniformBufferObjectViewFromUBOName(const char* const uniformBufferObjectName);

			void BindMaterial();
			void UnBindMaterial();

			void CreateMaterialObjectIfNotExist();
			void DestroyMaterialObjectIfExist();
			void DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType);

		private:

			static UINT64 BOUND_SHADER_ID[GRAPHICS_PIPELINE_STAGE_COUNT];
			static UINT64 BOUND_INPUT_LAYOUT_ID;

			/// <summary>
			/// Used for OpenGL
			///	If Current Graphics API is DirectX, this varaible set to random uuid ( this is for overlap check )
			/// </summary>
			BufferID ProgramIDForOpenGL;

			/// <summary>
			/// Only used for DirectX
			/// </summary>
			std::array<BufferID, GRAPHICS_PIPELINE_STAGE_COUNT> PipeLineShaderView;
			std::vector<const TextureView*> mTargetTextures;
			std::vector<UniformBufferObjectView> TargetUniformBufferObjectViews;

			bool AttachShaderToMaterial(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType);
			UniformBufferObjectView* AddUniformBufferObjectView(UniformBufferObject* const ubo, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage);

		};
	}
}

