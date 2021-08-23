#pragma once

#include <vector>
#include <utility>
#include <string>
#include <variant>
#include <unordered_map>
#include <type_traits>
#include <cassert>
#include "../Core/Core.h"




class IniData
{
public:
	using ini_data_type = typename  std::variant<std::string, int, double, bool>;
	//using VariableType = typename  std::pair<std::string, ini_data_type>;
	
private:
	/// <summary>
	/// Section -> Data
	/// </summary>
	std::unordered_map<std::string, std::unordered_map<std::string, ini_data_type> > mIniDatas{};
public:

	

	void AddSection(const std::string& section);
	void InsertVariable(const std::string& section, const std::string& key, ini_data_type data);

	template <typename T>
	T GetValue(const std::string& section, const std::string& variableKey) const
	{
		auto& sectionData = mIniDatas.at(section);
		return std::get<T>(sectionData.at(variableKey));
	}

	template <>
	float GetValue<float>(const std::string& section, const std::string& variableKey) const
	{
		auto& sectionData = mIniDatas.at(section);
		return static_cast<float>(std::get<double>(sectionData.at(variableKey)));
	}

	bool IsValueExist(const std::string& section, const std::string& variableKey) const
	{
		auto& sectionData = mIniDatas.at(section);
		auto iter = sectionData.find(variableKey);

		return iter != sectionData.end();
	}
};

/// <summary>
/// Portable Ini Parser
/// </summary>
class SimpleIniParser
{
public:
	static IniData ParseIniFile(std::string fileDirectory);

	
};