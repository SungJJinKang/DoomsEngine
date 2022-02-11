#include "shaderAssetHelper.h"

#include <Core.h>

#include <array>
#include <filesystem>
#include <sstream>

#include <Misc/String/trim.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "../TextImporter.h"

namespace dooms::asset::shaderAssetHelper
{
	static const std::array<const std::string, GRAPHICS_PIPELINE_STAGE_COUNT> mShaderMacros
	{
		"//@begin_vert",
		"//@begin_frag",
		"//@begin_comp"
		//"#HULL",
		//"#DOMAIN",
		//"#GEOMETRY",
	};

	static const std::array<const std::string, GRAPHICS_PIPELINE_STAGE_COUNT> mShaderReflectionMacros
	{
		"#VERTEX_REFLECTION",
		"#FRAGMENT_REFLECTION",
		"#COMPUTE_REFLECTION"
		//"#HULL_REFLECTION",
		//"#DOMAIN_REFLECTION",
		//"#GEOMETRY_REFLECTION",
	};

	bool CheckIsSharpInclude(const std::string& str)
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

	std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> ParseShaderTextStringsBasedOnTargetGraphicsPipeLineStage(const std::filesystem::path& shaderAssetPath, const std::string& shaderText)
	{
		std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> shaderStringTexts{};
		
		std::stringstream inputStringStream{ shaderText };
		std::string line;

		graphics::GraphicsAPI::eGraphicsPipeLineStage currentShaderType = graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY;
		std::string currentShaderStr{};
		
		while (std::getline(inputStringStream, line))
		{
			if (shaderAssetHelper::CheckIsSharpInclude(line))
			{
				//mAssetPath.relative
				std::filesystem::path targetPath = shaderAssetPath;
				targetPath.remove_filename();

				std::string includeTargetPath = line.substr(line.find("#include", 0) + 8, std::string::npos);
				includeTargetPath = std::trim(includeTargetPath, "\r");
				includeTargetPath = std::trim(includeTargetPath, ' ');
				targetPath.append(includeTargetPath);

				currentShaderStr += ExtractShaderFile(targetPath.make_preferred().string());
				currentShaderStr += '\n';
				continue;
			}

			const size_t firstCharacterPos = line.find_first_not_of(' '); // find first not white space character
			if (firstCharacterPos == std::string::npos)
			{
				continue;
			}

			if (line[firstCharacterPos] == '#')
			{
				bool isFindShaderMacros = false;

				for (size_t shaderTypeIndex = 0; shaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT; shaderTypeIndex++)
				{
					if (line.compare(firstCharacterPos, mShaderMacros[shaderTypeIndex].size(), mShaderMacros[shaderTypeIndex], 0) == 0)
					{
						if (currentShaderStr.size() != 0 && currentShaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
						{
							shaderStringTexts[static_cast<UINT32>(currentShaderType)] = std::move(currentShaderStr); // store currentShaderStr current line to shader string
						}

						currentShaderStr.clear();

						currentShaderType = static_cast<graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex);
						isFindShaderMacros = true;

						break;
					}
				}

				if (isFindShaderMacros == true)
				{
					continue;
				}
			}


			if (currentShaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
			{
				currentShaderStr += line; // getline stil contain newline character(\n)
				currentShaderStr += '\n';
			}
		}

		if (currentShaderStr.size() != 0)
		{
			shaderStringTexts[static_cast<UINT32>(currentShaderType)] = std::move(currentShaderStr);
		}

		return std::move(shaderStringTexts);
	}

	std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> ParseShaderReflectionTextStringsBasedOnTargetGraphicsPipeLineStage(const std::string& shaderReflectionText)
	{
		std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> shaderReflectionDataStringTexts{};

		std::stringstream inputStringStream{ shaderReflectionText };
		std::string line;

		graphics::GraphicsAPI::eGraphicsPipeLineStage currentShaderType = graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY;
		std::string currentShaderStr{};

		while (std::getline(inputStringStream, line))
		{
			const size_t firstCharacterPos = line.find_first_not_of(' '); // find first not white space character
			if (firstCharacterPos == std::string::npos)
			{
				continue;
			}

			if (line[firstCharacterPos] == '#')
			{
				bool isFindShaderMacros = false;

				for (size_t shaderTypeIndex = 0; shaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT; shaderTypeIndex++)
				{
					if (line.compare(firstCharacterPos, mShaderReflectionMacros[shaderTypeIndex].size(), mShaderReflectionMacros[shaderTypeIndex], 0) == 0)
					{
						if (currentShaderStr.size() != 0 && currentShaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
						{
							shaderReflectionDataStringTexts[static_cast<UINT32>(currentShaderType)] = std::move(currentShaderStr); // store currentShaderStr current line to shader string
						}

						currentShaderStr.clear();

						currentShaderType = static_cast<graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex);
						isFindShaderMacros = true;

						break;
					}
				}

				if (isFindShaderMacros == true)
				{
					continue;
				}
			}


			if (currentShaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
			{
				currentShaderStr += line; // getline stil contain newline character(\n)
				currentShaderStr += '\n';
			}
		}

		if (currentShaderStr.size() != 0)
		{
			shaderReflectionDataStringTexts[static_cast<UINT32>(currentShaderType)] = std::move(currentShaderStr);
		}

		return std::move(shaderReflectionDataStringTexts);
	}

	std::string ExtractShaderFile(const std::filesystem::path& path)
	{
		std::stringstream inputStringStream{textImporter::GetTextFromFile(path) };
		std::string line;

		std::string extractedShaderText{};

		while (std::getline(inputStringStream, line))
		{
			if (shaderAssetHelper::CheckIsSharpInclude(line))
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

	dooms::graphics::GraphicsAPI::eGraphicsAPIType GetShaderAssetGraphicsAPIType
	(
		const std::string& shaderAssetFileExtension
	)
	{
		dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE;

		D_ASSERT_LOG(shaderAssetFileExtension[0] == '.', "shaderAssetFileExtension should start with '.'");
		if (shaderAssetFileExtension.empty() == false)
		{
			if (shaderAssetFileExtension == ".hlsl")
			{
				shaderGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10;
			}
			else if (shaderAssetFileExtension == ".glsl")
			{
				shaderGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL;
			}
		}

		return shaderGraphicsAPIType;
	}

}
