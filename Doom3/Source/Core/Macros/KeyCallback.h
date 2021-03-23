#pragma once

#if defined(DEBUG_MODE)

bool GetToogle(int keyCode);

#ifndef ONLY_WHEN_KEY_TOGGLE_ON
#define ONLY_WHEN_KEY_TOGGLE_ON(keyCode, statement)	\
	do {	\
		if (GetToogle(static_cast<int>(keyCode)))	\
		{	\
			statement;	\
		}	\
	} while (false)
#endif

#else

#ifndef ONLY_WHEN_KEY_TOGGLE_ON
#define ONLY_WHEN_KEY_TOGGLE_ON(keyCode, statement) statement
#endif

#endif
