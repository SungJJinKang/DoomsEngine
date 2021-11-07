#pragma once


#include <Doom_Core.h>



namespace dooms
{

class PhysicsDebuggerController : public PlainComponent
{

	DOBJECT_CLASS_BODY(PhysicsDebuggerController)
	DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

private:

	

public:

	dooms::Entity* entity = nullptr;

	void InitComponent() override;
	void UpdateComponent() override;


};
}
