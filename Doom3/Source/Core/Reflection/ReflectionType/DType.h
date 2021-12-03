#pragma once

#include <Macros/Assert.h>
#include <Macros/DllMarcos.h>

#include "../Reflection.h"


#include "DPrimitive.h"


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DClass;
		class DTemplateType;
		class DEnum;
		class DOOM_API D_CLASS DType : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Type * clType;

		protected:


		public:

			FORCE_INLINE DType()
				: DPrimitive(nullptr), clType(nullptr)
			{

			}
			FORCE_INLINE DType(const clcpp::Type* const _clType)
				: DPrimitive(_clType), clType(_clType)
			{

			}
			DType(const char* const typeFullName);

			FORCE_INLINE const char* GetTypeFullName() const
			{
				return DPrimitive::GetPrimitiveFullName();
			}

			FORCE_INLINE size_t GetTypeSize() const
			{
				return clType->size;
			}

			FORCE_INLINE bool operator==(const DType& dType) const
			{
				return clType == dType.clType;
			}

			FORCE_INLINE bool operator!=(const DType& dType) const
			{
				return clType != dType.clType;
			}


			DClass AsDClass() const;
			DTemplateType AsDTemplateType() const;
			DEnum AsDEnum() const;
		};
	}
}