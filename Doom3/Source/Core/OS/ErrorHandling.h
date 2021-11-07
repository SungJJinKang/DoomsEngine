#pragma once

#include <cstdio>
#include <Windows.h>

#define MAX_STACKWALK 10

namespace dooms
{
    namespace errorHandling
    {
        extern LONG ExceptionHandler(_EXCEPTION_POINTERS* lpExceptionInfo);

        extern void SetUnHandledExceptionHandling();
    }
}



