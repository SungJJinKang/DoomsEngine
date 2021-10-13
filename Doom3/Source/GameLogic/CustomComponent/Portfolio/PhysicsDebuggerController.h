#pragma once


#include <Doom_Core.h>



namespace doom
{

class PhysicsDebuggerController : public PlainComponent
{

private:

	

public:

	doom::Entity* entity = nullptr;

	void InitComponent() override;
	void UpdateComponent() override;


};
}
