#include "AssetExporter_Shader.h"

#include <DynamicLinkingHelper/SmartDynamicLinking.h>
#include <EngineGUI/PrintText.h>

#define GLSLCC_DLL_FILE_NAME "glslcc.dll"

#define GLSL_ENGINE_SHADER_TEXT_FILE_EXTENSION "glsl.shader"
#define HLSL_ENGINE_SHADER_TEXT_FILE_EXTENSION "hlsl.shader"

namespace dooms::assetExporter::assetExporterShader
{
	static SmartDynamicLinking _SmartDynamicLinking{  };
}

bool dooms::assetExporter::assetExporterShader::GenerateEngineShaderFiles
(
	const std::filesystem::path& originalGlslShaderTextFilePath,
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType toShaderTextGraphisAPIType
)
{
	bool isSuccess = false;

	D_ASSERT(toShaderTextGraphisAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE);
	D_ASSERT(originalGlslShaderTextFilePath.extension().compare(".glsl") == 0);
	if ( (originalGlslShaderTextFilePath.extension().compare(".glsl") == 0) && (toShaderTextGraphisAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE) )
	{
		std::vector<std::string> glslccArgvs;

		glslccArgvs.push_back(originalGlslShaderTextFilePath.generic_u8string());
		
		if (toShaderTextGraphisAPIType == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			const std::filesystem::path outPutPath = std::filesystem::path{ originalGlslShaderTextFilePath }.replace_extension(GLSL_ENGINE_SHADER_TEXT_FILE_EXTENSION);
			glslccArgvs.push_back("--output=" + outPutPath.generic_u8string());

			glslccArgvs.push_back("--lang=glsl");
		}
		else if (toShaderTextGraphisAPIType == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			const std::filesystem::path outPutPath = std::filesystem::path{ originalGlslShaderTextFilePath }.replace_extension(HLSL_ENGINE_SHADER_TEXT_FILE_EXTENSION);
			glslccArgvs.push_back("--output=" + outPutPath.generic_u8string());

			glslccArgvs.push_back("--lang=hlsl");
		}
		else
		{
			NEVER_HAPPEN;
		}

		glslccArgvs.push_back("--reflect");


		/*
		 *	glslcc arguments : GbufferWriter_PBR.glsl --output=GbufferWriter_PBR.hlsl --lang=hlsl --reflect
		 *
		 *  Generated files : "GbufferWriter_PBR_fs.hlsl", "GbufferWriter_PBR_fs.hlsl.json", "GbufferWriter_PBR_vs.hlsl", "GbufferWriter_PBR_vs.hlsl.json"
		 */

		LoadGlslcc();

		std::vector<const char*> cStrGlslccArgvs;
		cStrGlslccArgvs.push_back(nullptr); // first argument is stripped out
		for(const std::string& argv : glslccArgvs)
		{
			cStrGlslccArgvs.push_back(argv.c_str());
		}


		dooms::ui::PrintText("Generating Engine Shader File ( Shader File Path : %s )", originalGlslShaderTextFilePath.generic_u8string().c_str());

		int result;
		_SmartDynamicLinking.CallFunctionWithReturn<int, int, char**>("glslcc", result, static_cast<int>(cStrGlslccArgvs.size()), const_cast<char**>(cStrGlslccArgvs.data()));
		
		if(result == 0)
		{
			dooms::ui::PrintText("Success to generate Engine Shader File ( Shader File Path : %s )", originalGlslShaderTextFilePath.generic_u8string().c_str());
			D_DEBUG_LOG(eLogType::D_LOG, "SUCCESS TO GENERATE ENGINE SHADER FILES ( Shader File Path : %s )", originalGlslShaderTextFilePath.generic_u8string().c_str());
			isSuccess = true;
		}
		else
		{
			dooms::ui::PrintText("Fail to generate Engine Shader File ( Shader File Path : %s )", originalGlslShaderTextFilePath.generic_u8string().c_str());
			D_DEBUG_LOG(eLogType::D_LOG, "FAIL TO GENERATE ENGINE SHADER FILES ( Shader File Path : %s )", originalGlslShaderTextFilePath.generic_u8string().c_str());
		}
	}

	return isSuccess;
}

void dooms::assetExporter::assetExporterShader::LoadGlslcc()
{
	if(_SmartDynamicLinking.IsDynamicLibraryLoaded() == false)
	{
		_SmartDynamicLinking.LoadDynamicLinkingLibrary(GLSLCC_DLL_FILE_NAME);
	}
}

void dooms::assetExporter::assetExporterShader::UnloadGlslcc()
{
	_SmartDynamicLinking.ReleaseDynamicLinkingLibrary();
}


std::filesystem::path dooms::assetExporter::assetExporterShader::GetEngineShaderFilePath
(
	const std::filesystem::path& originalShaderFilePath,
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType targetShaderTextGraphisAPIType,
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetShaderStageType,
	const eEngineShaderFileType targetFileType
)
{
	/*
	 *	Original File Name : GbufferWriter_PBR.glsl
	 *
	 *	OPENGL(GLSL) : GbufferWriter_PBR.shader.glsl
	 *	OPENGL(GLSL) Reflection File : GbufferWriter_PBR.shader.glsl.json
	 *
	 *	DIRECTX(HLSL) : GbufferWriter_PBR.shader.hlsl
	 *	DIRECTX(HLSL) Reflection File : GbufferWriter_PBR.shader.hlsl.json
	 */

	D_ASSERT(originalShaderFilePath.extension().compare(".glsl") == 0);
	if (originalShaderFilePath.extension().compare(".glsl") == 0)
	{
		std::filesystem::path targetShaderFilePath = std::filesystem::path{ originalShaderFilePath }.replace_extension("");

		{
			std::string replacedFileName = targetShaderFilePath.filename().generic_u8string();
			switch (targetShaderStageType)
			{
			case graphics::GraphicsAPI::VERTEX_SHADER:
				replacedFileName += "_vs";
				break;
			case graphics::GraphicsAPI::PIXEL_SHADER:
				replacedFileName += "_fs";
				break;
			case graphics::GraphicsAPI::COMPUTE_SHADER:
				replacedFileName += "_cs";
				break;
			default:
				NEVER_HAPPEN;
			}
			targetShaderFilePath.replace_filename(replacedFileName);
		}

		{
			std::string newExtension;

			switch (targetShaderTextGraphisAPIType)
			{
			case graphics::GraphicsAPI::eGraphicsAPIType::OpenGL:
				newExtension += GLSL_ENGINE_SHADER_TEXT_FILE_EXTENSION;
				break;
			case graphics::GraphicsAPI::eGraphicsAPIType::DX11_10: 
				newExtension += HLSL_ENGINE_SHADER_TEXT_FILE_EXTENSION;
				break;
			default:
				NEVER_HAPPEN;
			}

			switch (targetFileType)
			{
			case eEngineShaderFileType::SHADER_TEXT_FILE: 
				
				break;
			case eEngineShaderFileType::SHADER_REFLECTION_DATA_JSON_FILE: 
				newExtension += ".json";
				break;
			default:
				NEVER_HAPPEN;
			}

			D_ASSERT(newExtension.empty() == false);
			targetShaderFilePath.replace_extension(newExtension);
		}
		
		return targetShaderFilePath;
	}
	else
	{
		return {};
	}
}
