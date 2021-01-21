#pragma once

#include <string>

#include "Base_Asset.h"

namespace Doom
{
	class ShaderAsset : public Asset
	{
	private:

		enum class ShaderType : std::int8_t
		{
			None,
			Vertex,
			Fragment,
			Geometry
		};

		std::string ShaderFileText;

		static const std::string VertexShaderMacros;
		static const std::string FragmentShaderMacros;
		static const std::string GeometryShaderMacros;

		unsigned int vertexId, fragmentId, geometryId;

		bool IsCompiled = false;

		/// <summary>
		/// Don't call this subthread, Should Call this at mainthread
		/// </summary>
		void CompileShader(const std::string& str);
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

		void OnImportEndOnMainThread() final;
	};

	

	template <> struct Asset::AssetTypeConditional<Asset::AssetType::SHADER> { using type = ShaderAsset; };
}
