#include <sstream>

#include "ShaderAsset.h"

#include "../Graphics/Material/Material.h"
#include <utility/TextImporter.h>
#include <utility/trim.h>
#include <EngineGUI/PrintText.h>

const std::string dooms::asset::ShaderAsset::VertexShaderMacros = "#VERTEX";
const std::string dooms::asset::ShaderAsset::FragmentShaderMacros = "#FRAGMENT";
const std::string dooms::asset::ShaderAsset::GeometryShaderMacros = "#GEOMETRY";



dooms::asset::ShaderAsset::ShaderAsset()
	: mVertexId(), mFragmentId(), mGeometryId()
{
}

dooms::asset::ShaderAsset::ShaderAsset(const std::string& shaderStr)
	: mVertexId(), mFragmentId(), mGeometryId()
{
	SetShaderText(shaderStr, false);
	CompileShaders();
}

dooms::asset::ShaderAsset::ShaderAsset(ShaderText shaderText)
	:mShaderText(std::move(shaderText)), mVertexId(), mFragmentId(), mGeometryId()
{
	CompileShaders();
}

dooms::asset::ShaderAsset::ShaderAsset(ShaderAsset&& shader) noexcept
	: Asset(std::move(shader)), mVertexId{ shader.mVertexId }, mFragmentId{ shader.mFragmentId }, mGeometryId{ shader.mGeometryId }, 
	mShaderText{ std::move(shader.mShaderText) }
{
	shader.mVertexId.Reset();
	shader.mFragmentId.Reset();
	shader.mGeometryId.Reset();
}

dooms::asset::ShaderAsset& dooms::asset::ShaderAsset::operator=(ShaderAsset&& shader) noexcept
{
	Base::operator=(std::move(shader));

	mVertexId = shader.mVertexId;
	shader.mVertexId.Reset();

	mFragmentId = shader.mFragmentId;
	shader.mFragmentId.Reset();

	mGeometryId = shader.mGeometryId;
	shader.mGeometryId.Reset();

	mShaderText = std::move(shader.mShaderText);

	return *this;
}

dooms::asset::ShaderAsset::~ShaderAsset()
{
}

void dooms::asset::ShaderAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();
	
	DeleteShaders();
}

void dooms::asset::ShaderAsset::DeleteShaders()
{
	if (mVertexId.IsValid())
	{
		graphics::GraphicsAPI::DestroyShaderObject(mVertexId);
		mVertexId.Reset();
	}

	if (mFragmentId.IsValid())
	{
		graphics::GraphicsAPI::DestroyShaderObject(mFragmentId);
		mFragmentId.Reset();
	}

	if (mGeometryId.IsValid())
	{
		graphics::GraphicsAPI::DestroyShaderObject(mGeometryId);
		mGeometryId.Reset();
	}
}

void dooms::asset::ShaderAsset::SetShaderText(const std::string& shaderStr, const bool compileShader)
{
	ClassifyShader(shaderStr);
	if (compileShader == true)
	{
		CompileShaders();
	}
}

void dooms::asset::ShaderAsset::CompileShaders()
{
	mVertexId.Reset();
	mFragmentId.Reset();
	mGeometryId.Reset();

	D_ASSERT(
		mShaderText.mVertexShaderText.empty() == false ||
		mShaderText.mFragmentShaderText.empty() == false ||
		mShaderText.mGeometryShaderText.empty() == false
	);

	if (mShaderText.mVertexShaderText.empty() == false)
	{
		CompileSpecificShader(mShaderText.mVertexShaderText, graphics::GraphicsAPI::Vertex, mVertexId);
	}

	if (mShaderText.mFragmentShaderText.empty() == false)
	{
		CompileSpecificShader(mShaderText.mFragmentShaderText, graphics::GraphicsAPI::Fragment, mFragmentId);
	}

	if (mShaderText.mGeometryShaderText.empty() == false)
	{
		CompileSpecificShader(mShaderText.mGeometryShaderText, graphics::GraphicsAPI::Geometry, mGeometryId);
	}

	
}

void dooms::asset::ShaderAsset::CompileSpecificShader(const std::string& shaderStr, graphics::GraphicsAPI::eShaderType shaderType, dooms::graphics::BufferID& shaderId)
{
	UINT32 shaderTypeFlag{};
	shaderId = graphics::GraphicsAPI::CreateShaderObject(shaderType);

	const char* shaderCode = shaderStr.c_str();
	graphics::GraphicsAPI::CompileShader(shaderId, shaderType, shaderCode);

/*
#ifdef DEBUG_MODE
	checkCompileError(shaderId, shaderType);
#endif
*/

	if (shaderType == graphics::GraphicsAPI::Vertex)
	{
		dooms::ui::PrintText("Compile Shader - Vertex ( %s )", GetAssetPath().generic_string().c_str());
	}
	else if (shaderType == graphics::GraphicsAPI::Fragment)
	{
		dooms::ui::PrintText("Compile Shader - Fragment ( %s )", GetAssetPath().generic_string().c_str());

	}
	else if (shaderType == graphics::GraphicsAPI::Geometry)
	{
		dooms::ui::PrintText("Compile Shader - Geometry ( %s )", GetAssetPath().generic_string().c_str());
	}
	
}



