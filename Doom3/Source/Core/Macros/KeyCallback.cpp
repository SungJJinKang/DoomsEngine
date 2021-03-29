#include "KeyCallback.h"

#include "../IO/UserInput_Server.h"


bool GetKeyToogle(int keyCode)
{
	return doom::userinput::UserInput_Server::GetKeyToggle(static_cast<doom::userinput::eKEY_CODE>(keyCode));
}
bool GetKeyPressing(int keyCode)
{
	return doom::userinput::UserInput_Server::GetKey(static_cast<doom::userinput::eKEY_CODE>(keyCode));
}
bool GetKeyUp(int keyCode)
{
	return doom::userinput::UserInput_Server::GetKeyUp(static_cast<doom::userinput::eKEY_CODE>(keyCode));
}
bool GetKeyDown(int keyCode)
{
	return doom::userinput::UserInput_Server::GetKeyDown(static_cast<doom::userinput::eKEY_CODE>(keyCode));
}