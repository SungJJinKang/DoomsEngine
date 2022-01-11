#include "GraphicsAPILoader.h"

#include <cassert>
#include <string>

#include <Windows.h>

#include "GraphicsAPIManager.h"
#include "EngineGUI/PrintText.h"

#define OPENGL_DLL_FILE_NAME TEXT("OpenGLGraphicsAPI.dll")
#define DX11_DLL_FILE_NAME TEXT("DX11GraphicsAPI.dll")
#define DW_FLAGS 0x00000000

unsigned int dooms::graphics::GraphicsAPILoader::FreeGraphicsAPILibrary()
{
	bool isFreeLibrarySuccess = false;
	if (mAPIModule != nullptr)
	{
		isFreeLibrarySuccess = FreeLibrary(reinterpret_cast<HMODULE>(mAPIModule));      //2: unload the DLL
		//D_ASSERT(isFreeLibrarySuccess == true);
	}
	return isFreeLibrarySuccess == true ? 0 : 1;
}

dooms::graphics::GraphicsAPILoader::GraphicsAPILoader()
	:mAPIModule{ NULL }
{
}

dooms::graphics::GraphicsAPILoader::~GraphicsAPILoader()
{
	const bool isSuccess = FreeGraphicsAPILibrary();
	D_ASSERT(isSuccess == true);
}


dooms::graphics::GraphicsAPILoader::GraphicsAPILoader(GraphicsAPILoader&& loader) noexcept
	: mAPIModule{ loader.mAPIModule }
{
	loader.mAPIModule = NULL;
}


dooms::graphics::GraphicsAPILoader& dooms::graphics::GraphicsAPILoader::operator=(GraphicsAPILoader&& loader) noexcept
{
	mAPIModule = loader.mAPIModule;
	loader.mAPIModule = NULL;

	return *this;
}

void* dooms::graphics::GraphicsAPILoader::LoadGraphicsAPILibrary
(
	const eGraphicsAPIType graphicsAPIType
)
{
	assert(mAPIModule == nullptr);


#ifdef UNICODE
	std::wstring dllFileName;
#else
	std::string dllFileName;
#endif

	switch (graphicsAPIType)
	{
	case eGraphicsAPIType::OpenGL: 
		dllFileName = OPENGL_DLL_FILE_NAME;
		break;

	case eGraphicsAPIType::DX11: 
		dllFileName = DX11_DLL_FILE_NAME;
		break;

	default: 
		assert(false);
	}

#ifdef UNICODE
	mAPIModule = LoadLibraryEx(dllFileName.c_str(), NULL, DW_FLAGS);
#else
	mAPIModule = LoadLibraryEx(dllFileName.c_str(), NULL, dwFlags);
#endif
	
	if (mAPIModule == NULL)
	{//FAIL
		const DWORD errorCode = GetLastError();

		D_ASSERT_LOG(false, "Fail to Load Graphics API Library - Error Code : %d", errorCode);
		dooms::ui::PrintText("Fail to Load Graphics API Library - Error Code : %d", errorCode);
	}

	return mAPIModule;
}

bool dooms::graphics::GraphicsAPILoader::UnLoadGraphicsAPILibrary()
{
	return FreeGraphicsAPILibrary();
}
