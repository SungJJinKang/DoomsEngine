#pragma once

#include <string>
#include <filesystem>

#include "Doom_Core.h"

std::string GetTextFromFile(const std::filesystem::path& path);
bool GetTextFromFile(const std::filesystem::path& path, std::string& text);