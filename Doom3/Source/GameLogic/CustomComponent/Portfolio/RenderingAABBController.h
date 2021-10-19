#pragma once
#include <Doom_Core.h>



namespace doom
{
	class RenderingAABBController : public PlainComponent
	{

		DOBJECT_CLASS_BODY(RenderingAABBController)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	private:

	protected:

		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}
