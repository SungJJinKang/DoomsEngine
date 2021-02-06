#include "Path.h"
#include <filesystem>

std::string _GetCurrentPath(const char* additional)
{
	if (additional == nullptr)
	{
		return std::filesystem::current_path().string();
	}
	else
	{
		return std::filesystem::current_path().string() + "/" + additional;
	}
}
