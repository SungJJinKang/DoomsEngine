#pragma once

#include <DoomsGameLogicCore.h>


#include "ViewFrustumCullingDebug.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class PicktureInPickture;
	}

	class DOOM_API D_CLASS ViewFrustumCullingDebug : public Component
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
