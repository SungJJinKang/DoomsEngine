#pragma once

#include <Doom_Core.h>


#include "ViewFrustumCullingDebug.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class PicktureInPickture;
	}

	class DOOM_API D_CLASS ViewFrustumCullingDebug : public PlainComponent
	{
		GENERATE_BODY()
		
		

	private:


	public:

		void InitComponent() override;

		void ShowIsViewFrustumCullingActivated();


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}
