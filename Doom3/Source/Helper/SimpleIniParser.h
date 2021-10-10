#pragma once

#include <utility>
#include <string>
#include <variant>
#include <unordered_map>


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
	const std::unordered_map<std::string, ini_data_type>* GetSection(const std::string& sectionKey) const;
	const ini_data_type* GetSectionData(const std::string& sectionKey, const std::string& variableKey) const;

public:

	

	void AddSection(const std::string& section);
	
	void InsertVariable(const std::string& section, const std::string& key, ini_data_type data);
	
	template <typename T>
	T GetValue(const std::string& section, const std::string& variableKey) const
	{
		auto sectionData = GetSectionData(section, variableKey);

		if(sectionData != nullptr)
		{
			return std::get<T>(*sectionData);
		}
		else
		{
			return T();
		}
		
	}

	template <>
	float GetValue<float>(const std::string& section, const std::string& variableKey) const
	{
		auto sectionData = GetSectionData(section, variableKey);

		if (sectionData != nullptr)
		{
			return static_cast<float>(std::get<double>(*sectionData));
		}
		else
		{
			return 0.0f;
		}
	}

	bool IsValueExist(const std::string& section, const std::string& variableKey) const
	{
		auto sectionData = GetSectionData(section, variableKey);

		return sectionData != nullptr;
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