#pragma once

#define CONCAT(A, B) A##B
#define MAKE_STRING(A) #A

#ifndef SUPPORT_UNICODE
#define SUPPORT_UNICODE
#endif

#ifdef SUPPORT_UNICODE

#ifndef D_TEXT
#define D_TEXT(Str) L##Str
#endif

#else

#ifndef D_TEXT
#define D_TEXT(Str) Str
#endif

#endif