#pragma once

#if defined(DEBUG_MODE)
bool GetToogle(int keyCode);
#define ONLY_WHEN_KEY_TOGGLE_ON(keyCode, statement)	\
	do {	\
		if (GetToogle(static_cast<int>(keyCode)))	\
		{	\
			statement;	\
		}	\
	} while (false)
#else
#define ONLY_WHEN_KEY_TOGGLE_ON(keyCode, statement) statement
#endif
