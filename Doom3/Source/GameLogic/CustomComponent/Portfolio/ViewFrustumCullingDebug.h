#pragma once

#include <memory>

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

		std::shared_ptr<graphics::PicktureInPickture> PIP;

	public:

		void InitComponent() override;

		void ShowIsViewFrustumCullingActivated();


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}
