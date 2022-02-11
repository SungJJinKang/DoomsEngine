#pragma once


#include <DoomsGameLogicCore.h>


#include "PhysicsDebuggerController.reflection.h"
namespace dooms
{

class DOOM_API D_CLASS PhysicsDebuggerController : public Component
{

	
	

private:

	

public:

	dooms::Entity* entity = nullptr;

	void InitComponent() override;
	void UpdateComponent() override;


};
}
