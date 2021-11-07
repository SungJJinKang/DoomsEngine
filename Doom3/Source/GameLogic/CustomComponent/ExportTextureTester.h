#pragma once

#include <Doom_Core.h>

namespace dooms
{
	class ExportTextureTester : public PlainComponent
	{

		DOBJECT_CLASS_BODY(ExportTextureTester)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	protected:

		void InitComponent() override;
		void UpdateComponent() override;

	};
}
