#include "SmartDynamicLinking.h"

#include <Windows.h>
#include <EngineGUI/PrintText.h>

#include "OS/ErrorHandling.h"

std::mutex  dooms::DynamicLinkingLibrary::LoadUnLoadDLLMutexs{};

#define DEFAULT_LOAD_LIBRARY_EX_DWFLAGS 0x00000000

dooms::DynamicLinkingLibrary::DynamicLinkingLibrary(const std::string& libraryPath)
	: DynamicLinkingLibrary(libraryPath, DEFAULT_LOAD_LIBRARY_EX_DWFLAGS)
{
	
}

dooms::DynamicLinkingLibrary::DynamicLinkingLibrary(const std::string& libraryPath, const unsigned long dwFlags)
	: mLibraryPath(libraryPath), mLibrary(LoadDynamicLinkingLibrary(dwFlags))
{
	if (mLibrary == NULL)
	{
		const DWORD errorCode = GetLastError();

		D_ASSERT_LOG(false, "Fail to Load Library ( %s ) - Error Code : %d", libraryPath.c_str(), errorCode);
		dooms::ui::PrintText("Fail to Load Library ( %s ) - Error Code : %d", libraryPath.c_str(), errorCode);
	}
}

dooms::DynamicLinkingLibrary::~DynamicLinkingLibrary()
{
	UnloadDynamicLinkingLibrary();
}

void* dooms::DynamicLinkingLibrary::LoadDynamicLinkingLibrary(const unsigned long dwFlags)
{
	//if call LoadLibrary on same dll, it's not thread safe
		//https://stackoverflow.com/questions/11253725/are-loadlibrary-freelibrary-and-getmodulehandle-win32-functions-thread-safe
		//But In this code, Lock critical section regardless with which library
		//I know this is slow, But I think this is acceptable.

		//I tried lock on specific library name using unordred_map<string library name, mutex>
		//unordered_map isn't thread-safe too!!

	std::scoped_lock<std::mutex> uniq_lock{ LoadUnLoadDLLMutexs };

#ifdef UNICODE
	const std::wstring wide_str{ mLibraryPath.begin(), mLibraryPath.end() };
	return reinterpret_cast<void*>(LoadLibraryEx(wide_str.c_str(), NULL, dwFlags ));
#else
	return reinterpret_cast<void*>(LoadLibraryEx(libraryPath.c_str(), NULL, dwFlags));
#endif
	
}

bool dooms::DynamicLinkingLibrary::UnloadDynamicLinkingLibrary()
{
	bool isFreeLibrarySuccess = false;
	if (mLibrary != nullptr)
	{
		std::scoped_lock<std::mutex> uniq_lock{ LoadUnLoadDLLMutexs };

		isFreeLibrarySuccess = FreeLibrary(reinterpret_cast<HMODULE>(mLibrary));      //2: unload the DLL
		//D_ASSERT(isFreeLibrarySuccess == true);
	}
	return isFreeLibrarySuccess;
}


void* dooms::SmartDynamicLinking::_GetProcAddress(const char* const functionName)
{
	D_ASSERT(mDynamicLinkingLibrary->mLibrary != nullptr);

	if(mDynamicLinkingLibrary->mLibrary != nullptr)
	{
		void* const procAddress = GetProcAddress(reinterpret_cast<HMODULE>(mDynamicLinkingLibrary->mLibrary), functionName);

		if(procAddress == nullptr)
		{
			const DWORD errorCode = GetLastError();

			D_ASSERT_LOG(false, "Fail to GetProcAddress ( ""%s"" from ""%s"" ) - Error Code : %d", functionName, mDynamicLinkingLibrary->mLibraryPath.c_str(), errorCode);
			dooms::ui::PrintText("Fail to GetProcAddress ( ""%s"" from ""%s"" ) - Error Code : %d", functionName, mDynamicLinkingLibrary->mLibraryPath.c_str(), errorCode);
		}

		return procAddress;
	}
	else
	{
		dooms::ui::PrintText("Try to GetProcAddress, But Library is not loaded");
		return nullptr;
	}
}

dooms::SmartDynamicLinking::SmartDynamicLinking()
	: mDynamicLinkingLibrary()
{
}


dooms::SmartDynamicLinking::SmartDynamicLinking(const std::string& libraryPath)
	:	mDynamicLinkingLibrary(std::make_shared<DynamicLinkingLibrary>(libraryPath))
{
	
}

dooms::SmartDynamicLinking::~SmartDynamicLinking()
{
	
}
dooms::SmartDynamicLinking::SmartDynamicLinking(const SmartDynamicLinking&) = default;
dooms::SmartDynamicLinking::SmartDynamicLinking(SmartDynamicLinking&&) noexcept = default;
dooms::SmartDynamicLinking& dooms::SmartDynamicLinking::operator=(const SmartDynamicLinking&) = default;
dooms::SmartDynamicLinking& dooms::SmartDynamicLinking::operator=(SmartDynamicLinking&&) noexcept = default;

void dooms::SmartDynamicLinking::LoadDynamicLinkingLibrary(const std::string& libraryPath)
{
	D_ASSERT_LOG(static_cast<bool>(mDynamicLinkingLibrary) == false, "Already another library is loaded");
	if(static_cast<bool>(mDynamicLinkingLibrary) == false)
	{
		mDynamicLinkingLibrary = std::make_shared<DynamicLinkingLibrary>(libraryPath);
	}	
}

void dooms::SmartDynamicLinking::ReleaseDynamicLinkingLibrary()
{
	mDynamicLinkingLibrary.reset();
}

bool dooms::SmartDynamicLinking::IsDynamicLibraryLoaded() const
{
	return static_cast<bool>(mDynamicLinkingLibrary);
}

int dooms::filter(unsigned code, _EXCEPTION_POINTERS* ptr)
{
	dooms::ui::PrintText("Exception from Called DLL's Function");
	dooms::errorHandling::ExceptionHandler(ptr);
	return EXCEPTION_EXECUTE_HANDLER;
}
