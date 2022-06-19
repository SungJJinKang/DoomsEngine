#pragma once

#include <string>
#include <array>

#include "Asset.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Rendering/Buffer/BufferID.h>
#include <Rendering/Shader/ShaderTextData.h>
#include <Rendering/Shader/eShaderCompileStatus.h>
#include "Utility/ShaderAsset/shaderReflectionDataParser.h"

#include "ShaderAsset.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker_Shader;
	}

	namespace graphics 
	{
		class Material;
		class UniformBufferObject;
		class RenderingShaderProxy;
	}

	namespace asset
	{
		class DOOM_API D_CLASS ShaderAsset : public Asset
		{
			GENERATE_BODY()

			
		private:

			graphics::RenderingShaderProxy* ShaderProxy = nullptr;
			
			
			D_PROPERTY()
			std::array<FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> mShaderTextDatas;
			
			/// <summary>
			/// Don't call this subthread, Should Call this at mainthread
			/// </summary>
			bool CompileShaders();
			bool CompileSpecificTypeShader(FShaderTextData& shaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType, ShaderObject& shaderObject);
			const std::vector<dooms::graphics::UniformBufferObject*>& GenerateUniformBufferObjectFromShaderReflectionData(const shaderReflectionDataParser::ShaderReflectionData& shaderReflectionData);

			void CreateInputLayoutForD3D(dooms::asset::ShaderAsset* const shaderAsset);

		public:

			ShaderAsset();
			ShaderAsset(const ShaderAsset& shader) = delete;
			ShaderAsset(ShaderAsset&& shader) noexcept;
			ShaderAsset operator=(const ShaderAsset& shader) = delete;
			ShaderAsset& operator=(ShaderAsset&& shader) noexcept;
			virtual ~ShaderAsset();

			virtual void OnSetPendingKill() override;

			const std::vector<dooms::graphics::UniformBufferObject*>& GetContainedUniformBufferObject() const;

			bool SetShaderText
			(
				const std::array<FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderTextDatas,
				const bool compileShader
			);
			
			const std::string& GetShaderStringText(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			const std::string& GetShaderReflectionDataStringText(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			const shaderReflectionDataParser::ShaderReflectionData& GetShaderReflectionData(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;


			/// <summary>
			/// You can delete shaders after Linking to material program
			/// If Shader is linked to material program when the shader is deleted,
			/// Deleting is delayed until the shader is unlinked to the mateiral  
			/// </summary>
			void DestroyShaderObjects();
			void ClearShaderTextDatas();

		

			void OnEndImportInMainThread_Internal() final;
			
			const dooms::graphics::BufferID& GetShaderObject(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			bool IsShaderObjectSuccessfullyCreated(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			bool IsHasAnyValidShaderObject() const;
			bool IsHasAnyValidShaderTextString() const;

			graphics::Material* CreateMatrialWithThisShaderAsset();
			void CompileShaderIfNotCompiled();

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			graphics::eShaderCompileStatus GetCurrentShaderCompileStatus(const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType) const;
			
		};
		
	}
}
