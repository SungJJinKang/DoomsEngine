#pragma once

#include <type_traits>

#include "Macros/TypeDef.h"
#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include "../../DObject.h"

namespace dooms
{
	struct DOOM_API D_STRUCT DProperty /*: public dooms::DObject*/ // Dont Do this
	{
		enum class eProperyQualifier
		{
			VALUE = clcpp::Qualifier::Operator::VALUE,
			POINTER = clcpp::Qualifier::Operator::POINTER,
			REFERENCE = clcpp::Qualifier::Operator::REFERENCE
		};

		const clcpp::Field* const clField;


		DProperty(const clcpp::Field* const _clField)
			: clField(_clField)
		{
		}

		const char* GetPropertyVariableFullName() const
		{
			return clField->name.text;
		}

		int GetPropertyOffset() const
		{
			return clField->offset;
		}

		size_t GetPropertyTypeSize() const
		{
			return clField->type->size;
		}

		eProperyQualifier GetPropertyQualifier() const
		{
			return static_cast<eProperyQualifier>(clField->qualifier.op);
		}
		
		template <typename RETURN_TYPE>
		RETURN_TYPE* GetPropertyValue(dooms::DObject* const dObject)
		{
			D_ASSERT(dObject != nullptr);

			//clField->parent_unique_id
			//dObject->GetTypeHashVlue()

			RETURN_TYPE* returnedProperty = nullptr;
			
			returnedProperty = reinterpret_cast<RETURN_TYPE*>(dObject + clField->offset);

			return returnedProperty;
		}
	};
}
