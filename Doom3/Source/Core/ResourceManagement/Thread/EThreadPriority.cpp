#include "EThreadPriority.h"

const char* dooms::thread::GetThreadPriorityNameStr(const EThreadPriority InThreadPriority)
{
	const char* Str = nullptr;

	switch (InThreadPriority)
	{
		case EThreadPriority::High:
		{
			Str = "High";
			break;
		}
		case EThreadPriority::Middle:
		{
			Str = "Middle";
			break;
		}
		case EThreadPriority::Low:
		{
			Str = "Low";
			break;
		}
		case EThreadPriority::Background:
		{
			Str = "Background";
			break;
		}
		default:
		{
			D_ASSERT(false);
			break;
		}
	}

	return Str;
}
