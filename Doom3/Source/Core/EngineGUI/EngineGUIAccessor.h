#pragma once

namespace dooms
{
	class DObject;
	namespace ui
	{
		class EngineGUIAccessor
		{
		private:

			DObject* const mOwnerDObject;

			bool IsVisibleOnGUI = false;

		public:

			EngineGUIAccessor(DObject* const dObject);
			
			inline bool GetIsVisibleOnGUI() const
			{
				return IsVisibleOnGUI;
			}

			void SetIsVisibleOnGUI(const bool isVisible);
		};
	}
}