void dooms::asset::ShaderAsset::ClassifyShader(const std::string& shaderText)
{
	std::stringstream inputStringStream{ shaderText };
	std::string line;

	graphics::GraphicsAPI::eShaderType currentShaderType = graphics::GraphicsAPI::eShaderType::ShaderType_None;
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
					case graphics::GraphicsAPI::eShaderType::Vertex:
						mShaderText.mVertexShaderText = std::move(currentShaderStr);
						break;

					case graphics::GraphicsAPI::eShaderType::Fragment:
						mShaderText.mFragmentShaderText = std::move(currentShaderStr);
						break;

					case graphics::GraphicsAPI::eShaderType::Geometry:
						mShaderText.mGeometryShaderText = std::move(currentShaderStr);
						break;
					}

					currentShaderStr.clear();
				}

				if (line.compare(0, ShaderAsset::VertexShaderMacros.size(), ShaderAsset::VertexShaderMacros, 0) == 0)
				{
					currentShaderType = graphics::GraphicsAPI::eShaderType::Vertex;
					isMacros = true;
				}
				else if (line.compare(0, ShaderAsset::FragmentShaderMacros.size(), ShaderAsset::FragmentShaderMacros, 0) == 0)
				{
					currentShaderType = graphics::GraphicsAPI::eShaderType::Fragment;
					isMacros = true;
				}
				else if (line.compare(0, ShaderAsset::GeometryShaderMacros.size(), ShaderAsset::GeometryShaderMacros, 0) == 0)
				{
					currentShaderType = graphics::GraphicsAPI::eShaderType::Geometry;
					isMacros = true;
				}

				continue;
			}
		}
		
		

		if (currentShaderType != graphics::GraphicsAPI::eShaderType::ShaderType_None)
		{
			currentShaderStr += line; // getline stil contain newline character(\n)
			currentShaderStr += '\n';
		}
	}

	if (currentShaderStr.size() != 0)
	{
		switch (currentShaderType)
		{
		case graphics::GraphicsAPI::eShaderType::Vertex:
			mShaderText.mVertexShaderText = std::move(currentShaderStr);
			break;

		case graphics::GraphicsAPI::eShaderType::Fragment:
			mShaderText.mFragmentShaderText = std::move(currentShaderStr);
			break;

		case graphics::GraphicsAPI::eShaderType::Geometry:
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


bool dooms::asset::ShaderAsset::CheckIsSharpInclude(const std::string& str)
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

std::string dooms::asset::ShaderAsset::ExtractShaderFile(const std::filesystem::path& path)
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

/*
#ifdef DEBUG_MODE
void dooms::asset::ShaderAsset::checkCompileError(UINT32& id, ShaderType shaderType)
{
	INT32 success;
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
		id = 0;
		D_ASSERT_LOG
		(
			false, "Shader File Name : %s ( Shader Type : %s ). SHADER_COMPILATION_ERROR : %s"
			, GetAssetFileName().c_str()
			, shaderTypeStr.c_str()
			, infoLog
		);
		dooms::ui::PrintText
		(
			"Shader File Name : %s ( Shader Type : %s ). SHADER_COMPILATION_ERROR : %s"
			, GetAssetFileName().c_str()
			, shaderTypeStr.c_str()
			, infoLog
		);
	}
}
#endif
*/


void dooms::asset::ShaderAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Compile_Shader, eProfileLayers::Rendering);
	CompileShaders();
	D_END_PROFILING(Compile_Shader);
}

dooms::graphics::Material dooms::asset::ShaderAsset::CreateMatrialWithThisShader()
{
	return dooms::graphics::Material(this);
}

dooms::asset::eAssetType dooms::asset::ShaderAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::SHADER;
}

bool dooms::asset::ShaderAsset::GetIsShaderCompiled() const
{
	return (GetVertexId().IsValid() || GetFragmentId().IsValid() || GetGeometryId().IsValid());
}

dooms::asset::ShaderAsset::ShaderText::ShaderText(
	std::string vertexShaderText, 
	std::string fragmentShaderText, 
	std::string geometryShaderText
)
	: mVertexShaderText(std::move(vertexShaderText)),
	mFragmentShaderText(std::move(fragmentShaderText)),
	mGeometryShaderText(std::move(geometryShaderText))
{
}

void dooms::asset::ShaderAsset::ShaderText::Clear()
{
	mVertexShaderText.resize(0);
	mFragmentShaderText.resize(0);
	mGeometryShaderText.resize(0);
}
