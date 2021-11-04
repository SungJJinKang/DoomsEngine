#include "SmartDynamicLinking.h"

#include <Windows.h>
#include <UI/PrintText.h>

#include "OS/StackTrace.h"

std::mutex  doom::DynamicLinkingLibrary::LoadUnLoadDLLMutexs{};

#define DEFAULT_LOAD_LIBRARY_EX_DWFLAGS 0x00000000

struct DynamicLinkingReleaser {
	void operator()(void* const library)
	{
		if (library != nullptr)
		{
			FreeLibrary(reinterpret_cast<HMODULE>(library));
		}
	};

};

doom::DynamicLinkingLibrary::DynamicLinkingLibrary(const std::string& libraryPath)
	: DynamicLinkingLibrary(libraryPath, DEFAULT_LOAD_LIBRARY_EX_DWFLAGS)
{
	
}

doom::DynamicLinkingLibrary::DynamicLinkingLibrary(const std::string& libraryPath, const unsigned long dwFlags)
	: mLibraryPath(libraryPath), mLibrary(LoadDynamicLinkingLibrary(dwFlags), DynamicLinkingReleaser())
{
	if (mLibrary == nullptr)
	{
		const DWORD errorCode = GetLastError();

		D_ASSERT_LOG(false, "Fail to Load Library ( %s ) - Error Code : %d", libraryPath.c_str(), errorCode);
		doom::ui::PrintText("Fail to Load Library ( %s ) - Error Code : %d", libraryPath.c_str(), errorCode);
	}
}

void* doom::DynamicLinkingLibrary::LoadDynamicLinkingLibrary(const unsigned long dwFlags)
{
	//if call LoadLibrary on same dll, it's not thread safe
		//https://stackoverflow.com/questions/11253725/are-loadlibrary-freelibrary-and-getmodulehandle-win32-functions-thread-safe
		//But In this code, Lock critical section regardless with which library
		//I know this is slow, But I think this is acceptable.

		//I tried lock on specific library name using unordred_map<string library name, mutex>
		//unordered_map isn't thread-safe too!!

	std::unique_lock<std::mutex> uniq_lock{ LoadUnLoadDLLMutexs };

#ifdef UNICODE
	const std::wstring wide_str{ mLibraryPath.begin(), mLibraryPath.end() };
	return reinterpret_cast<void*>(LoadLibraryEx(wide_str.c_str(), NULL, dwFlags ));
#else
	return reinterpret_cast<void*>(LoadLibraryEx(libraryPath.c_str(), NULL, dwFlags));
#endif
	
}

bool doom::DynamicLinkingLibrary::UnloadDynamicLinkingLibrary()
{
	bool isFreeLibrarySuccess = false;
	if (mLibrary != nullptr)
	{
		std::unique_lock<std::mutex> uniq_lock{ LoadUnLoadDLLMutexs };

		isFreeLibrarySuccess = FreeLibrary(reinterpret_cast<HMODULE>(mLibrary.get()));      //2: unload the DLL
		//D_ASSERT(isFreeLibrarySuccess == true);
	}
	return isFreeLibrarySuccess;
}


void* doom::SmartDynamicLinking::_GetProcAddress(const char* const functionName)
{
	D_ASSERT(mDynamicLinkingLibrary.mLibrary != nullptr);

	if(mDynamicLinkingLibrary.mLibrary != nullptr)
	{
		void* const procAddress = GetProcAddress(reinterpret_cast<HMODULE>(mDynamicLinkingLibrary.mLibrary.get()), functionName);

		if(procAddress == nullptr)
		{
			const DWORD errorCode = GetLastError();

			D_ASSERT_LOG(false, "Fail to GetProcAddress ( ""%s"" from ""%s"" ) - Error Code : %d", functionName, mDynamicLinkingLibrary.mLibraryPath.c_str(), errorCode);
			doom::ui::PrintText("Fail to GetProcAddress ( ""%s"" from ""%s"" ) - Error Code : %d", functionName, mDynamicLinkingLibrary.mLibraryPath.c_str(), errorCode);
		}

		return procAddress;
	}
	else
	{
		doom::ui::PrintText("Try to GetProcAddress, But Library is not loaded");
		return nullptr;
	}
}


doom::SmartDynamicLinking::SmartDynamicLinking(const std::string& csharpLibraryPath)
	:	mDynamicLinkingLibrary(csharpLibraryPath)
{
	
}

doom::SmartDynamicLinking::~SmartDynamicLinking() = default;
doom::SmartDynamicLinking::SmartDynamicLinking(const SmartDynamicLinking&) = default;
doom::SmartDynamicLinking::SmartDynamicLinking(SmartDynamicLinking&&) noexcept = default;
doom::SmartDynamicLinking& doom::SmartDynamicLinking::operator=(const SmartDynamicLinking&) = default;
doom::SmartDynamicLinking& doom::SmartDynamicLinking::operator=(SmartDynamicLinking&&) noexcept = default;
int doom::filter(unsigned code, _EXCEPTION_POINTERS* ptr)
{
	doom::ui::PrintText("Exception from Called DLL's Function");
	doom::debugging::ExceptionHandler(ptr);
	return EXCEPTION_EXECUTE_HANDLER;
}
