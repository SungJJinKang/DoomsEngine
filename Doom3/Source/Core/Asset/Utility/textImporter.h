#pragma once

#include <string>
#include <filesystem>

namespace dooms
{
	namespace asset
	{
		namespace textImporter
		{
			extern std::string GetTextFromFile(const std::filesystem::path& path);
			extern bool GetTextFromFile(const std::filesystem::path& path, std::string& text);
		}
	
	}
}