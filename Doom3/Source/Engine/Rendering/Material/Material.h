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
		class TextureView;

		class DOOM_API D_CLASS Material : public DObject
		{
			GENERATE_BODY()
			
		private:
			
			static UINT64 BOUND_SHADER_ID[GRAPHICS_PIPELINE_STAGE_COUNT];
			static UINT64 BOUND_INPUT_LAYOUT_ID;

			D_PROPERTY()
			eStatus mMaterialStatus;

			std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderAsset;

			void OnSetPendingKill() override;
			
		public:

			Material();
			Material(dooms::asset::ShaderAsset* const shaderAsset);
			Material(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType);
			Material(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderAssets);

			/**
			 * \brief Create program object for OPENGL
			 */
			void CreateMaterialObjectIfNotExist();
			void DestroyMaterialObjectIfExist();
			void DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType);

			virtual ~Material();

			Material(const Material&) = delete;
			Material& operator=(const Material&) noexcept = delete;

			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;
			
			//void SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset);
			void SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset);
			void SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType);
			void SetShaderAsset(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderAssets);

			bool IsHasAnyValidShaderObject() const;

			void AddTexture(const UINT32 bindingPoint, const TextureView* const textureView);
			void AddTexture(const UINT32 bindingPoint, const dooms::asset::TextureAsset* const textureAsset);
			void AddTextures(const std::vector<const TextureView*>& textures);

			void BindMaterial() const;
			void UnBindMaterial() const;

			bool IsMaterialCreated() const;

			FORCE_INLINE dooms::asset::ShaderAsset* GetShaderAsset(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
			{
				return ShaderAsset[shaderType];
			}

			FORCE_INLINE const dooms::asset::ShaderAsset* GetShaderAsset(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType) const
			{
				return ShaderAsset[shaderType];
			}
			
			UINT64 GetMaterialHashValue() const;
			static bool Equal(const Material* const lhs, const Material* const rhs);
			
			const TextureView* GetTextureView(const size_t index) const;
			size_t GetTextureViewCount() const;
		};
	}
}

