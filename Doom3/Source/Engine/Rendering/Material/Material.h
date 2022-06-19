#pragma once
#include <array>

#include <Graphics/Graphics_Core.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "eUniformLocation.h"
#include "eTextureBindingPoint.h"

#include <Misc/eStatus.h>

#include "Material.reflection.h"
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
		class RenderingTextureViewProxy;
		class RenderingMaterialProxy;

		class DOOM_API D_CLASS Material : public DObject
		{
			GENERATE_BODY()
			
		private:
			
			static UINT64 BOUND_SHADER_ID[GRAPHICS_PIPELINE_STAGE_COUNT];
			static UINT64 BOUND_INPUT_LAYOUT_ID;

			RenderingMaterialProxy* MaterialProxy{ nullptr };

			std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderAsset;

			void OnSetPendingKill() override;
			
		public:

			void CreateRenderingMaterialProxy();
			void CreateRenderingMaterialProxyIfNotCreated();
			void DestroyRenderingMaterialProxy();
			RenderingMaterialProxy* GetRenderingMaterialProxy() const;
			bool IsRenderingMaterialProxyCreated() const;

			Material() = default;
			Material(dooms::asset::ShaderAsset* const ShaderAsset);
			Material(dooms::asset::ShaderAsset* const ShaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType);
			Material(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& ShaderAssets);
			
			virtual ~Material() override;

			Material(const Material&) = delete;
			Material& operator=(const Material&) noexcept = delete;

			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;
			
			//void SetShaderAsset(dooms::asset::ShaderAsset* const ShaderAsset);
			void SetShaderAsset(dooms::asset::ShaderAsset* const ShaderAsset);
			void SetShaderAsset(dooms::asset::ShaderAsset* const ShaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType);
			void SetShaderAsset(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& ShaderAssets);

			void AddTexture
			(
				const UINT32 BindingPoint, 
				const dooms::asset::TextureAsset* const TextureAsset,
				const graphics::GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage = graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER
			);

			void BindMaterial() const;
			void UnBindMaterial() const;
			
			FORCE_INLINE dooms::asset::ShaderAsset* GetShaderAsset(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
			{
				return ShaderAsset[shaderType];
			}

			FORCE_INLINE const dooms::asset::ShaderAsset* GetShaderAsset(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType) const
			{
				return ShaderAsset[shaderType];
			}
		};
	}
}

