#pragma once

#include <Doom_Core.h>

namespace doom
{
	class ExportTextureTester : public PlainComponent
	{

		DOBJECT_BODY(ExportTextureTester)

	protected:

		void InitComponent() override;
		void UpdateComponent() override;

	};
}
