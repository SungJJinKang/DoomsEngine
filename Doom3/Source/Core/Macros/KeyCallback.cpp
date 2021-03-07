#include "KeyCallback.h"

#include "../IO/UserInput_Server.h"

bool GetToogle(int keyCode)
{
	return doom::userinput::UserInput_Server::GetKeyToggle(static_cast<doom::userinput::eKEY_CODE>(keyCode));
}