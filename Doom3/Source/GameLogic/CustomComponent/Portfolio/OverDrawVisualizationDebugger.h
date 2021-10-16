#pragma once


#include <Doom_Core.h>



namespace doom
{

	class OverDrawVisualizationDebugger : public PlainComponent
	{

		DOBJECT_BODY(OverDrawVisualizationDebugger)

	private:

	public:

		void InitComponent() override;
		void ShowIsSortObjectFrontToBack();
		void UpdateComponent() override;

	};
}
