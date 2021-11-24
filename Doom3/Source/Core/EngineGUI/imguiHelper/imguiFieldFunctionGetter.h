#pragma once

namespace dooms
{
	namespace reflection
	{
		class DAttributeList;
	}

	namespace ui
	{
		namespace imguiFieldFunctionGetter
		{
			using IMGUI_WITH_REFLECTION_FUNC =
				bool (*)(void* const object, const char* const label, const reflection::DAttributeList& attributeList);


			void Initialize();

			IMGUI_WITH_REFLECTION_FUNC GetImguiWithReflectionFunction(const char* const typeFullName);
		}
	}
}