#pragma once

namespace dooms
{
	class DObject;
	namespace ui
	{
		class EngineGUIAccessor
		{
			friend class dooms::DObject;

		private:

			bool mIsAddedToRootObjectList;

			DObject* mOwnerDObject;

			bool mIsVisibleOnGUI = false;
			
			void SetOwnerObject(DObject* const dObject);


			EngineGUIAccessor(DObject* const dObject);

			EngineGUIAccessor(const EngineGUIAccessor&) = delete;
			EngineGUIAccessor(EngineGUIAccessor&&) noexcept = delete;

			EngineGUIAccessor& operator=(const EngineGUIAccessor&) = delete;
			EngineGUIAccessor& operator=(EngineGUIAccessor&&) noexcept = delete;

		public:


			inline bool GetIsVisibleOnGUI() const
			{
				return mIsVisibleOnGUI;
			}

			void SetIsVisibleOnGUI(const bool isVisible);
			
		};
	}
}

