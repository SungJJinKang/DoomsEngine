#pragma once

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include "Macros/Assert.h"

#include "../Reflection.h"

#include "DPrimitive.h"

namespace dooms
{
	class DObject;
	class DOOM_API D_STRUCT DProperty : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
	{
	protected:

		const clcpp::Field* clField;

	public:

		enum class eProperyQualifier
		{
			VALUE = clcpp::Qualifier::Operator::VALUE,
			POINTER = clcpp::Qualifier::Operator::POINTER,
			REFERENCE = clcpp::Qualifier::Operator::REFERENCE
		};

		FORCE_INLINE DProperty()
			: DPrimitive(), clField(nullptr)
		{
			
		}

		FORCE_INLINE DProperty(const clcpp::Field* const _clField)
			: DPrimitive(_clField), clField(_clField)
		{
			//D_ASSERT(clField != nullptr);
		}

		FORCE_INLINE const char* GetPropertyVariableFullName() const
		{
			return clField->name.text;
		}

		FORCE_INLINE int GetPropertyOffset() const
		{
			return clField->offset;
		}

		FORCE_INLINE size_t GetPropertyTypeSize() const
		{
			return clField->type->size;
		}

		FORCE_INLINE eProperyQualifier GetPropertyQualifier() const
		{
			return static_cast<eProperyQualifier>(clField->qualifier.op);
		}
		
		template <typename RETURN_TYPE>
		RETURN_TYPE* GetPropertyValue(dooms::DObject* const dObject) const
		{
			//D_ASSERT(dObject != nullptr);

			//clField->parent_unique_id
			//dObject->GetTypeHashVlue()

			RETURN_TYPE* returnedProperty = nullptr;
			
			returnedProperty = reinterpret_cast<RETURN_TYPE*>(reinterpret_cast<char*>(dObject) + clField->offset);

			return returnedProperty;
		}
	};
}
