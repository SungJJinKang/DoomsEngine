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

		class DOOM_API D_CLASS DEnum : public DType /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Enum * clEnum;

		public:

			DEnum(const UINT32 nameHash);

			/// <summary>
			/// if value doesn't exist, return nullptr
			/// </summary>
			/// <param name="value"></param>
			/// <param name="primitiveNameType"></param>
			/// <returns></returns>
			const char* GetNameOfEnumConstantsValue(const INT32 value, const dooms::reflection::ePrimitiveNameType primitiveNameType = dooms::reflection::ePrimitiveNameType::Short) const;

			// if value is found, return true
			const bool GetValue(const char* const valueName, INT32& result) const;

			FORCE_INLINE bool operator==(const DEnum& dEnum) const
			{
				return clEnum == dEnum.clEnum;
			}

			FORCE_INLINE bool operator!=(const DEnum& dEnum) const
			{
				return clEnum != dEnum.clEnum;
			}
		};

		template <typename T>
		extern DEnum CreateDEnum()
		{
			return DEnum(clcpp::GetTypeNameHash<T>());
		}
	}
}