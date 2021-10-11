#include "KEY_CODE.h"

#include <Doom_Core.h>

#include "UserInputHelper.h"

template<> doom::userinput::eKEY_CODE IniData::GetValue<doom::userinput::eKEY_CODE>(const std::string& section, const std::string& variableKey) const
{
	auto sectionData = GetSectionData(section, variableKey);

	D_ASSERT(sectionData != nullptr);
	if(sectionData != nullptr)
	{
		return 	doom::userinput::UserInputHelper::ConvertStringToKeyCode(std::get<std::string>(*sectionData));
	}
	else
	{
		return doom::userinput::eKEY_CODE::ERROR_CODE;
	}
}