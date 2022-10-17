#pragma once

#include <Reflection/ReflectionType/DPrimitive.h>
#include <Reflection/ReflectionType/ePropertyQualifier.h>

namespace dooms
{
	namespace reflection
	{
		class DType;
		class DAttributeList;
	}

	namespace ui
	{
		namespace imguiFieldFunctionGetter
		{
			using IMGUI_WITH_REFLECTION_FUNC =
				bool (*)(
					void* const object, 
					const char* const label,
					const char* const typeFullName,
					const reflection::eProperyQualifier dataQualifier,
					const reflection::DAttributeList& attributeList, 
					const reflection::DType* const fieldDType
					);


			void Initialize();

			IMGUI_WITH_REFLECTION_FUNC GetImguiWithReflectionFunction
			(
				const char* const typeFullName,
				const reflection::eProperyQualifier valueQualifier,
				const reflection::DType* const fieldDType
			);
		}
	}
}