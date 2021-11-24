#pragma once

#include <Macros/DllMarcos.h>
#include <Macros/Assert.h>

#include "../Reflection.h"


namespace dPrimitiveHelper
{
	// return short name
	// ex) dooms::graphics::GraphicsServer -> GraphicsServer
	// ex) dooms::graphics::eClor::Red -> Red
	const char* GetShortNamePointer(const char* const name);
}


D_NAMESPACE(dooms)
namespace dooms
{
	

	class DObject;

	namespace reflection
	{
		enum class ePrimitiveNameType
		{
			Full,
			Short
		};

		class DOOM_API D_CLASS DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{
		public:

			enum class ePrimitiveType
			{
				NONE = clcpp::Primitive::KIND_NONE,
				ATTRIBUTE = clcpp::Primitive::KIND_ATTRIBUTE,
				FLAG_ATTRIBUTE = clcpp::Primitive::KIND_FLAG_ATTRIBUTE,
				INT_ATTRIBUTE = clcpp::Primitive::KIND_INT_ATTRIBUTE,
				FLOAT_ATTRIBUTE = clcpp::Primitive::KIND_FLOAT_ATTRIBUTE,
				PRIMITIVE_ATTRIBUTE = clcpp::Primitive::KIND_PRIMITIVE_ATTRIBUTE,
				TEXT_ATTRIBUTE = clcpp::Primitive::KIND_TEXT_ATTRIBUTE,
				TYPE = clcpp::Primitive::KIND_TYPE,
				ENUM_CONSTANT = clcpp::Primitive::KIND_ENUM_CONSTANT,
				ENUM = clcpp::Primitive::KIND_ENUM,
				FIELD = clcpp::Primitive::KIND_FIELD,
				FUNCTION = clcpp::Primitive::KIND_FUNCTION,
				TEMPLATE_TYPE = clcpp::Primitive::KIND_TEMPLATE_TYPE,
				TEMPLATE = clcpp::Primitive::KIND_TEMPLATE,
				CLASS = clcpp::Primitive::KIND_CLASS,
				NAMESPACE = clcpp::Primitive::KIND_NAMESPACE,
			};

		protected:

			const clcpp::Primitive* clPrimitive;
			
		protected:

			FORCE_INLINE DPrimitive()
				: clPrimitive(nullptr)
			{
			}


			FORCE_INLINE DPrimitive(const clcpp::Primitive* const _clPrimitive)
				: clPrimitive(_clPrimitive)
			{
			}


		public:

			FORCE_INLINE bool IsValid() const
			{
				return clPrimitive != nullptr;
			}

			FORCE_INLINE const char* GetPrimitiveFullName() const
			{
				return clPrimitive->name.text;
			}

			FORCE_INLINE const char* GetPrimitiveName() const
			{
				return dPrimitiveHelper::GetShortNamePointer(clPrimitive->name.text);
			}

			FORCE_INLINE UINT32 GetPrimitiveHashValue() const
			{
				return clPrimitive->name.hash;
			}

			FORCE_INLINE const char* GetParentFullName() const
			{
				if (clPrimitive->parent != nullptr)
				{
					return clPrimitive->parent->name.text;
				}
				else
				{
					return nullptr;
				}
			}

			


			FORCE_INLINE bool Equal(const DPrimitive& dPrimitive) const
			{
				return clPrimitive == dPrimitive.clPrimitive;
			}

			FORCE_INLINE bool operator==(const DPrimitive& dPrimitive) const
			{
				return clPrimitive == dPrimitive.clPrimitive;
			}

			FORCE_INLINE bool operator!=(const DPrimitive& dPrimitive) const
			{
				return clPrimitive != dPrimitive.clPrimitive;
			}

			FORCE_INLINE ePrimitiveType GetPrimitiveType() const
			{
				return static_cast<ePrimitiveType>(clPrimitive->kind);
			}
		};
	}
}