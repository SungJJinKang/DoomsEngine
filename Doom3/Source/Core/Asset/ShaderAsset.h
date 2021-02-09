#pragma once

#include <string>

#include "Base_Asset.h"

namespace doom
{
	class ShaderAsset : public Asset
	{
		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

	private:

		enum class ShaderType 
		{
			None,
			Vertex,
			Fragment,
			Geometry
		};

		std::string mShaderFileText;

		static const std::string VertexShaderMacros;
		static const std::string FragmentShaderMacros;
		static const std::string GeometryShaderMacros;

		unsigned int mVertexId, mFragmentId, mGeometryId;

		
	
		/// <summary>
		/// Don't call this subthread, Should Call this at mainthread
		/// </summary>
		void CompileShaders(const std::string& str);
		void CompileSpecificShader(const std::string& shaderStr, ShaderType shaderType, unsigned int& shaderId);
		std::array<std::string, 3> ClassifyShader(const std::string& str);
		bool CheckIsSharpInclude(const std::string& str);
		/// <summary>
		/// extract shader file
		/// this function also extract recursive #include (#include of #include of #include), 
		/// </summary>
		/// <param name="shaderStr"></param>
		std::string ExtractShaderFile(const std::filesystem::path& path);

		void checkCompileError(unsigned int id, ShaderType shaderType);

		/// <summary>
		/// return shader is valid??
		/// </summary>
		/// <returns></returns>
		bool GetIsValid();

	protected:

	

	public:
		
		ShaderAsset() = default;
		ShaderAsset(const std::string & shaderStr);
		ShaderAsset(const ShaderAsset & shader) = delete;
		ShaderAsset(ShaderAsset && shader) noexcept;
		ShaderAsset operator=(const ShaderAsset & shader) = delete;
		ShaderAsset& operator=(ShaderAsset && shader) noexcept;
		~ShaderAsset();

		void OnEndImportInMainThread() final;

		unsigned int GetVertexId();
		unsigned int GetFragmentId();
		unsigned int GetGeometryId();

	};

	

	template <> struct Asset::asset_type<eAssetType::SHADER> { using type = ShaderAsset; };
}
