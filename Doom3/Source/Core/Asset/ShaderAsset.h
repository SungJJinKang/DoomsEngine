#pragma once

#include <string>
#include <array>

#include "Asset.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Graphics/Buffer/BufferID.h>

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
	}

	namespace asset
	{
		struct DOOM_API D_STRUCT ShaderTextString
		{
			dooms::graphics::GraphicsAPI::eGraphicsAPIType mShaderTextGraphicsAPIType;
			std::string mText;

			ShaderTextString();

			ShaderTextString(const std::string& text);

			ShaderTextString(const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType, const std::string& text);

			void Clear();
			bool IsValid() const;
		};

		class DOOM_API D_CLASS ShaderAsset : public Asset
		{
			GENERATE_BODY()
				
		private:

			

			D_PROPERTY()
			std::array<ShaderTextString, GRAPHICS_PIPELINE_STAGE_COUNT> mShaderTextStrings;

			D_PROPERTY()
			std::array<dooms::graphics::BufferID, GRAPHICS_PIPELINE_STAGE_COUNT> mShaderObject;

			bool ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat(ShaderTextString& shaderText);
			
			/// <summary>
			/// Don't call this subthread, Should Call this at mainthread
			/// </summary>
			void CompileShaders();
			bool CompileSpecificTypeShader(ShaderTextString& shaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType, dooms::graphics::BufferID& shaderId);
			
		public:

			ShaderAsset();
			ShaderAsset(const std::array<ShaderTextString, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderText);
			ShaderAsset(const ShaderAsset& shader) = delete;
			ShaderAsset(ShaderAsset&& shader) noexcept;
			ShaderAsset operator=(const ShaderAsset& shader) = delete;
			ShaderAsset& operator=(ShaderAsset&& shader) noexcept;
			virtual ~ShaderAsset();

			virtual void OnSetPendingKill() override;

			void SetShaderText(const std::string& shaderStr, const dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderTextraphicsAPIType, const bool compileShader);


			/// <summary>
			/// You can delete shaders after Linking to material program
			/// If Shader is linked to material program when the shader is deleted,
			/// Deleting is delayed until the shader is unlinked to the mateiral  
			/// </summary>
			void DestroyShaderObjects();
			void ClearShaderTextStrings();

		

			void OnEndImportInMainThread_Internal() final;

			const dooms::graphics::BufferID& GetShaderObject(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			bool IsShaderObjectSuccessfullyCreated(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			bool IsHasAnyValidShaderObject() const;
			bool IsHasAnyValidShaderTextString() const;

			graphics::Material CreateMatrialWithThisShader();


			virtual dooms::asset::eAssetType GetEAssetType() const final;
			
		};
		
	}
}
