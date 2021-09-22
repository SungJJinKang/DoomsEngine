#pragma once

#include <string>

#include "Base_Asset.h"

namespace doom
{
	namespace graphics 
	{
		class Material;
	}
	namespace asset
	{
		class ShaderAsset : public Asset
		{
			friend class ::doom::assetimporter::ImportedAssetPort<eAssetType::SHADER>;

			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;
		
		public:

			struct ShaderText
			{
				std::string mVertexShaderText;
				std::string mFragmentShaderText;
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

			enum class ShaderType
			{
				None,
				Vertex,
				Fragment,
				Geometry
			};

			

			ShaderText mShaderText;

			static const std::string VertexShaderMacros;
			static const std::string FragmentShaderMacros;
			static const std::string GeometryShaderMacros;

			bool bmIsShaderCompiled{ false };
			unsigned int mVertexId, mFragmentId, mGeometryId;



			/// <summary>
			/// Don't call this subthread, Should Call this at mainthread
			/// </summary>
			void CompileShaders();
			void CompileSpecificShader(const std::string& shaderStr, ShaderType shaderType, unsigned int& shaderId);
			void ClassifyShader(const std::string& shaderText);
			bool CheckIsSharpInclude(const std::string& str);
			/// <summary>
			/// extract shader file
			/// this function also extract recursive #include (#include of #include of #include), 
			/// </summary>
			/// <param name="shaderStr"></param>
			std::string ExtractShaderFile(const std::filesystem::path& path);

#ifdef DEBUG_MODE
			void checkCompileError(unsigned int id, ShaderType shaderType);
#endif
			/// <summary>
			/// return shader is valid??
			/// </summary>
			/// <returns></returns>
			bool GetIsValid() const;

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

			/// <summary>
			/// You can delete shaders after Linking to material program
			/// If Shader is linked to material program when the shader is deleted,
			/// Deleting is delayed until the shader is unlinked to the mateiral  
			/// </summary>
			void DeleteShaders();

			void SetShaderText(const std::string& shaderStr, const bool compileShader = true);

			void OnEndImportInMainThread_Internal() final;

			unsigned int GetVertexId() const;
			unsigned int GetFragmentId() const;
			unsigned int GetGeometryId() const;

			graphics::Material CreateMatrialWithThisShader();
		};

		template <> struct Asset::asset_type<eAssetType::SHADER> { using type = ShaderAsset; };
	}
}
