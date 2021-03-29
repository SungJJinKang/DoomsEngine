#pragma once

bool GetKeyToogle(int keyCode);
bool GetKeyPressing(int keyCode);
bool GetKeyUp(int keyCode);
bool GetKeyDown(int keyCode);

#ifdef DEBUG_MODE

#ifndef D_DEBUG_ARROW_INCREMENT_DECREMENT

//Put this in loop function
//If you are pressin Arrow Up Button, Variable with "variablename" variablename will be incremented
#define D_DEBUG_ARROW_INCREMENT_DECREMENT(variablename) \
if(GetKeyPressing(265) == true)							\
{														\
	variablename++;										\
}														\
else if (GetKeyPressing(264) == true)					\
{														\
	variablename--;										\
}
#endif

#else

#ifndef D_DEBUG_ARROW_INCREMENT_DECREMENT
#define D_DEBUG_ARROW_INCREMENT_DECREMENT(variablename) 
#endif

#endif
