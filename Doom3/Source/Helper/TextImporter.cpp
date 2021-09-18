#include "TextImporter.h"
#include <fstream>



std::string GetTextFromFile(const std::filesystem::path& path)
{
	std::ifstream inputFileStream(path, std::ios::in | std::ios::binary | std::ios::ate);

	D_ASSERT_LOG(inputFileStream.is_open() == true, "Fail to Load File ( %ls )", path.c_str());


	if (inputFileStream.is_open())
	{
		std::string str{};
		str.reserve(inputFileStream.tellg()); // prevent reallocation. reallocation is really really expensive
		inputFileStream.seekg(0, std::ios::beg);
		str.assign(std::istreambuf_iterator{ inputFileStream }, {});
		inputFileStream.close();

		return str;
	}
	else
	{
		return "";
	}
}

bool GetTextFromFile(const std::filesystem::path& path, std::string& text)
{
	std::ifstream inputFileStream(path, std::ios::in | std::ios::binary | std::ios::ate);

	if (inputFileStream.is_open())
	{
		text.reserve(inputFileStream.tellg()); // prevent reallocation. reallocation is really really expensive
		inputFileStream.seekg(0, std::ios::beg);
		text.assign(std::istreambuf_iterator{ inputFileStream }, {});
		inputFileStream.close();

		return true;
	}
	else
	{
		return false;
	}
}