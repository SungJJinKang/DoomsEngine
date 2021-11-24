#include "SimpleIniParser.h"
#include <fstream>
#include <regex>
#include <cstdlib>


#include <Core.h>

#include <trim.h>
#include <EngineGUI/PrintText.h>

static const std::regex sectionPattern{R"(\s*\[\s*(\S+)\s*\]\s*)"};
static const std::regex variablePattern{ R"(\s*(\S+)\s*=\s*(\S+)\s*)" };




bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && (std::isdigit(*it) || *it == '.')) ++it;
	return !s.empty() && it == s.end();
}

IniData SimpleIniParser::ParseIniFile(std::string fileDirectory)
{
	std::ifstream inputfStream{ fileDirectory };
	if (inputfStream.is_open() == false)
	{
		D_DEBUG_LOG(eLogType::D_LOG, "can't open Ini file : %s", fileDirectory.c_str());
		return {};
	}

	/// <summary>
	/// unordered_map
	/// key : section
	/// value : Variable
	/// 
	/// vector elements : Variable of section
	/// key : Variable name
	/// value : Variable Value
	/// </summary>
	/// <param name="fileDirectory"></param>
	IniData iniData;
	
	std::string line;

	std::string currentSection{};

	while (std::getline(inputfStream, line))
	{
		if(line.empty())
			continue;

		line = std::trim(line, ' ');

		if (line.empty())
			continue;

		const char& front = line.front();
		
		switch (front)
		{
		case '#':
		case ';':
			continue;
			break;

		case '[':
		{
			std::smatch matches;
			if (std::regex_search(line, matches, sectionPattern, std::regex_constants::match_flag_type::match_default))
			{
				currentSection = matches[1];
				iniData.AddSection(currentSection);
			}
			break;
		}


		default:
		{
			std::smatch matches;
			if (std::regex_search(line, matches, variablePattern, std::regex_constants::match_flag_type::match_default))
			{
				IniData::ini_data_type value;

				std::string valueStr = matches[2].str();
				size_t commnetPos = valueStr.find_first_of("//");
				if (commnetPos != std::string::npos)
				{
					valueStr.resize(commnetPos);
				}
				valueStr = std::trim(valueStr, ' ');
				valueStr = std::trim(valueStr, ';');

				

				std::string upperStr{};
				upperStr.resize(valueStr.size());
				std::transform(valueStr.begin(), valueStr.end(), upperStr.begin(), ::toupper);
		
				if (valueStr.size() == 1 && valueStr == "0")
				{
					value = 0;
				}
				else if (upperStr == "TRUE")
				{
					value = true;
				}
				else if (upperStr == "FALSE")
				{
					value = false;
				}
				else if (is_number(valueStr))
				{
					double d = std::stod(valueStr);
					if (valueStr.find('.') != std::string::npos)
					{
						value = d;
					}
					else
					{
						value = static_cast<int>(d);
					}
				}
				else
				{
					value = valueStr;
				}

				iniData.InsertVariable(currentSection, matches[1], value);
			}
			break;
		}
		}
	}

	return iniData;
}

const IniData::ini_data_type* IniData::GetSectionData(const std::string& sectionKey, const std::string& variableKey) const
{
	const IniData::ini_data_type* sectionData = nullptr;

	auto sectionIter = mIniDatas.find(sectionKey);

	D_ASSERT_LOG(sectionIter != mIniDatas.end(), "Can't Find Section : %s", sectionKey.c_str());
	if(sectionIter != mIniDatas.end())
	{
		auto sectionDataIter = sectionIter->second.find(variableKey);

		if (sectionDataIter != sectionIter->second.end())
		{
			sectionData = &(sectionDataIter->second);
		}

		D_ASSERT_LOG(sectionData != nullptr, "Can't Find Section Data ( SectionKey : %s, DataKey : %s )", sectionKey.c_str(), variableKey.c_str());
	}

	if(sectionData == nullptr)
	{
		dooms::ui::PrintText("Fail to Find Data ( SectionKey : %s, DataKey : %s )", sectionKey.c_str(), variableKey.c_str());
	}

	return sectionData;
}

void IniData::AddSection(const std::string& section)
{
	mIniDatas[section]; // just accessing to unordered_map with key make hash table
	dooms::ui::PrintText("Add New Section : %s", section.c_str());
}

struct ConverToString
{
	std::string operator()(const std::string& str )
	{
		return str;
	}
	std::string operator()(int str)
	{
		return std::to_string(str);
	}
	std::string operator()(double str)
	{
		return std::to_string(str);
	}
};


void IniData::InsertVariable(const std::string& section, const std::string& key, ini_data_type data)
{
	auto IsInsert = mIniDatas[section].insert_or_assign(key, data);
	D_ASSERT(IsInsert.second == true); // if already key is exsist, make exeption

	/*
	* //Evaluated at compile time
	auto sdf = std::visit([](auto&& arg) {
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, std::string>)
			return arg;
		else if constexpr (std::is_arithmetic_v<T>)
			return std::to_string(arg);
		else
			static_assert(std::false_type, "non-exhaustive visitor!");
		}, variable.second);
	*/
	auto valueString = std::visit(ConverToString(), data);
	dooms::ui::PrintText("Add New Variable : Section ( %s ), Key( %s ), Value( %s ) ", section.c_str(), key.c_str(), valueString.c_str());

	
}

