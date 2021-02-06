#pragma once
#include <optional>
#include <string>
#include <filesystem>

std::optional<std::string> GetTextFromFile(const std::filesystem::path& path);