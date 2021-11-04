#pragma once

#include <cstdio>
#include <Windows.h>

#define MAX_STACKWALK 10

namespace doom
{
    namespace debugging
    {
        LONG ExceptionHandler(_EXCEPTION_POINTERS* lpExceptionInfo)
        {
            printf("================== Exception ===================\r\n");
            printf("Exception Code : 0x%08X\r\n",
                lpExceptionInfo->ExceptionRecord->ExceptionCode);
            printf("Exception Address : 0x%08P\r\n",
                lpExceptionInfo->ExceptionRecord->ExceptionAddress);

            DWORD64   dwEbp = 0, dwOldEbp = 0;

            dwEbp = lpExceptionInfo->ContextRecord->Rbp;
            printf("EBP Register : 0x%08x\r\n", dwEbp);
            printf("CallStack :\r\n");

            for (INT nIndex = 0; nIndex < MAX_STACKWALK; nIndex++)
            {
                printf("\t%d th Stack : 0x%08x \r\n", nIndex + 1, *(DWORD64*)(dwEbp + sizeof(DWORD64)));
                dwOldEbp = dwEbp;
                dwEbp = *(DWORD64*)(dwEbp);
                if (dwEbp % sizeof(DWORD64) != 0 || dwOldEbp > dwEbp) // 잘못된 값이 나올때까지 추적  
                {
                    break;
                }
            }

            return EXCEPTION_EXECUTE_HANDLER;
        }
    }
}



