#pragma once

#include <string>

#include "Base_Asset.h"

namespace doom
{
	class ShaderAsset : public Asset
	{
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
		void checkCompileError(unsigned int id, ShaderType shaderType);

	public:
		ShaderAsset(const std::string& shaderStr);

		ShaderAsset(const ShaderAsset& shader) = delete;
		ShaderAsset(ShaderAsset&& shader) noexcept;
		ShaderAsset operator=(const ShaderAsset& shader) = delete;
		ShaderAsset& operator=(ShaderAsset&& shader) noexcept;

		~ShaderAsset();

		void OnEndImportInMainThread() final;

		unsigned int GetVertexId();
		unsigned int GetFragmentId();
		unsigned int GetGeometryId();

	};

	

	template <> struct Asset::asset_type<Asset::eAssetType::SHADER> { using type = ShaderAsset; };
}
