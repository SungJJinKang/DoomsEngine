#pragma once

#include <Doom_Core.h>

#include "ExportTextureTester.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS ExportTextureTester : public PlainComponent
	{
		GENERATE_BODY()
		
		

	protected:

		void InitComponent() override;
		void UpdateComponent() override;

	};
}
