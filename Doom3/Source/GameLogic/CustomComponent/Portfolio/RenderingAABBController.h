#pragma once
#include <DoomsGameLogicCore.h>


#include "RenderingAABBController.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS RenderingAABBController : public Component
	{
		GENERATE_BODY()
		
		

	private:

	protected:

		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}
