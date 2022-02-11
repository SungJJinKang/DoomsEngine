#pragma once

#include <DoomsGameLogicCore.h>

#include "Test/GCTestDObject.h"

#include "TestComponent.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS TestComponent : public Component
	{
		GENERATE_BODY()
		
		

	private:

		D_PROPERTY()
		dooms::GCTestDObject* mGCTestDObject = nullptr;

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
