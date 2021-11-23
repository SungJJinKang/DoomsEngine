#include "DAttributeList.h"

#include <utility>

#include "DAttribute.h"
#include "imgui.h"

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
		// case-insensitive check
		if(_stricmp(mDAttributeList[i].GetAttributeName(), attributeName) == 0)
		{
			dAttribute = &(mDAttributeList[i]);
			break;
		}
	}

	return dAttribute;
}

ImVec4 dooms::reflection::DAttributeList::GetTextColor() const
{
	static const std::pair<const char* const, ImVec4> ColorNameMap[]
	{
		{"BLACK", ImVec4{0.0f, 0.0f, 0.0f, 1.0f}},
		{"WHITE", ImVec4{1.0f, 1.0f, 0.0f, 1.0f}},
		{"RED", ImVec4{1.0f, 0.0f, 0.0f, 1.0f}},
		{"GREEN", ImVec4{0.0f, 1.0f, 0.0f, 1.0f}},
		{"BLUE", ImVec4{0.0f, 0.0f, 1.0f, 1.0f}},
	};

	ImVec4 color = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };

	const dooms::reflection::DAttribute* const textColor = GetAttributeWithName("TEXTCOLOR");
	
	if(textColor != nullptr)
	{
		D_ASSERT(textColor->GetAttributeType() == DAttribute::AttributeType::Text);

		const char* const textColorStr = textColor->GetStringValue();
		//this is slow.
		// but slowness of gui is acceptable



		bool isSuccess = false;

		for (size_t i = 0; i < sizeof(ColorNameMap) / sizeof(ColorNameMap[0]) ; i++)
		{
			// case-insensitive check
			if (_stricmp(textColorStr, ColorNameMap[i].first) == 0)
			{
				color = ColorNameMap[i].second;
				isSuccess = true;
				break;
			}
		}

		D_ASSERT_LOG(isSuccess == true, "Fail to find appropriate color from textColor attribute ( Imput Color Attribute Text : %s )", textColor->GetStringValue());
	}

	return color;
}

bool dooms::reflection::DAttributeList::GetIsVisibleOnGUI() const
{
	bool isVisible = true; // default : true

	const dooms::reflection::DAttribute* isVisibleAttribute = GetAttributeWithName("ISVISIBLE");
	if(isVisibleAttribute == nullptr)
	{
		isVisibleAttribute = GetAttributeWithName("VISIBLE");
	}
	if (isVisibleAttribute == nullptr)
	{
		isVisibleAttribute = GetAttributeWithName("INVISIBLE");
	}

	if (isVisibleAttribute != nullptr)
	{
		D_ASSERT
		(
			(isVisibleAttribute->GetAttributeType() == DAttribute::AttributeType::Text) ||
			(isVisibleAttribute->GetAttributeType() == DAttribute::AttributeType::Flag)
		);

		if(isVisibleAttribute->GetAttributeType() == DAttribute::AttributeType::Text)
		{
			const char* const textColorStr = isVisibleAttribute->GetStringValue();

			// case-insensitive check
			if (_stricmp(textColorStr, "TRUE") == 0)
			{
				isVisible = true;
			}
			else if (_stricmp(textColorStr, "FALSE") == 0)
			{
				isVisible = false;
			}
			else
			{
				D_ASSERT_LOG(false, "Worng attribute value from INVISIBLE Attribute ( Input value : %s )", textColorStr);
			}
		}
		else
		{
			if(_stricmp(isVisibleAttribute->GetAttributeName(), "VISIBLE") == 0)
			{
				isVisible = true;
			}
			else 	if (_stricmp(isVisibleAttribute->GetAttributeName(), "INVISIBLE") == 0)
			{
				isVisible = false;
			}
		}
		
	}

	return isVisible;
}

bool dooms::reflection::DAttributeList::GetIsHasGUIType(const char* const typeName) const
{
	bool isHasGUIType = false;

	const dooms::reflection::DAttribute* const guiTypeAttribute = GetAttributeWithName(typeName);
	if (guiTypeAttribute != nullptr)
	{
		isHasGUIType = true;		
	}

	return isHasGUIType;
}

bool dooms::reflection::DAttributeList::GetIsReadOnly() const
{
	bool isReadOnly = false; 
	
	const dooms::reflection::DAttribute* isVisibleAttribute = GetAttributeWithName("READONLY");

	if (isVisibleAttribute != nullptr)
	{
		D_ASSERT((isVisibleAttribute->GetAttributeType() == DAttribute::AttributeType::Flag));

		isReadOnly = true;

	}

	return isReadOnly;
}

float dooms::reflection::DAttributeList::GetMinValue() const
{
	float minValue = FLOAT32_MIN; // 0.0f mean infinity

	const dooms::reflection::DAttribute* minAttribute = GetAttributeWithName("MIN");
	if(minAttribute == nullptr)
	{
		minAttribute = GetAttributeWithName("MINVALUE");
	}
	if (minAttribute == nullptr)
	{
		minAttribute = GetAttributeWithName("MIN_VALUE");
	}

	if (minAttribute != nullptr)
	{
		minValue = minAttribute->GetFloatValue();
	}

	return minValue;
}

float dooms::reflection::DAttributeList::GetMaxValue() const
{
	float maxValue = FLOAT32_MAX; // 0.0f mean infinity

	const dooms::reflection::DAttribute* maxAttribute = GetAttributeWithName("MAX");
	if (maxAttribute == nullptr)
	{
		maxAttribute = GetAttributeWithName("MAXVALUE");
	}
	if (maxAttribute == nullptr)
	{
		maxAttribute = GetAttributeWithName("MAX_VALUE");
	}

	if (maxAttribute != nullptr)
	{
		maxValue = maxAttribute->GetFloatValue();
	}

	return maxValue;
}
