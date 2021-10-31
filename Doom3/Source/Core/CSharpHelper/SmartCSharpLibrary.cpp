#include "SmartCSharpLibrary.h"


#include <Windows.h>


void* doom::SmartCSharpLibrary::_GetProcAddress(const char* const functionName)
{
	D_ASSERT(mLibrary != nullptr);

	if(mLibrary != nullptr)
	{
		void* const procAddress = GetProcAddress(reinterpret_cast<HMODULE>(mLibrary), functionName);

		if(procAddress == nullptr)
		{
			const DWORD errorCode = GetLastError();

			D_ASSERT_LOG(false, "Fail to GetProcAddress ( ""%s"" from ""%s"" ) - Error Code : %d", functionName, mCSharpLibraryPath.c_str(), errorCode);
			doom::ui::PrintText("Fail to GetProcAddress ( ""%s"" from ""%s"" ) - Error Code : %d", functionName, mCSharpLibraryPath.c_str(), errorCode);
		}

		return procAddress;
	}
	else
	{
		doom::ui::PrintText("Try to GetProcAddress, But Library is not loaded");
		return nullptr;
	}
}

doom::SmartCSharpLibrary::SmartCSharpLibrary(const std::string& csharpLibraryPath)
	: mCSharpLibraryPath(csharpLibraryPath), mLibrary(nullptr)
{
#ifdef UNICODE
	mLibrary = LoadLibrary(std::wstring( mCSharpLibraryPath.begin(), mCSharpLibraryPath.end()).c_str());
#else
	mLibrary = LoadLibrary(mCSharpLibraryPath.c_str());
#endif
	

	if(mLibrary == nullptr)
	{
		const DWORD errorCode = GetLastError();

		D_ASSERT_LOG(false, "Fail to Load Library ( %s ) - Error Code : %d", csharpLibraryPath.c_str(), errorCode);
		doom::ui::PrintText("Fail to Load Library ( %s ) - Error Code : %d", csharpLibraryPath.c_str(), errorCode);
	}
}

doom::SmartCSharpLibrary::~SmartCSharpLibrary()
{
	if (mLibrary != nullptr)
	{
		const bool isFreeLibrarySuccess = FreeLibrary(reinterpret_cast<HMODULE>(mLibrary));      //2: unload the DLL
		//D_ASSERT(isFreeLibrarySuccess == true);
	}
}

doom::SmartCSharpLibrary::SmartCSharpLibrary(SmartCSharpLibrary&& _SmartCSharpLibrary) noexcept
	: mLibrary(_SmartCSharpLibrary.mLibrary), mCSharpLibraryPath(_SmartCSharpLibrary.mCSharpLibraryPath)
{
	_SmartCSharpLibrary.mLibrary = nullptr;
	_SmartCSharpLibrary.mCSharpLibraryPath.clear();
}

doom::SmartCSharpLibrary& doom::SmartCSharpLibrary::operator=(SmartCSharpLibrary&& _SmartCSharpLibrary) noexcept
{
	mLibrary = _SmartCSharpLibrary.mLibrary;
	mCSharpLibraryPath = _SmartCSharpLibrary.mCSharpLibraryPath;

	_SmartCSharpLibrary.mLibrary = nullptr;
	_SmartCSharpLibrary.mCSharpLibraryPath.clear();
	return *this;
}

int doom::filter(unsigned code, _EXCEPTION_POINTERS* ptr)
{
	D_ASSERT_LOG(false, "Exception in Calling C# Function");
	return EXCEPTION_EXECUTE_HANDLER;
}
