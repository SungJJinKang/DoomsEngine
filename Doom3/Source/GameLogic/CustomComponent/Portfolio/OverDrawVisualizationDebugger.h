#pragma once


#include <Doom_Core.h>



namespace dooms
{

	class D_CLASS OverDrawVisualizationDebugger : public PlainComponent
	{

		DOBJECT_CLASS_BODY(OverDrawVisualizationDebugger)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	private:

	public:

		void InitComponent() override;
		void ShowIsSortObjectFrontToBack();
		void UpdateComponent() override;

	};
}
