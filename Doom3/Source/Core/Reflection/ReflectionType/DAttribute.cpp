#include "DAttribute.h"

dooms::reflection::DAttribute::DAttribute(clcpp::Attribute* const clcppAttribute)
	: DPrimitive(clcppAttribute), mclcppAttribute(clcppAttribute)
{
	D_ASSERT(clcppAttribute != nullptr);
	D_ASSERT(
		clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_INT_ATTRIBUTE ||
		clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_FLOAT_ATTRIBUTE ||
		clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_TEXT_ATTRIBUTE ||
		clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_PRIMITIVE_ATTRIBUTE ||
		clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_FLAG_ATTRIBUTE
	);
}

std::string dooms::reflection::DAttribute::GetStringValue() const
{
	D_ASSERT(mclcppAttribute != nullptr);
	D_ASSERT(GetAttributeType() == AttributeType::Text);

	return mclcppAttribute->AsTextAttribute()->value;
}

float dooms::reflection::DAttribute::GetFloatValue() const
{
	D_ASSERT(mclcppAttribute != nullptr);
	D_ASSERT(GetAttributeType() == AttributeType::Float);

	return mclcppAttribute->AsFloatAttribute()->value;
}

int dooms::reflection::DAttribute::GetIntValue()
{
	D_ASSERT(mclcppAttribute != nullptr);
	D_ASSERT(GetAttributeType() == AttributeType::Int);

	return mclcppAttribute->AsIntAttribute()->value;
}

const char* dooms::reflection::DAttribute::GetAttributeLabel() const
{
	D_ASSERT(mclcppAttribute != nullptr);
	D_ASSERT
	(
		GetAttributeType() == AttributeType::Int ||
		GetAttributeType() == AttributeType::Float ||
		GetAttributeType() == AttributeType::Text
	);

	return mclcppAttribute->name.text;
}

dooms::reflection::DAttribute::AttributeType dooms::reflection::DAttribute::GetAttributeType() const
{
	D_ASSERT(mclcppAttribute != nullptr);
	D_ASSERT
	(
		GetAttributeType() == AttributeType::Int ||
		GetAttributeType() == AttributeType::Float ||
		GetAttributeType() == AttributeType::Text
	);

	return static_cast<AttributeType>(mclcppAttribute->kind);
}
