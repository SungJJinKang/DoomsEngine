#pragma once

#include <cstdio>
#include <Windows.h>

#define MAX_STACKWALK 10

namespace doom
{
    namespace errorHandling
    {
        extern LONG ExceptionHandler(_EXCEPTION_POINTERS* lpExceptionInfo);

        extern void SetUnHandledExceptionHandling();
    }
}



