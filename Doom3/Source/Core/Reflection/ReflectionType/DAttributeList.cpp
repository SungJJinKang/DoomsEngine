#include "DAttributeList.h"

#include "DAttribute.h"

dooms::reflection::DAttributeList::DAttributeList(const std::vector<DAttribute>& attributes)
	: mDAttributeList(attributes)
{
}

dooms::reflection::DAttributeList::DAttributeList(std::vector<DAttribute>&& attributes) noexcept
	: mDAttributeList(std::move(attributes))
{
}

const dooms::reflection::DAttribute* dooms::reflection::DAttributeList::GetAttributeWithName(const char* const attributeName) const
{
	const dooms::reflection::DAttribute* dAttribute = nullptr;

	for(size_t i = 0 ; i < mDAttributeList.size() ; i++)
	{
		if(std::strcmp(mDAttributeList[i].GetAttributeName(), attributeName) == 0)
		{
			dAttribute = &(mDAttributeList[i]);
			break;
		}
	}

	return dAttribute;
}
