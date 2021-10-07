#pragma once

#include <Doom_Core.h>



namespace doom
{
	namespace graphics
	{
		class PicktureInPickture;
	}

	class ViewFrustumCullingDebug : public PlainComponent
	{

	private:


	public:

		void InitComponent() override;

		void ShowIsViewFrustumCullingActivated();


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}
