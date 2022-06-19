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
			
			std::array<FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderTextDatas;
			
			D_PROPERTY()
			std::vector<dooms::graphics::UniformBufferObject*> ContainedUniformBufferObjects;
			/*
			bool ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat(ShaderTextData& outShaderText);
			*/
			
			/// <summary>
			/// Don't call this subthread, Should Call this at mainthread
			/// </summary>
			void CreateRenderingShaderProxy();
			void CreateRenderingShaderProxyIfNotCreated();
			void DestroyRenderingShaderProxy();
			void GenerateUniformBufferObjectFromShaderReflectionData();

		public:

			ShaderAsset();
			ShaderAsset(const ShaderAsset& shader) = delete;
			ShaderAsset(ShaderAsset&& shader) noexcept;
			ShaderAsset operator=(const ShaderAsset& shader) = delete;
			ShaderAsset& operator=(ShaderAsset&& shader) noexcept;
			virtual ~ShaderAsset();

			virtual void OnSetPendingKill() override;

			graphics::RenderingShaderProxy* GetRenderingShaderProxy() const;

			const std::vector<dooms::graphics::UniformBufferObject*>& GetContainedUniformBufferObject() const;
			
			bool SetShaderText(const std::array<FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT>& InShaderTextDatas);
			const std::string& GetShaderStringText(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			const std::string& GetShaderReflectionDataStringText(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			const shaderReflectionDataParser::ShaderReflectionData& GetShaderReflectionData(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;

			bool IsHasAnyValidShaderTextString() const;
			void ClearShaderTextDatas();

			void OnEndImportInMainThread_Internal() final;
			
			graphics::Material* CreateMatrialWithThisShaderAsset();
			bool IsRenderingShaderProxyCreated() const;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			graphics::eShaderCompileStatus GetCurrentShaderCompileStatus(const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType) const;
		};
		
	}
}
