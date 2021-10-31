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

			D_ASSERT_LOG(false, "Fail to GetProcAddress ( \"%s\" from \"%ls\" ) - Error Code : %d", functionName, mCSharpLibraryPath, errorCode);
			doom::ui::PrintText("Fail to GetProcAddress ( \"%s\" from \"%ls\" ) - Error Code : %d", functionName, mCSharpLibraryPath, errorCode);
		}

		return procAddress;
	}
	else
	{
		doom::ui::PrintText("Try to GetProcAddress, But Library is not loaded");
		return nullptr;
	}
}

doom::SmartCSharpLibrary::SmartCSharpLibrary(const wchar_t* csharpLibraryPath)
	: mCSharpLibraryPath(csharpLibraryPath), mLibrary(nullptr)
{
	mLibrary = LoadLibrary(mCSharpLibraryPath);

	if(mLibrary == nullptr)
	{
		const DWORD errorCode = GetLastError();

		D_ASSERT_LOG(false, "Fail to Load Library ( %ls ) - Error Code : %d", csharpLibraryPath, errorCode);
		doom::ui::PrintText("Fail to Load Library ( %ls ) - Error Code : %d", csharpLibraryPath, errorCode);
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
	_SmartCSharpLibrary.mCSharpLibraryPath = nullptr;
}

doom::SmartCSharpLibrary& doom::SmartCSharpLibrary::operator=(SmartCSharpLibrary&& _SmartCSharpLibrary) noexcept
{
	mLibrary = _SmartCSharpLibrary.mLibrary;
	mCSharpLibraryPath = _SmartCSharpLibrary.mCSharpLibraryPath;

	_SmartCSharpLibrary.mLibrary = nullptr;
	_SmartCSharpLibrary.mCSharpLibraryPath = nullptr;
	return *this;
}
