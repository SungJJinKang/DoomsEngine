#include <sstream>
#include <array>

#include "ShaderAsset.h"

#include "../API/OpenglAPI.h"
#include "../Core.h"
#include "../Graphics/Material/Material.h"
#include "../../Helper/TextImporter.h"
#include "../../Helper/trim.h"
#include <UI/PrintText.h>

const std::string doom::asset::ShaderAsset::VertexShaderMacros = "#VERTEX";
const std::string doom::asset::ShaderAsset::FragmentShaderMacros = "#FRAGMENT";
const std::string doom::asset::ShaderAsset::GeometryShaderMacros = "#GEOMETRY";



doom::asset::ShaderAsset::ShaderAsset()
	: mVertexId(0), mFragmentId(0), mGeometryId(0)
{
}

doom::asset::ShaderAsset::ShaderAsset(const std::string& shaderStr)
	: mVertexId(0), mFragmentId(0), mGeometryId(0)
{
	SetShaderText(shaderStr, false);
	CompileShaders();
}

doom::asset::ShaderAsset::ShaderAsset(ShaderText shaderText)
	:mShaderText(std::move(shaderText)), mVertexId(0), mFragmentId(0), mGeometryId(0)
{
	CompileShaders();
}

doom::asset::ShaderAsset::ShaderAsset(ShaderAsset&& shader) noexcept
	: Asset(std::move(shader)), mVertexId{ shader.mVertexId }, mFragmentId{ shader.mFragmentId }, mGeometryId{ shader.mGeometryId }, 
	mShaderText{ std::move(shader.mShaderText) }
{
	shader.mVertexId = 0;
	shader.mFragmentId = 0;
	shader.mGeometryId = 0;
}

doom::asset::ShaderAsset& doom::asset::ShaderAsset::operator=(ShaderAsset&& shader) noexcept
{
	Asset::operator=(std::move(shader));

	mVertexId = shader.mVertexId;
	shader.mVertexId = 0;

	mFragmentId = shader.mFragmentId;
	shader.mFragmentId = 0;

	mGeometryId = shader.mGeometryId;
	shader.mGeometryId = 0;

	mShaderText = std::move(shader.mShaderText);

	return *this;
}

doom::asset::ShaderAsset::~ShaderAsset()
{
	DeleteShaders();
}

void doom::asset::ShaderAsset::DeleteShaders()
{
	if (mVertexId != 0)
	{
		glDeleteShader(mVertexId);
		mVertexId = 0;
	}

	if (mFragmentId != 0)
	{
		glDeleteShader(mFragmentId);
		mFragmentId = 0;
	}

	if (mGeometryId != 0)
	{
		glDeleteShader(mGeometryId);
		mGeometryId = 0;
	}
}

void doom::asset::ShaderAsset::SetShaderText(const std::string& shaderStr, const bool compileShader)
{
	ClassifyShader(shaderStr);
	if (compileShader == true)
	{
		CompileShaders();
	}
}

void doom::asset::ShaderAsset::CompileShaders()
{
	mVertexId = 0;
	mFragmentId = 0;
	mGeometryId = 0;

	D_ASSERT(
		mShaderText.mVertexShaderText.empty() == false ||
		mShaderText.mFragmentShaderText.empty() == false ||
		mShaderText.mGeometryShaderText.empty() == false
	);

	if (mShaderText.mVertexShaderText.empty() == false)
	{
		CompileSpecificShader(mShaderText.mVertexShaderText, ShaderType::Vertex, mVertexId);
	}

	if (mShaderText.mFragmentShaderText.empty() == false)
	{
		CompileSpecificShader(mShaderText.mFragmentShaderText, ShaderType::Fragment, mFragmentId);
	}

	if (mShaderText.mGeometryShaderText.empty() == false)
	{
		CompileSpecificShader(mShaderText.mGeometryShaderText, ShaderType::Geometry, mGeometryId);
	}

	
}

