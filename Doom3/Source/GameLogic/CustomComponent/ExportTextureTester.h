#pragma once

#include <DoomsGameLogicCore.h>

#include "ExportTextureTester.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS ExportTextureTester : public Component
	{
		GENERATE_BODY()
		
		

	protected:

		void InitComponent() override;
		void UpdateComponent() override;

	};
}
