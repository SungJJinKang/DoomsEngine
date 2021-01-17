#pragma once

#include <string>

#include "../Core.h"

namespace Doom
{
	class Shader
	{
	private:

		enum class ShaderType : std::int8_t
		{
			None,
			Vertex,
			Fragment,
			Geometry
		};


		

		static const std::string VertexShaderMacros;
		static const std::string FragmentShaderMacros;
		static const std::string GeometryShaderMacros;

		unsigned int vertexId, fragmentId, geometryId;

		bool isCompiled = false;
		void CompileSpecificShader(const std::string& shaderStr, ShaderType shaderType, unsigned int& shaderId);
		std::array<std::string, 3> ClassifyShader(const std::string& str);
		void checkCompileError(unsigned int id, ShaderType shaderType);

	public:
		Shader(const std::string& shaderStr);

		Shader(const Shader& shader) = delete;
		Shader(Shader&& shader) noexcept;
		Shader operator=(const Shader& shader) = delete;
		Shader& operator=(Shader&& shader) noexcept;

		~Shader();
	};
}
