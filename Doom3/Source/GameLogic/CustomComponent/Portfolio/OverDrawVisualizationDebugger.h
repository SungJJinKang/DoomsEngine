#pragma once


#include <memory>

#include <Doom_Core.h>



namespace doom
{

	class OverDrawVisualizationDebugger : public PlainComponent
	{

	private:

	public:

		void InitComponent() override;
		void ShowIsSortObjectFrontToBack();
		void UpdateComponent() override;

	};
}
