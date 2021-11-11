#pragma once

#include <Doom_Core.h>



namespace dooms
{
	namespace graphics
	{
		class PicktureInPickture;
	}

	class D_CLASS ViewFrustumCullingDebug : public PlainComponent
	{

		DOBJECT_CLASS_BODY(ViewFrustumCullingDebug)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	private:


	public:

		void InitComponent() override;

		void ShowIsViewFrustumCullingActivated();


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}
