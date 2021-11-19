#pragma once


#include <string>
#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include "Macros/Assert.h"

#include "../Reflection.h"

#include "DPrimitive.h"

namespace dooms
{
	class DObject;

	namespace reflection
	{

		class DOOM_API D_CLASS DField : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Field * clField;

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

			FORCE_INLINE const char* GetFieldVariableName() const
			{
				return dPrimitiveHelper::GetShortNamePointer(clField->name.text);
			}

			FORCE_INLINE int GetFieldOffset() const
			{
				return clField->offset;
			}

			FORCE_INLINE const char* GetFieldTypeName() const
			{
				return clField->type->name.text;
			}

			FORCE_INLINE UINT32 GetFieldTypeHashValue() const
			{
				return clField->type->name.hash;
			}

			FORCE_INLINE size_t GetFieldTypeSize() const
			{
				return clField->type->size;
			}

			FORCE_INLINE eProperyQualifier GetFieldQualifier() const
			{
				return static_cast<eProperyQualifier>(clField->qualifier.op);
			}

			FORCE_INLINE void* GetRawFieldValue(void* const dObject)
			{
				return reinterpret_cast<char*>(dObject) + clField->offset;
			}

			template <typename RETURN_TYPE>
			RETURN_TYPE* GetFieldValue(void* const dObject)
			{
				//D_ASSERT(dObject != nullptr);

				//clField->parent_unique_id
				//dObject->GetTypeHashVlue()


				// TODO : add Assert
				//D_ASSERT(sizeof(RETURN_TYPE) == GetFieldTypeSize(), "Wrong RETURN TYPE. Please Check Type. Type of DField = %s", GetFieldTypeName());

				RETURN_TYPE* returnedField = nullptr;

				returnedField = reinterpret_cast<RETURN_TYPE*>(GetRawFieldValue(dObject));

				return returnedField;
			}

			template <typename RETURN_TYPE>
			const RETURN_TYPE* GetFieldValue(void* const dObject) const
			{
				//D_ASSERT(dObject != nullptr);

				//clField->parent_unique_id
				//dObject->GetTypeHashVlue()


				// TODO : add Assert
				//D_ASSERT(sizeof(RETURN_TYPE) == GetFieldTypeSize(), "Wrong RETURN TYPE. Please Check Type. Type of DField = %s", GetFieldTypeName());

				RETURN_TYPE* returnedField = nullptr;

				returnedField = reinterpret_cast<RETURN_TYPE*>(GetRawFieldValue(dObject));

				return returnedField;
			}

			std::string ToString(void* const dObject);
		};
	}
}
