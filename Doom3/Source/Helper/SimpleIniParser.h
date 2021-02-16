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
	using ini_data_type = typename  std::variant<std::string, int, double>;
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
		auto& sectionData = this->mIniDatas.at(section);
		return std::get<T>(sectionData.at(variableKey));

	}
};

class SimpleIniParser
{
public:
	static IniData ParseIniFile(std::string fileDirectory);

	
};