void doom::asset::ShaderAsset::CompileSpecificShader(const std::string& shaderStr, ShaderType shaderType, unsigned int& shaderId)
{
	unsigned int shaderTypeFlag{};
	if (shaderType == ShaderType::Vertex)
	{
		shaderTypeFlag = GL_VERTEX_SHADER;
	}
	else if (shaderType == ShaderType::Fragment)
	{
		shaderTypeFlag = GL_FRAGMENT_SHADER;

	}
	else if (shaderType == ShaderType::Geometry)
	{
		shaderTypeFlag = GL_GEOMETRY_SHADER;
	}


	shaderId = glCreateShader(shaderTypeFlag);

	const char* shaderCode = shaderStr.c_str();
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);

#ifdef DEBUG_MODE
	checkCompileError(shaderId, shaderType);
#endif

	if (shaderType == ShaderType::Vertex)
	{
		doom::ui::PrintText("Compile Shader - Vertex ( %s )", GetAssetPath().generic_string().c_str());
	}
	else if (shaderType == ShaderType::Fragment)
	{
		doom::ui::PrintText("Compile Shader - Fragment ( %s )", GetAssetPath().generic_string().c_str());

	}
	else if (shaderType == ShaderType::Geometry)
	{
		doom::ui::PrintText("Compile Shader - Geometry ( %s )", GetAssetPath().generic_string().c_str());
	}
	
}



void doom::asset::ShaderAsset::ClassifyShader(const std::string& shaderText)
{
	std::stringstream inputStringStream{ shaderText };
	std::string line;

	ShaderType currentShaderType = ShaderType::None;
	std::string currentShaderStr{};

	

	while (std::getline(inputStringStream, line))
	{
		bool isMacros = false;

		if (CheckIsSharpInclude(line))
		{
			//mAssetPath.relative
			std::filesystem::path targetPath = GetAssetPath();//
			targetPath.remove_filename();

			std::string includeTargetPath = line.substr(line.find("#include", 0) + 8, std::string::npos);
			includeTargetPath = std::trim(includeTargetPath, "\r");
			includeTargetPath = std::trim(includeTargetPath, ' ');
			targetPath.append(includeTargetPath);

			currentShaderStr += ExtractShaderFile(targetPath.make_preferred().string());
			currentShaderStr += '\n';
			continue;
		}
		else if (line.compare(0, 1, "#") == 0)
		{// macros shouldn't have whitespace

			if  
				(line.compare(0, ShaderAsset::VertexShaderMacros.size(), ShaderAsset::VertexShaderMacros, 0) == 0 ||
				line.compare(0, ShaderAsset::FragmentShaderMacros.size(), ShaderAsset::FragmentShaderMacros, 0) == 0 ||
				line.compare(0, ShaderAsset::GeometryShaderMacros.size(), ShaderAsset::GeometryShaderMacros, 0) == 0
				)
			{
				if (currentShaderStr.size() != 0)
				{
					switch (currentShaderType)
					{
					case ShaderType::Vertex:
						mShaderText.mVertexShaderText = std::move(currentShaderStr);
						break;

					case ShaderType::Fragment:
						mShaderText.mFragmentShaderText = std::move(currentShaderStr);
						break;

					case ShaderType::Geometry:
						mShaderText.mGeometryShaderText = std::move(currentShaderStr);
						break;
					}

					currentShaderStr.clear();
				}

				if (line.compare(0, ShaderAsset::VertexShaderMacros.size(), ShaderAsset::VertexShaderMacros, 0) == 0)
				{
					currentShaderType = ShaderType::Vertex;
					isMacros = true;
				}
				else if (line.compare(0, ShaderAsset::FragmentShaderMacros.size(), ShaderAsset::FragmentShaderMacros, 0) == 0)
				{
					currentShaderType = ShaderType::Fragment;
					isMacros = true;
				}
				else if (line.compare(0, ShaderAsset::GeometryShaderMacros.size(), ShaderAsset::GeometryShaderMacros, 0) == 0)
				{
					currentShaderType = ShaderType::Geometry;
					isMacros = true;
				}

				continue;
			}
		}
		
		

		if (currentShaderType != ShaderType::None)
		{
			currentShaderStr += line; // getline stil contain newline character(\n)
			currentShaderStr += '\n';
		}
	}

	if (currentShaderStr.size() != 0)
	{
		switch (currentShaderType)
		{
		case ShaderType::Vertex:
			mShaderText.mVertexShaderText = std::move(currentShaderStr);
			break;

		case ShaderType::Fragment:
			mShaderText.mFragmentShaderText = std::move(currentShaderStr);
			break;

		case ShaderType::Geometry:
			mShaderText.mGeometryShaderText = std::move(currentShaderStr);
			break;
		}

	}

	D_ASSERT_LOG
	(
		mShaderText.mVertexShaderText.empty() == false ||
		mShaderText.mFragmentShaderText.empty() == false ||
		mShaderText.mGeometryShaderText.empty() == false,
		"Invalid Shader Asset ( File Path : %s )", GetAssetPath().u8string().c_str()
	);
}


