#pragma once

#include <string>

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
		class DOOM_API D_CLASS ShaderAsset : public Asset
		{
			GENERATE_BODY()
				

			friend class ::dooms::assetImporter::AssetImporterWorker_Shader;
			
		
		public:

			struct DOOM_API D_STRUCT ShaderText
			{
				D_PROPERTY()
				std::string mVertexShaderText;

				D_PROPERTY()
				std::string mFragmentShaderText;

				D_PROPERTY()
				std::string mGeometryShaderText;

				ShaderText() = default;
				ShaderText(
					std::string vertexShaderText,
					std::string fragmentShaderText,
					std::string geometryShaderText
				);
				void Clear();
			};

		private:

			

			D_PROPERTY()
			ShaderText mShaderText;

			static const std::string VertexShaderMacros;
			static const std::string FragmentShaderMacros;
			static const std::string GeometryShaderMacros;

			D_PROPERTY()
			bool bmIsShaderCompiled{ false };
			
			D_PROPERTY()
			dooms::graphics::BufferID mVertexId;

			D_PROPERTY()
			dooms::graphics::BufferID mFragmentId;

			D_PROPERTY()
			dooms::graphics::BufferID mGeometryId;



			/// <summary>
			/// Don't call this subthread, Should Call this at mainthread
			/// </summary>
			void CompileShaders();
			void CompileSpecificShader(const std::string& shaderStr, graphics::GraphicsAPI::eShaderType shaderType, dooms::graphics::BufferID& shaderId);
			void ClassifyShader(const std::string& shaderText);
			bool CheckIsSharpInclude(const std::string& str);
			/// <summary>
			/// extract shader file
			/// this function also extract recursive #include (#include of #include of #include), 
			/// </summary>
			/// <param name="shaderStr"></param>
			std::string ExtractShaderFile(const std::filesystem::path& path);

/*
#ifdef DEBUG_MODE
			void checkCompileError(UINT32& id, ShaderType shaderType);
#endif
*/
			
		protected:



		public:

			ShaderAsset();
			ShaderAsset(const std::string& shaderStr);
			ShaderAsset(ShaderText shaderText);
			ShaderAsset(const ShaderAsset& shader) = delete;
			ShaderAsset(ShaderAsset&& shader) noexcept;
			ShaderAsset operator=(const ShaderAsset& shader) = delete;
			ShaderAsset& operator=(ShaderAsset&& shader) noexcept;
			virtual ~ShaderAsset();

			virtual void OnSetPendingKill() override;

			/// <summary>
			/// You can delete shaders after Linking to material program
			/// If Shader is linked to material program when the shader is deleted,
			/// Deleting is delayed until the shader is unlinked to the mateiral  
			/// </summary>
			void DeleteShaders();

			void SetShaderText(const std::string& shaderStr, const bool compileShader = true);

			void OnEndImportInMainThread_Internal() final;

			FORCE_INLINE const dooms::graphics::BufferID& GetVertexId() const
			{
				return mVertexId;
			}
			FORCE_INLINE bool IsVertexShaderExist() const
			{
				return mVertexId.IsValid();
			}
			FORCE_INLINE const dooms::graphics::BufferID& GetFragmentId() const
			{
				return mFragmentId;
			}
			FORCE_INLINE bool IsFramgmentShaderExist() const {
				return mFragmentId.IsValid();
			}
			FORCE_INLINE const dooms::graphics::BufferID& GetGeometryId() const
			{
				return mGeometryId;
			}
			FORCE_INLINE bool IsGeometryShaderExist() const
			{
				return mGeometryId.IsValid();
			}

			graphics::Material CreateMatrialWithThisShader();


			virtual dooms::asset::eAssetType GetEAssetType() const final;

			bool GetIsShaderCompiled() const;
		};
		
	}
}
