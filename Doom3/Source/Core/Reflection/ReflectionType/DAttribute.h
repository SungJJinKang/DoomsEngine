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
			enum class AttributeType
			{
				Int = clcpp::Primitive::Kind::KIND_INT_ATTRIBUTE,
				Float = clcpp::Primitive::Kind::KIND_FLOAT_ATTRIBUTE,
				Text = clcpp::Primitive::Kind::KIND_TEXT_ATTRIBUTE
			};

		private:

			clcpp::Attribute * mclcppAttribute;

		public:

			FORCE_INLINE DAttribute(clcpp::Attribute* const clcppAttribute)
				: DPrimitive(clcppAttribute), mclcppAttribute(clcppAttribute)
			{
				D_ASSERT(clcppAttribute != nullptr);
				D_ASSERT(
					clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_INT_ATTRIBUTE ||
					clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_FLOAT_ATTRIBUTE ||
					clcppAttribute->KIND == clcpp::Primitive::Kind::KIND_TEXT_ATTRIBUTE
				);
			}
			
			FORCE_INLINE const char* GetAttributeName() const
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

			FORCE_INLINE const char* GetStringValue() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT(GetAttributeType() == AttributeType::Text);

				return mclcppAttribute->AsTextAttribute()->value;
			}

			FORCE_INLINE float GetFloatValue() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT(GetAttributeType() == AttributeType::Float);

				return mclcppAttribute->AsFloatAttribute()->value;
			}

			FORCE_INLINE int GetIntValue() const
			{
				D_ASSERT(mclcppAttribute != nullptr);
				D_ASSERT(GetAttributeType() == AttributeType::Int);

				return mclcppAttribute->AsIntAttribute()->value;
			}
			
			FORCE_INLINE AttributeType GetAttributeType() const
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


		};
	}
}