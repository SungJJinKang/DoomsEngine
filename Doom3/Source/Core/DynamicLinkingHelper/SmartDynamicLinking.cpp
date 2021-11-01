#include "SmartDynamicLinking.h"


#include <Windows.h>


void* doom::SmartDynamicLinking::_GetProcAddress(const char* const functionName)
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

doom::SmartDynamicLinking::SmartDynamicLinking(const std::string& csharpLibraryPath)
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

doom::SmartDynamicLinking::~SmartDynamicLinking()
{
	if (mLibrary != nullptr)
	{
		const bool isFreeLibrarySuccess = FreeLibrary(reinterpret_cast<HMODULE>(mLibrary));      //2: unload the DLL
		//D_ASSERT(isFreeLibrarySuccess == true);
	}
}

doom::SmartDynamicLinking::SmartDynamicLinking(SmartDynamicLinking&& _SmartCSharpLibrary) noexcept
	: mLibrary(_SmartCSharpLibrary.mLibrary), mCSharpLibraryPath(_SmartCSharpLibrary.mCSharpLibraryPath)
{
	_SmartCSharpLibrary.mLibrary = nullptr;
	_SmartCSharpLibrary.mCSharpLibraryPath.clear();
}

doom::SmartDynamicLinking& doom::SmartDynamicLinking::operator=(SmartDynamicLinking&& _SmartCSharpLibrary) noexcept
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
