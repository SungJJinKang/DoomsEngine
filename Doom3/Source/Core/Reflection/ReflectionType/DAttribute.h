#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include <vector>
#include <unordered_map>

#include "DPrimitive.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DOOM_API D_CLASS DAttribute : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{

		public:

			enum class AttributeType
			{
				Int = clcpp::Primitive::Kind::KIND_INT_ATTRIBUTE, // ex) attribute name = integer number
				Float = clcpp::Primitive::Kind::KIND_FLOAT_ATTRIBUTE, // ex) attribute name = float number
				Text = clcpp::Primitive::Kind::KIND_TEXT_ATTRIBUTE, // ex) attribute name = string
				Flag = clcpp::Primitive::Kind::KIND_FLAG_ATTRIBUTE, // ex) attribute name ( only string )


				// below : unused
				Enum = clcpp::Primitive::Kind::KIND_ENUM_CONSTANT, // ex) ~~ =
				Primitive = clcpp::Primitive::Kind::KIND_PRIMITIVE_ATTRIBUTE
			};

		private:

			const clcpp::Attribute* mclcppAttribute;

		public:

			FORCE_INLINE DAttribute(const clcpp::Attribute* const clcppAttribute)
				: DPrimitive(clcppAttribute), mclcppAttribute(clcppAttribute)
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT(
					(mclcppAttribute->kind == clcpp::Primitive::Kind::KIND_INT_ATTRIBUTE) ||
					(mclcppAttribute->kind == clcpp::Primitive::Kind::KIND_FLOAT_ATTRIBUTE) ||
					(mclcppAttribute->kind == clcpp::Primitive::Kind::KIND_TEXT_ATTRIBUTE) ||
					(mclcppAttribute->kind == clcpp::Primitive::Kind::KIND_FLAG_ATTRIBUTE)
				);
			}
			
			FORCE_INLINE const char* GetAttributeName() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT
				(
					(GetAttributeType() == AttributeType::Int) ||
					(GetAttributeType() == AttributeType::Float) ||
					(GetAttributeType() == AttributeType::Text) ||
					(GetAttributeType() == AttributeType::Flag)
				);

				return mclcppAttribute->name.text;
			}

			FORCE_INLINE const char* GetStringValue() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT(GetAttributeType() == AttributeType::Text);

				const char* str = "";
				const clcpp::TextAttribute* const textAttribute = mclcppAttribute->AsTextAttribute();
				if(textAttribute != nullptr)
				{
					str = textAttribute->value;
				}

				return str;
			}

			FORCE_INLINE float GetFloatValue() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT((GetAttributeType() == AttributeType::Float) || (GetAttributeType() == AttributeType::Int));

				const AttributeType attributeType = GetAttributeType();

				float value = 0.0f;

				if(attributeType == AttributeType::Float)
				{
					value = mclcppAttribute->AsFloatAttribute()->value;
				}
				else if(attributeType == AttributeType::Int)
				{
					// this is not best case. but accept it
					value = static_cast<float>(mclcppAttribute->AsIntAttribute()->value);
				}

				return value;
			}

			FORCE_INLINE int GetIntValue() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT((GetAttributeType() == AttributeType::Float) || (GetAttributeType() == AttributeType::Int));

				const AttributeType attributeType = GetAttributeType();

				int value = 0;

				if (attributeType == AttributeType::Float)
				{
					// this is not best case. but accept it
					value = static_cast<int>(mclcppAttribute->AsFloatAttribute()->value);
				}
				else if (attributeType == AttributeType::Int)
				{
					value = mclcppAttribute->AsIntAttribute()->value;
				}

				return value;
			}
			
			FORCE_INLINE AttributeType GetAttributeType() const
			{
				D_ASSERT(mclcppAttribute != nullptr);

				return static_cast<AttributeType>(mclcppAttribute->kind);
			}


		};
	}
}