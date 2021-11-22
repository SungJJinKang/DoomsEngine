#pragma once

#include <string>
#include <vector>

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
		class DAttribute;
		class DAttributeList;
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
				D_ASSERT(clField != nullptr);
			}

			FORCE_INLINE const char* GetFieldName() const
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

			FORCE_INLINE UINT32 GetFieldTypeHashValue() const
			{
				return clField->type->name.hash;
			}

			FORCE_INLINE size_t GetFieldTypeSize() const
			{
				return clField->type->size;
			}
			
			FORCE_INLINE const clcpp::Type* GetclTypeOfFieldType() const
			{
				return clField->type;
			}

			FORCE_INLINE eProperyQualifier GetFieldQualifier() const
			{
				return static_cast<eProperyQualifier>(clField->qualifier.op);
			}

			void* GetRawFieldValue(void* const dObject);

			template <typename RETURN_TYPE>
			FORCE_INLINE RETURN_TYPE* GetFieldValue(void* const dObject)
			{
				//D_ASSERT(dObject != nullptr);

				//clField->parent_unique_id
				//dObject->GetTypeHashVlue()


				// TODO : add Assert
				//D_ASSERT(sizeof(RETURN_TYPE) == GetFieldTypeSize(), "Wrong RETURN TYPE. Please Check Type. Type of DField = %s", GetFieldTypeName());

				RETURN_TYPE* returnedField = reinterpret_cast<RETURN_TYPE*>(GetRawFieldValue(dObject));
				
				return returnedField;
			}

			template <typename RETURN_TYPE>
			FORCE_INLINE const RETURN_TYPE* GetFieldValue(void* const dObject) const
			{
				//D_ASSERT(dObject != nullptr);

				//clField->parent_unique_id
				//dObject->GetTypeHashVlue()


				// TODO : add Assert
				//D_ASSERT(sizeof(RETURN_TYPE) == GetFieldTypeSize(), "Wrong RETURN TYPE. Please Check Type. Type of DField = %s", GetFieldTypeName());

				RETURN_TYPE* returnedField = reinterpret_cast<RETURN_TYPE*>(GetRawFieldValue(dObject));

				return returnedField;
			}

			/// <summary>
			/// if Setting field value success, return true
			///
			/// you can set only raw value.
			///
			///	you can't don this. ex) copy constructor, move constructor
			/// </summary>
			template <typename PARAMETER_TYPE>
			FORCE_INLINE bool SetValueToField(void* const dObject, const PARAMETER_TYPE& paramter)
			{
				void* const rawFieldPtr = GetRawFieldValue(dObject);

				D_ASSERT(rawFieldPtr != nullptr);

				if(rawFieldPtr != nullptr)
				{
					*reinterpret_cast<PARAMETER_TYPE*>(rawFieldPtr) = paramter;
					return true;
				}
				else
				{
					return false;
				}
				
			}

			FORCE_INLINE bool SetRawValueToField(void* const dObject, const void* parameter)
			{
				void* const rawFieldPtr = GetRawFieldValue(dObject);

				D_ASSERT(rawFieldPtr != nullptr);

				if (rawFieldPtr != nullptr)
				{
					std::memcpy(rawFieldPtr, parameter, GetFieldTypeSize());
					return true;
				}
				else
				{
					return false;
				}

			}

			std::string ToString(void* const dObject);

			FORCE_INLINE bool operator==(const DField& dField) const
			{
				return clField == dField.clField;
			}

			FORCE_INLINE bool operator!=(const DField& dField) const
			{
				return clField != dField.clField;
			}

			DAttributeList GetAttributeList() const;
		};
	}
}
