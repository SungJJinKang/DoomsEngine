#pragma once

#include <vector>

namespace dooms
{
	class DObject;

	namespace reflection
	{
		class DFunction;
		class DClass;
		class DField;
	}

	namespace ui
	{
		namespace imguiWithReflection
		{
			extern void Initialize();

			extern void AddToVisibleOnGUIDObjectList(DObject* const dObject);
			extern void RemoveFromVisibleOnGUIDObjectList(DObject* const dObject);

			extern void UpdateGUI_DObjectsVisibleOnGUI();
		}
	}
}