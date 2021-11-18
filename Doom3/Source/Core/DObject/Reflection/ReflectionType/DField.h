#pragma once

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include "Macros/Assert.h"

#include "../Reflection.h"

#include "DPrimitive.h"

namespace dooms
{
	class DObject;
	class DOOM_API D_STRUCT DField : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
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

		FORCE_INLINE DField()
			: DPrimitive(), clField(nullptr)
		{
			
		}

		FORCE_INLINE DField(const clcpp::Field* const _clField)
			: DPrimitive(_clField), clField(_clField)
		{
			//D_ASSERT(clField != nullptr);
		}

		FORCE_INLINE const char* GetFieldVariableFullName() const
		{
			return clField->name.text;
		}

		FORCE_INLINE int GetFieldOffset() const
		{
			return clField->offset;
		}

		FORCE_INLINE const char* GetFieldTypeName() const
		{
			return clField->type->name.text;
		}

		FORCE_INLINE const char* GetFieldTypeHashValue() const
		{
			return clField->type->name.text;
		}

		FORCE_INLINE size_t GetFieldTypeSize() const
		{
			return clField->type->size;
		}

		FORCE_INLINE eProperyQualifier GetFieldQualifier() const
		{
			return static_cast<eProperyQualifier>(clField->qualifier.op);
		}
		
		template <typename RETURN_TYPE>
		RETURN_TYPE* GetFieldValue(dooms::DObject* const dObject) const
		{
			//D_ASSERT(dObject != nullptr);

			//clField->parent_unique_id
			//dObject->GetTypeHashVlue()

			//D_ASSERT(sizeof(RETURN_TYPE) == GetFieldTypeSize(), "Wrong RETURN TYPE. Please Check Type. Type of DField = %s", GetFieldTypeName());

			RETURN_TYPE* returnedField = nullptr;
			
			returnedField = reinterpret_cast<RETURN_TYPE*>(reinterpret_cast<char*>(dObject) + clField->offset);

			return returnedField;
		}
	};
}
