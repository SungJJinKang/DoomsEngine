#pragma once

#define CONCAT2(x, y) x##y
#define CONCAT(x, y) CONCAT2(x, y)

#define MAKE_STRING(A) #A


#ifdef UNICODE

#ifndef D_TEXT
#define D_TEXT(Str) L##Str
#endif

#else

#ifndef D_TEXT
#define D_TEXT(Str) Str
#endif

#endif

