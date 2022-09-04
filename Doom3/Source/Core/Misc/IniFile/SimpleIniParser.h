#pragma once

#include <utility>
#include <string>
#include <variant>
#include <unordered_map>

#include "Macros/Assert.h"
#include "Macros/TypeDef.h"


namespace dooms
{
	class GeneralConfigurationValue;

	class IniData
	{

	public:

		template <typename T>
		T GetValue(const std::string& SectionName, const std::string& KeyName) const
		{
			D_ASSERT_LOG(false, "Unsupported Type for config value");
			return T{};
		}

		template<>
		bool GetValue<bool>(const std::string& SectionName, const std::string& KeyName) const;

		template<>
		INT32 GetValue<INT32>(const std::string& SectionName, const std::string& KeyName) const;

		template<>
		INT64 GetValue<INT64>(const std::string& SectionName, const std::string& KeyName) const;

		template<>
		FLOAT32 GetValue<FLOAT32>(const std::string& SectionName, const std::string& KeyName) const;

		template<>
		FLOAT64 GetValue<FLOAT64>(const std::string& SectionName, const std::string& KeyName) const;

		template<>
		std::string GetValue<std::string>(const std::string& SectionName, const std::string& KeyName) const;

	private:

		dooms::GeneralConfigurationValue* GetConfigurationValue(const std::string& SectionName, const std::string& KeyName) const;
	};

}