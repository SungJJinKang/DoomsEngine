#pragma once

#include <utility>
#include <string>
#include <type_traits>

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
			static_assert(!std::is_same<T, T>::value, "Unsupported Type for config value");
			return T{};
		}

		template<>
		bool GetValue<bool>(const std::string& SectionName, const std::string& KeyName) const;
		
		template<>
		INT64 GetValue<INT64>(const std::string& SectionName, const std::string& KeyName) const;
		
		template<>
		FLOAT64 GetValue<FLOAT64>(const std::string& SectionName, const std::string& KeyName) const;

		template<>
		std::string GetValue<std::string>(const std::string& SectionName, const std::string& KeyName) const;

	private:

		dooms::GeneralConfigurationValue* GetConfigurationValue(const std::string& SectionName, const std::string& KeyName) const;
	};

}