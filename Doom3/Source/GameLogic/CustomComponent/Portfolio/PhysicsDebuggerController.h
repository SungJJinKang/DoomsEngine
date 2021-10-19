#pragma once


#include <Doom_Core.h>



namespace doom
{

class PhysicsDebuggerController : public PlainComponent
{

	DOBJECT_CLASS_BODY(PhysicsDebuggerController)
	DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

private:

	

public:

	doom::Entity* entity = nullptr;

	void InitComponent() override;
	void UpdateComponent() override;


};
}
