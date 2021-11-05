#include "ErrorHandling.h"

LONG doom::errorHandling::ExceptionHandler(_EXCEPTION_POINTERS* lpExceptionInfo)
{
	printf("================== Exception ===================\r\n");
	printf("Exception Code : 0x%08X\r\n",
	       lpExceptionInfo->ExceptionRecord->ExceptionCode);
	printf("Exception Address : 0x%08P\r\n",
	       lpExceptionInfo->ExceptionRecord->ExceptionAddress);

	size_t   dwEbp = 0, dwOldEbp = 0;

	dwEbp = lpExceptionInfo->ContextRecord->Rbp;
	printf("EBP Register : 0x%08x\r\n", dwEbp);
	printf("CallStack :\r\n");

	for (INT nIndex = 0; nIndex < MAX_STACKWALK; nIndex++)
	{
		printf("\t%d th Stack : 0x%08x \r\n", nIndex + 1, *(size_t*)(dwEbp + sizeof(size_t)));
		dwOldEbp = dwEbp;
		dwEbp = *(size_t*)(dwEbp);
		if (dwEbp % sizeof(size_t) != 0 || dwOldEbp > dwEbp) // 잘못된 값이 나올때까지 추적  
		{
			break;
		}
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

void doom::errorHandling::SetUnHandledExceptionHandling()
{
	static bool IsInitialized = false;

	if(IsInitialized == false)
	{
		SetUnhandledExceptionFilter(&doom::errorHandling::ExceptionHandler);
		IsInitialized = true;
	}
}
