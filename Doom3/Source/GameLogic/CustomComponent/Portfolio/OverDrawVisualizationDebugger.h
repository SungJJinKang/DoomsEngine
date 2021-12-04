#pragma once


#include <Doom_Core.h>


#include "OverDrawVisualizationDebugger.reflection.h"
namespace dooms
{

	class DOOM_API D_CLASS OverDrawVisualizationDebugger : public Component
	{
		GENERATE_BODY()
		
		

	private:

	public:

		void InitComponent() override;
		void ShowIsSortObjectFrontToBack();
		void UpdateComponent() override;

	};
}