bool doom::asset::ShaderAsset::CheckIsSharpInclude(const std::string& str)
{
	std::string trimedStr = std::trim(str, ' ');
	if (trimedStr.compare(0, 1, "#") == 0)
	{// macros shouldn't have whitespace

		if (trimedStr.compare(0, 8, "#include") == 0)
		{// To Support #include in GLSL
			return true;
		}
	}

	return false;
}

std::string doom::asset::ShaderAsset::ExtractShaderFile(const std::filesystem::path& path)
{
	std::stringstream inputStringStream{ GetTextFromFile(path) };
	std::string line;

	std::string extractedShaderText{};

	while (std::getline(inputStringStream, line))
	{
		if (CheckIsSharpInclude(line))
		{
			std::filesystem::path targetPath = path;//
			targetPath.remove_filename();

			std::string includeTargetPath = line.substr(line.find("#include", 0) + 8, std::string::npos);
			includeTargetPath = std::trim(includeTargetPath, "\r");
			includeTargetPath = std::trim(includeTargetPath, ' ');
			targetPath.append(includeTargetPath);

			extractedShaderText += ExtractShaderFile(targetPath.make_preferred().string());
		}
		else
		{
			extractedShaderText += line;
		}
		extractedShaderText += '\n';
	}
	
	return extractedShaderText;
}

#ifdef DEBUG_MODE
void doom::asset::ShaderAsset::checkCompileError(unsigned int id, ShaderType shaderType)
{
	int success;
	char infoLog[1024];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	std::string shaderTypeStr{};
	if (shaderType == ShaderType::Vertex)
	{
		shaderTypeStr = "Vertex Shader";
	}
	else if (shaderType == ShaderType::Vertex)
	{
		shaderTypeStr = "Fragment Shader";

	}
	else if (shaderType == ShaderType::Vertex)
	{
		shaderTypeStr = "Geometry Shader";
	}

	if (!success)
	{
		glGetShaderInfoLog(id, 1024, NULL, infoLog);
		D_DEBUG_LOG(
			{ "Shader File Name : ", GetAssetFileName(),
			"\nSHADER_COMPILATION_ERROR\n", 
			shaderTypeStr.c_str(), 
			"\n", 
			infoLog, 
			}
		, eLogType::D_ERROR
		);
	}
}
#endif

bool doom::asset::ShaderAsset::GetIsValid() const
{
	return mVertexId || mFragmentId || mGeometryId;
}

void doom::asset::ShaderAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING("Compile Shader", eProfileLayers::Rendering);
	CompileShaders();
	D_END_PROFILING("Compile Shader");
}

unsigned int doom::asset::ShaderAsset::GetVertexId() const
{
	return mVertexId;
}

unsigned int doom::asset::ShaderAsset::GetFragmentId() const
{
	return mFragmentId;
}

unsigned int doom::asset::ShaderAsset::GetGeometryId() const
{
	return mGeometryId;
}

doom::graphics::Material doom::asset::ShaderAsset::CreateMatrialWithThisShader()
{
	return doom::graphics::Material(this);
}

doom::asset::ShaderAsset::ShaderText::ShaderText(
	std::string vertexShaderText, 
	std::string fragmentShaderText, 
	std::string geometryShaderText
)
	: mVertexShaderText(std::move(vertexShaderText)),
	mFragmentShaderText(std::move(fragmentShaderText)),
	mGeometryShaderText(std::move(geometryShaderText))
{
}

void doom::asset::ShaderAsset::ShaderText::Clear()
{
	mVertexShaderText.resize(0);
	mFragmentShaderText.resize(0);
	mGeometryShaderText.resize(0);
}
