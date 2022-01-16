#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include "DType.h"

D_NAMESPACE(dooms)
namespace dooms
{
	
	class DObject;
	namespace reflection
	{
		class DAttributeList;

		class DOOM_API D_CLASS DEnum : public DType /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Enum * clEnum;

		public:

			DEnum(const UINT32 nameHash);
			DEnum(const char* const fullName);
			DEnum(const clcpp::Enum* const _clEnum);

			/// <summary>
			/// if value doesn't exist, return nullptr
			/// </summary>
			/// <param name="value"></param>
			/// <param name="primitiveNameType"></param>
			/// <returns></returns>
			const char* GetNameOfEnumConstantValue(const INT32 value, const dooms::reflection::ePrimitiveNameType primitiveNameType = dooms::reflection::ePrimitiveNameType::Short) const;
			const char* GetNameOfEnumConstantIndex(const size_t index, const dooms::reflection::ePrimitiveNameType primitiveNameType = dooms::reflection::ePrimitiveNameType::Short) const;

			// if value is found, return true
			const bool GetEnumConstantValue(const char* const valueName, INT32& result) const;
			const bool GetEnumConstantValue(const size_t index, INT32& result) const;

			size_t GetEnumConstantIndex(const char* const enumConstantName) const;
			size_t GetEnumConstantIndex(const INT32 value) const;

			size_t GetEnumConstantsCount() const;

			FORCE_INLINE bool operator==(const DEnum& dEnum) const
			{
				return clEnum == dEnum.clEnum;
			}

			FORCE_INLINE bool operator!=(const DEnum& dEnum) const
			{
				return clEnum != dEnum.clEnum;
			}

			DAttributeList GetDAttributeList() const;
		};

		template <typename T>
		extern DEnum CreateDEnum()
		{
			return DEnum(clcpp::GetTypeNameHash<T>());
		}
	}
}