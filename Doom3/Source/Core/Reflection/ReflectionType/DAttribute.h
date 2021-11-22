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

			DAttribute(clcpp::Attribute* const clcppAttribute);

			// We use only below four type attribute
			std::string GetStringValue() const;
			float GetFloatValue() const;
			int GetIntValue();

			const char* GetAttributeLabel() const;
			AttributeType GetAttributeType() const;

		};
	}
}