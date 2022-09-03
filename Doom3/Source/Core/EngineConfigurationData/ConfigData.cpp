#include "ConfigData.h"

#include <fstream>
#include <regex>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <memory>

#include <Misc/String/trim.h>
#include <EngineGUI/PrintText.h>

#include "EngineConfigurationData/ConfigData.h"

static const std::regex sectionPattern{ R"(\s*\[\s*(\S+)\s*\]\s*)" };
static const std::regex variablePattern{ R"(\s*(\S+)\s*=\s*(\S+)\s*)" };

static std::vector<std::shared_ptr<dooms::GeneralConfigurationValue>> IniConfigValueList{};

void dooms::ConfigData::RegisterConfigValue()
{
	std::string FileDirectory = dooms::path::_GetAssetFolderDirectory() + "config.ini";
	std::ifstream InputfStream{ std::filesystem::u8path(FileDirectory) };
	if (InputfStream.is_open() == false)
	{
		D_DEBUG_LOG(eLogType::D_LOG, "can't open Ini file : %s", FileDirectory.c_str());
	}

	auto IsNumberFunc = [](const std::string& s) -> bool
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && (std::isdigit(*it) || *it == '.')) ++it;
		return !s.empty() && it == s.end();
	};

	std::string CurrentLine;
	std::string LastCategory{};

	while (std::getline(InputfStream, CurrentLine))
	{
		if (CurrentLine.empty())
			continue;

		CurrentLine = std::trim(CurrentLine, ' ');

		if (CurrentLine.empty())
			continue;

		const char& front = CurrentLine.front();
		
		switch (front)
		{
			case '#':
			case ';':
			{
				continue;
				break;
			}
			case '[':
			{
				std::smatch matches;
				if (std::regex_search(CurrentLine, matches, sectionPattern, std::regex_constants::match_flag_type::match_default))
				{
					LastCategory = matches[1];
				}
				break;
			}
			default:
			{
				std::smatch matches;
				if (std::regex_search(CurrentLine, matches, variablePattern, std::regex_constants::match_flag_type::match_default))
				{
					std::string ValueString = matches[2].str();
					size_t DoubleSlashPos = ValueString.find_first_of("//");
					if (DoubleSlashPos != std::string::npos)
					{
						ValueString.resize(DoubleSlashPos);
					}
					ValueString = std::trim(ValueString, ' ');
					ValueString = std::trim(ValueString, ';');

					std::string UpperValueString{};
					UpperValueString.resize(ValueString.size());
					std::transform(ValueString.begin(), ValueString.end(), UpperValueString.begin(), ::toupper);

					GeneralConfigurationValue* ConfigurationValue{ nullptr };

					if (ValueString.size() == 1 && ValueString == "0")
					{
						TCvar<INT64>* CVar = new TCvar<INT64>(LastCategory, matches[1].str() , "", 0 );
						ConfigurationValue = reinterpret_cast<GeneralConfigurationValue*>(CVar);
					}
					else if (UpperValueString == "TRUE")
					{
						TCvar<bool>* CVar = new TCvar<bool>( LastCategory, matches[1].str() , "", true );
						ConfigurationValue = reinterpret_cast<GeneralConfigurationValue*>(CVar);
					}
					else if (UpperValueString == "FALSE")
					{
						TCvar<bool>* CVar = new TCvar<bool>(LastCategory, matches[1].str() , "", false );
						ConfigurationValue = reinterpret_cast<GeneralConfigurationValue*>(CVar);
					}
					else if (IsNumberFunc(ValueString))
					{
						FLOAT64 Number = std::stod(ValueString);
						if (ValueString.find('.') != std::string::npos)
						{
							TCvar<FLOAT64>* CVar = new TCvar<FLOAT64>( LastCategory, matches[1].str() , "", Number );
							ConfigurationValue = reinterpret_cast<GeneralConfigurationValue*>(CVar);
						}
						else
						{
							TCvar<INT64>* CVar = new TCvar<INT64>(LastCategory, matches[1].str() , "", static_cast<INT64>(Number));
							ConfigurationValue = reinterpret_cast<GeneralConfigurationValue*>(CVar);
						}
					}
					else
					{
						TCvar<std::string>* CVar = new TCvar<std::string>(LastCategory, matches[1].str() , "", ValueString );
						ConfigurationValue = reinterpret_cast<GeneralConfigurationValue*>(CVar);
					}

					if (ConfigurationValue != nullptr)
					{
						IniConfigValueList.push_back(std::unique_ptr<dooms::GeneralConfigurationValue>{ConfigurationValue});
					}
				}
				break;
			}
		}
	}
}

dooms::ConfigData::ConfigData()
	: mConfigData()
{
	RegisterConfigValue();
}

dooms::IniData& dooms::ConfigData::GetConfigData()
{
	return mConfigData;
}
