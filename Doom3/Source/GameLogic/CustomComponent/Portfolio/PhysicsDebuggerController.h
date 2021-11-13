#pragma once


#include <Doom_Core.h>


#include "PhysicsDebuggerController.reflection.h"
namespace dooms
{

class DOOM_API D_CLASS PhysicsDebuggerController : public PlainComponent
{

	
	

private:

	

public:

	dooms::Entity* entity = nullptr;

	void InitComponent() override;
	void UpdateComponent() override;


};
}
