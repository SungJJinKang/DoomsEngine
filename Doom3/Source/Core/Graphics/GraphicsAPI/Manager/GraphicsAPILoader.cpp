#include "GraphicsAPILoader.h"

#include <cassert>
#include <string>

#include <Windows.h>

#include "GraphicsAPIManager.h"
#include "EngineGUI/PrintText.h"
#include "../GraphicsAPI.h"
#include "../Input/GraphicsAPIInput.h"
#include "../PlatformImgui/PlatformImgui.h"

#define OPENGL_DLL_FILE_NAME TEXT("OpenGLGraphicsAPI.dll")
#define DX11_DLL_FILE_NAME TEXT("DX11GraphicsAPI.dll")
#define DW_FLAGS 0x00000000

void dooms::graphics::GraphicsAPILoader::FetExportedFunctionAddress(void* module)
{
	D_ASSERT(module != nullptr);
	HMODULE hModule = reinterpret_cast<HMODULE>(module);

	dooms::graphics::GraphicsAPI::ActivateTextureUnit = (GraphicsAPI::GRAPHICS_ACTIVATETEXTUREUNIT)GetProcAddress(hModule, "ActivateTextureUnit");
	dooms::graphics::GraphicsAPI::AllocateBufferMemory = (GraphicsAPI::GRAPHICS_ALLOCATEBUFFERMEMORY)GetProcAddress(hModule, "AllocateBufferMemory");
	dooms::graphics::GraphicsAPI::AllocateRenderBufferMemory = (GraphicsAPI::GRAPHICS_ALLOCATERENDERBUFFERMEMORY)GetProcAddress(hModule, "AllocateRenderBufferMemory");
	dooms::graphics::GraphicsAPI::Attach2DTextureToFrameBuffer = (GraphicsAPI::GRAPHICS_ATTACH2DTEXTURETOFRAMEBUFFER)GetProcAddress(hModule, "Attach2DTextureToFrameBuffer");
	dooms::graphics::GraphicsAPI::AttachRenderBufferToFrameBuffer = (GraphicsAPI::GRAPHICS_ATTACHRENDERBUFFERTOFRAMEBUFFER)GetProcAddress(hModule, "AttachRenderBufferToFrameBuffer");
	dooms::graphics::GraphicsAPI::AttachShaderToMaterial = (GraphicsAPI::GRAPHICS_ATTACHSHADERTOMATERIAL)GetProcAddress(hModule, "AttachShaderToMaterial");
	dooms::graphics::GraphicsAPI::BindBuffer = (GraphicsAPI::GRAPHICS_BINDBUFFER)GetProcAddress(hModule, "BindBuffer");
	dooms::graphics::GraphicsAPI::BindBufferToIndexedBuffer = (GraphicsAPI::GRAPHICS_BINDBUFFERTOINDEXEDBUFFER)GetProcAddress(hModule, "BindBufferToIndexedBuffer");
	dooms::graphics::GraphicsAPI::BindFrameBuffer = (GraphicsAPI::GRAPHICS_BINDFRAMEBUFFER)GetProcAddress(hModule, "BindFrameBuffer");
	dooms::graphics::GraphicsAPI::BindMaterial = (GraphicsAPI::GRAPHICS_BINDMATERIAL)GetProcAddress(hModule, "BindMaterial");
	dooms::graphics::GraphicsAPI::BindRenderBuffer = (GraphicsAPI::GRAPHICS_BINDRENDERBUFFER)GetProcAddress(hModule, "BindRenderBuffer");
	dooms::graphics::GraphicsAPI::BindTextureObject = (GraphicsAPI::GRAPHICS_BINDTEXTUREOBJECT)GetProcAddress(hModule, "BindTextureObject");
	dooms::graphics::GraphicsAPI::BindTextureObjectAndActivateTextureUnit = (GraphicsAPI::GRAPHICS_BINDTEXTUREOBJECTANDACTIVATETEXTUREUNIT)GetProcAddress(hModule, "BindTextureObjectAndActivateTextureUnit");
	dooms::graphics::GraphicsAPI::BindVertexArrayObject = (GraphicsAPI::GRAPHICS_BINDVERTEXARRAYOBJECT)GetProcAddress(hModule, "BindVertexArrayObject");
	dooms::graphics::GraphicsAPI::BlitFrameBuffer = (GraphicsAPI::GRAPHICS_BLITFRAMEBUFFER)GetProcAddress(hModule, "BlitFrameBuffer");
	dooms::graphics::GraphicsAPI::CheckFrameBufferIsSuccesfullyCreated = (GraphicsAPI::GRAPHICS_CHECKFRAMEBUFFERISSUCCESFULLYCREATED)GetProcAddress(hModule, "CheckFrameBufferIsSuccesfullyCreated");
	dooms::graphics::GraphicsAPI::ClearBuffer = (GraphicsAPI::GRAPHICS_CLEARBUFFER)GetProcAddress(hModule, "ClearBuffer");
	dooms::graphics::GraphicsAPI::ClearBuffer1 = (GraphicsAPI::GRAPHICS_CLEARBUFFER1)GetProcAddress(hModule, "ClearBuffer1");
	dooms::graphics::GraphicsAPI::ClearBuffer2 = (GraphicsAPI::GRAPHICS_CLEARBUFFER2)GetProcAddress(hModule, "ClearBuffer2");
	dooms::graphics::GraphicsAPI::ClearBuffer3 = (GraphicsAPI::GRAPHICS_CLEARBUFFER3)GetProcAddress(hModule, "ClearBuffer3");
	dooms::graphics::GraphicsAPI::ClearColor = (GraphicsAPI::GRAPHICS_CLEARCOLOR)GetProcAddress(hModule, "ClearColor");
	dooms::graphics::GraphicsAPI::ClearSpecificBuffer = (GraphicsAPI::GRAPHICS_CLEARSPECIFICBUFFER)GetProcAddress(hModule, "ClearSpecificBuffer");
	dooms::graphics::GraphicsAPI::CompileShader = (GraphicsAPI::GRAPHICS_COMPILESHADER)GetProcAddress(hModule, "CompileShader");
	dooms::graphics::GraphicsAPI::CompileShaders = (GraphicsAPI::GRAPHICS_COMPILESHADERS)GetProcAddress(hModule, "CompileShaders");
	dooms::graphics::GraphicsAPI::CreateBuffers = (GraphicsAPI::GRAPHICS_CREATEBUFFERS)GetProcAddress(hModule, "CreateBuffers");
	dooms::graphics::GraphicsAPI::CreateMaterial = (GraphicsAPI::GRAPHICS_CREATEMATERIAL)GetProcAddress(hModule, "CreateMaterial");
	dooms::graphics::GraphicsAPI::CreateRenderBufferObject = (GraphicsAPI::GRAPHICS_CREATERENDERBUFFEROBJECT)GetProcAddress(hModule, "CreateRenderBufferObject");
	dooms::graphics::GraphicsAPI::CreateShaderObject = (GraphicsAPI::GRAPHICS_CREATESHADEROBJECT)GetProcAddress(hModule, "CreateShaderObject");
	dooms::graphics::GraphicsAPI::CreateTextureObject = (GraphicsAPI::GRAPHICS_CREATEXTUREOBJECT)GetProcAddress(hModule, "CreateTextureObject");
	dooms::graphics::GraphicsAPI::CreateVertexArrayObject = (GraphicsAPI::GRAPHICS_CREATEVERTEXARRAYOBJECT)GetProcAddress(hModule, "CreateVertexArrayObject");
	dooms::graphics::GraphicsAPI::Define1DCompressedTextureStorageRequirement = (GraphicsAPI::GRAPHICS_DEFINE1DCOMPRESSEDTEXTURESTORAGEREQUIREMENT)GetProcAddress(hModule, "Define1DCompressedTextureStorageRequirement");
	dooms::graphics::GraphicsAPI::Define1DTextureStorageRequirement = (GraphicsAPI::GRAPHICS_DEFINE1DTEXTURESTORAGEREQUIREMENT)GetProcAddress(hModule, "Define1DTextureStorageRequirement");
	dooms::graphics::GraphicsAPI::Define2DCompressedTextureStorageRequirement = (GraphicsAPI::GRAPHICS_DEFINE2DCOMPRESSEDTEXTURESTORAGEREQUIREMENT)GetProcAddress(hModule, "Define2DCompressedTextureStorageRequirement");
	dooms::graphics::GraphicsAPI::Define2DTextureStorageRequirement = (GraphicsAPI::GRAPHICS_DEFINE2DTEXTURESTORAGEREQUIREMENT)GetProcAddress(hModule, "Define2DTextureStorageRequirement");
	dooms::graphics::GraphicsAPI::Define3DCompressedTextureStorageRequirement = (GraphicsAPI::GRAPHICS_DEFINE3DCOMPRESSEDTEXTURESTORAGEREQUIREMENT)GetProcAddress(hModule, "Define3DCompressedTextureStorageRequirement");
	dooms::graphics::GraphicsAPI::Define3DTextureStorageRequirement = (GraphicsAPI::GRAPHICS_DEFINE3DTEXTURESTORAGEREQUIREMENT)GetProcAddress(hModule, "Define3DTextureStorageRequirement");
	dooms::graphics::GraphicsAPI::DefineVertexAttributeLayout = (GraphicsAPI::GRAPHICS_DEFINEVERTEXATTRIBUTELAYOUT)GetProcAddress(hModule, "DefineVertexAttributeLayout");
	dooms::graphics::GraphicsAPI::DeinitializeGraphicsAPI = (GraphicsAPI::GRAPHICS_DEINITIALIZEGRAPHICSAPI)GetProcAddress(hModule, "DeinitializeGraphicsAPI");
	dooms::graphics::GraphicsAPI::DestroyBuffer = (GraphicsAPI::GRAPHICS_DESTROYBUFFER)GetProcAddress(hModule, "DestroyBuffer");
	dooms::graphics::GraphicsAPI::DestroyBuffers = (GraphicsAPI::GRAPHICS_DESTORYBUFFERS)GetProcAddress(hModule, "DestroyBuffers");
	dooms::graphics::GraphicsAPI::DestroyFrameBuffer = (GraphicsAPI::GRAPHICS_DESTROYFRAMEBUFFER)GetProcAddress(hModule, "DestroyFrameBuffer");
	dooms::graphics::GraphicsAPI::DestroyMaterial = (GraphicsAPI::GRAPHICS_DESTROYMATERIAL)GetProcAddress(hModule, "DestroyMaterial");
	dooms::graphics::GraphicsAPI::DestroyRenderBuffer = (GraphicsAPI::GRAPHICS_DESTROYRENDERBUFFER)GetProcAddress(hModule, "DestroyRenderBuffer");
	dooms::graphics::GraphicsAPI::DestroyShaderObject = (GraphicsAPI::GRAPHICS_DESTROYSHADEROBJECT)GetProcAddress(hModule, "DestroyShaderObject");
	dooms::graphics::GraphicsAPI::DestroyTextureObject = (GraphicsAPI::GRAPHICS_DESTROYTEXTUREOBJECT)GetProcAddress(hModule, "DestroyTextureObject");
	dooms::graphics::GraphicsAPI::DestroyVertexArrayObject = (GraphicsAPI::GRAPHICS_DESTROYVERTEXARRAYOBJECT)GetProcAddress(hModule, "DestroyVertexArrayObject");
	dooms::graphics::GraphicsAPI::Draw = (GraphicsAPI::GRAPHICS_DRAW)GetProcAddress(hModule, "Draw");
	dooms::graphics::GraphicsAPI::DrawIndexed = (GraphicsAPI::GRAPHICS_DRAWINDEXED)GetProcAddress(hModule, "DrawIndexed");
	dooms::graphics::GraphicsAPI::EnableVertexAttributeArrayIndex = (GraphicsAPI::GRAPHICS_ENABLEVERTEXATTRIBUTEARRAYINDEX)GetProcAddress(hModule, "EnableVertexAttributeArrayIndex");
	dooms::graphics::GraphicsAPI::FetchTexturePixels = (GraphicsAPI::GRAPHICS_FETCHTEXTUREPIXELS)GetProcAddress(hModule, "FetchTexturePixels");
	dooms::graphics::GraphicsAPI::GenerateFrameBuffer = (GraphicsAPI::GRAPHICS_GENERATEFRAMEBUFFER)GetProcAddress(hModule, "GenerateFrameBuffer");
	dooms::graphics::GraphicsAPI::GetConstantBufferBindingPoint = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERBINDINGPOINT)GetProcAddress(hModule, "GetConstantBufferBindingPoint");
	dooms::graphics::GraphicsAPI::GetConstantBufferBlockCount = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERBLOCKCOUNT)GetProcAddress(hModule, "GetConstantBufferBlockCount");
	dooms::graphics::GraphicsAPI::GetConstantBufferDataSize = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERDATASIZE)GetProcAddress(hModule, "GetConstantBufferDataSize");
	dooms::graphics::GraphicsAPI::GetConstantBufferUniformLocation = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERUNIFORMLOCATION)GetProcAddress(hModule, "GetConstantBufferUniformLocation");
	dooms::graphics::GraphicsAPI::GetDrawCall = (GraphicsAPI::GRAPHICS_GETDRAWCALL)GetProcAddress(hModule, "GetDrawCall");
	dooms::graphics::GraphicsAPI::GetDebugFunction = (GraphicsAPI::GRAPHICS_GETDEBUGFUNCTION)GetProcAddress(hModule, "GetDebugFunction");
	dooms::graphics::GraphicsAPI::GetFrameBufferHeight = (GraphicsAPI::GRAPHICS_GETFRAMEBUFFERHEIGHT)GetProcAddress(hModule, "GetFrameBufferHeight");
	dooms::graphics::GraphicsAPI::GetFrameBufferWidth = (GraphicsAPI::GRAPHICS_GETFRAMEBUFFERWIDTH)GetProcAddress(hModule, "GetFrameBufferWidth");
	dooms::graphics::GraphicsAPI::GetPlatformVersion = (GraphicsAPI::GRAPHICS_GETPLATFORMVERSION)GetProcAddress(hModule, "GetPlatformVersion");
	dooms::graphics::GraphicsAPI::GetPlatformWindow = (GraphicsAPI::GRAPHICS_GETPLATFORMWINDOW)GetProcAddress(hModule, "GetPlatformWindow");
	dooms::graphics::GraphicsAPI::GetTextureMetaDataFloat = (GraphicsAPI::GRAPHICS_GETTEXTUREMETADATAFLOAT)GetProcAddress(hModule, "GetTextureMetaDataFloat");
	dooms::graphics::GraphicsAPI::GetTextureMetaDataInt = (GraphicsAPI::GRAPHICS_GETTEXTUREMETADATAINT)GetProcAddress(hModule, "GetTextureMetaDataInt");
	dooms::graphics::GraphicsAPI::GetTime = (GraphicsAPI::GRAPHICS_GETTIME)GetProcAddress(hModule, "GetTime");
	dooms::graphics::GraphicsAPI::GetViewPort = (GraphicsAPI::GRAPHICS_GETVIEWPORT)GetProcAddress(hModule, "GetViewPort");
	dooms::graphics::GraphicsAPI::InitializeGraphicsAPI = (GraphicsAPI::GRAPHICS_INITIALIZEGRAPHICSAPI)GetProcAddress(hModule, "InitializeGraphicsAPI");
	dooms::graphics::GraphicsAPI::LinkMaterial = (GraphicsAPI::GRAPHICS_LINKMATERIAL)GetProcAddress(hModule, "LinkMaterial");
	dooms::graphics::GraphicsAPI::MapBufferObjectToClientAddress = (GraphicsAPI::GRAPHICS_MAPBUFFEROBJECTTOCLIENTADDRESS)GetProcAddress(hModule, "MapBufferObjectToClientAddress");
	dooms::graphics::GraphicsAPI::ReadPixels = (GraphicsAPI::GRAPHICS_READPIXELS)GetProcAddress(hModule, "ReadPixels");
	dooms::graphics::GraphicsAPI::SetBlendFactor = (GraphicsAPI::GRAPHICS_SETBLENDFACTOR)GetProcAddress(hModule, "SetBlendFactor");
	dooms::graphics::GraphicsAPI::SetCullFace = (GraphicsAPI::GRAPHICS_SETCULLFACE)GetProcAddress(hModule, "SetCullFace");
	dooms::graphics::GraphicsAPI::SetDebugFunction = (GraphicsAPI::GRAPHICS_SETDEBUGFUNCTION)GetProcAddress(hModule, "SetDebugFunction");
	dooms::graphics::GraphicsAPI::SetDepthFunc = (GraphicsAPI::GRAPHICS_SETDEPTHFUNC)GetProcAddress(hModule, "SetDepthFunc");
	dooms::graphics::GraphicsAPI::SetDepthMask = (GraphicsAPI::GRAPHICS_SETDEPTHMASK)GetProcAddress(hModule, "SetDepthMask");
	dooms::graphics::GraphicsAPI::SetDrawBuffers = (GraphicsAPI::GRAPHICS_SETDRAWBUFFERS)GetProcAddress(hModule, "SetDrawBuffers");
	dooms::graphics::GraphicsAPI::SetFrontFaceWinding = (GraphicsAPI::GRAPHICS_SETFRONTFACEWINDING)GetProcAddress(hModule, "SetFrontFaceWinding");
	dooms::graphics::GraphicsAPI::SetIsAlphaTestEnabled = (GraphicsAPI::GRAPHICS_SETISALPHATESTENABLED)GetProcAddress(hModule, "SetIsAlphaTestEnabled");
	dooms::graphics::GraphicsAPI::SetIsBlendEnabled = (GraphicsAPI::GRAPHICS_SETISBLENDENABLED)GetProcAddress(hModule, "SetIsBlendEnabled");
	dooms::graphics::GraphicsAPI::SetIsDepthTestEnabled = (GraphicsAPI::GRAPHICS_SETISDEPTHTESTENABLED)GetProcAddress(hModule, "SetIsDepthTestEnabled");
	dooms::graphics::GraphicsAPI::SetMagFilter = (GraphicsAPI::GRAPHICS_SETMAGFILTER)GetProcAddress(hModule, "SetMagFilter");
	dooms::graphics::GraphicsAPI::SetMinFilter = (GraphicsAPI::GRAPHICS_SETMINFILTER)GetProcAddress(hModule, "SetMinFilter");
	dooms::graphics::GraphicsAPI::SetReadBuffer = (GraphicsAPI::GRAPHICS_SETREADBUFFER)GetProcAddress(hModule, "SetReadBuffer");
	dooms::graphics::GraphicsAPI::SetDrawBuffer = (GraphicsAPI::GRAPHICS_SETDRAWBUFFER)GetProcAddress(hModule, "SetDrawBuffer");
	dooms::graphics::GraphicsAPI::SetTextureParameterFloat = (GraphicsAPI::GRAPHICS_SETTEXTUREPARAMETERFLOAT)GetProcAddress(hModule, "SetTextureParameterFloat");
	dooms::graphics::GraphicsAPI::SetTextureParameterInt = (GraphicsAPI::GRAPHICS_SETTEXTUREPARAMETERINT)GetProcAddress(hModule, "SetTextureParameterInt");
	dooms::graphics::GraphicsAPI::SetTextureWrapMode_R = (GraphicsAPI::GRAPHICS_SETTEXTUREWRAPMODER)GetProcAddress(hModule, "SetTextureWrapMode_R");
	dooms::graphics::GraphicsAPI::SetTextureWrapMode_S = (GraphicsAPI::GRAPHICS_SETTEXTUREWRAPMODES)GetProcAddress(hModule, "SetTextureWrapMode_S");
	dooms::graphics::GraphicsAPI::SetTextureWrapMode_T = (GraphicsAPI::GRAPHICS_SETTEXTUREWRAPMODET)GetProcAddress(hModule, "SetTextureWrapMode_T");
	dooms::graphics::GraphicsAPI::SetViewport = (GraphicsAPI::GRAPHICS_SETVIEWPORT)GetProcAddress(hModule, "SetViewport");
	dooms::graphics::GraphicsAPI::SetVSync = (GraphicsAPI::GRAPHICS_SETVSYNC)GetProcAddress(hModule, "SetVSync");
	dooms::graphics::GraphicsAPI::SwapBuffer = (GraphicsAPI::GRAPHICS_SWAPBUFFER)GetProcAddress(hModule, "SwapBuffer");
	dooms::graphics::GraphicsAPI::UnBindBuffer = (GraphicsAPI::GRAPHICS_UNBINDBUFFER)GetProcAddress(hModule, "UnBindBuffer");
	dooms::graphics::GraphicsAPI::UnBindTextureObject = (GraphicsAPI::GRAPHICS_UNBINDTEXTUREOBJECT)GetProcAddress(hModule, "UnBindTextureObject");
	dooms::graphics::GraphicsAPI::UnBindVertexArrayObject = (GraphicsAPI::GRAPHICS_UNBINDVERTEXARRAYOBJECT)GetProcAddress(hModule, "UnBindVertexArrayObject");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool1 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERBOOL1)GetProcAddress(hModule, "UpdateConstantBuffer_bool1");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool2 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERBOOL2)GetProcAddress(hModule, "UpdateConstantBuffer_bool2");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool3 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERBOOL3)GetProcAddress(hModule, "UpdateConstantBuffer_bool3");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool4 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERBOOL4)GetProcAddress(hModule, "UpdateConstantBuffer_bool4");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float1 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERFLOAT1)GetProcAddress(hModule, "UpdateConstantBuffer_float1");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float2 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERFLOAT2)GetProcAddress(hModule, "UpdateConstantBuffer_float2");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float3 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERFLOAT3)GetProcAddress(hModule, "UpdateConstantBuffer_float3");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float4 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERFLOAT4)GetProcAddress(hModule, "UpdateConstantBuffer_float4");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int1 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERINT1)GetProcAddress(hModule, "UpdateConstantBuffer_int1");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int2 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERINT2)GetProcAddress(hModule, "UpdateConstantBuffer_int2");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int3 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERINT3)GetProcAddress(hModule, "UpdateConstantBuffer_int3");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int4 = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERINT4)GetProcAddress(hModule, "UpdateConstantBuffer_int4");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat2x2f = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERMAT2X2F)GetProcAddress(hModule, "UpdateConstantBuffer_mat2x2f");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat3x3f = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERMAT3X3F)GetProcAddress(hModule, "UpdateConstantBuffer_mat3x3f");
	dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat4x4f = (GraphicsAPI::GRAPHICS_UPDATECONSTANTBUFFERMAT4X4F)GetProcAddress(hModule, "UpdateConstantBuffer_mat4x4f");
	dooms::graphics::GraphicsAPI::UpdateDataToBuffer = (GraphicsAPI::GRAPHICS_UPDATEDATATOBUFFER)GetProcAddress(hModule, "UpdateDataToBuffer");
	dooms::graphics::GraphicsAPI::UploadPixelsTo1DCompressedTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO1DCOMPRESSEDTEXTURE)GetProcAddress(hModule, "UploadPixelsTo1DCompressedTexture");
	dooms::graphics::GraphicsAPI::UploadPixelsTo1DTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO1DTEXTURE)GetProcAddress(hModule, "UploadPixelsTo1DTexture");
	dooms::graphics::GraphicsAPI::UploadPixelsTo2DCompressedTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO2DCOMPRESSEDTEXTURE)GetProcAddress(hModule, "InitiUploadPixelsTo2DCompressedTexturealize");
	dooms::graphics::GraphicsAPI::UploadPixelsTo2DTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO2DTEXTURE)GetProcAddress(hModule, "UploadPixelsTo2DTexture");
	dooms::graphics::GraphicsAPI::UploadPixelsTo3DCompressedTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO3DCOMPRESSEDTEXTURE)GetProcAddress(hModule, "UploadPixelsTo3DCompressedTexture");
	dooms::graphics::GraphicsAPI::UploadPixelsTo3DTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO3DTEXTURE)GetProcAddress(hModule, "UploadPixelsTo3DTexture");


	dooms::input::GraphicsAPIInput::InitializeGraphisAPIInput = (dooms::input::GraphicsAPIInput::GRAPHICS_INITIALIZEGRAPHICSAPIINPUT)GetProcAddress(hModule, "InitializeGraphisAPIInput");
	dooms::input::GraphicsAPIInput::DeInitializeGraphisAPIInput = (dooms::input::GraphicsAPIInput::GRAPHICS_DEINITIALIZEGRAPHICSAPIINPUT)GetProcAddress(hModule, "DeInitializeGraphisAPIInput");
	dooms::input::GraphicsAPIInput::PollEvents = (dooms::input::GraphicsAPIInput::GRAPHICS_POLLEVENTS)GetProcAddress(hModule, "PollEvents");
	dooms::input::GraphicsAPIInput::SetCursorMode = (dooms::input::GraphicsAPIInput::GRAPHICS_SETCURSORMODE)GetProcAddress(hModule, "SetCursorMode");
	dooms::input::GraphicsAPIInput::SetCursorEnterCallback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETCURSORENTERCALLBACK)GetProcAddress(hModule, "SetCursorEnterCallback");
	dooms::input::GraphicsAPIInput::SetCursorPosition_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETCURSORPOSITIONCALLBACK)GetProcAddress(hModule, "SetCursorPosition_Callback");
	dooms::input::GraphicsAPIInput::SetScroll_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETSCROLLCALLBACK)GetProcAddress(hModule, "SetScroll_Callback");
	dooms::input::GraphicsAPIInput::SetKey_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETKEYCALLBACK)GetProcAddress(hModule, "SetKey_Callback");
	dooms::input::GraphicsAPIInput::SetMouseButton_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETMOUSEBUTTONCALLBACK)GetProcAddress(hModule, "SetMouseButton_Callback");


	dooms::graphics::PlatformImgui::InitializePlatformImgui = (PlatformImgui::GRAPHICS_INITIALIZEPLATFORMIMGUI)GetProcAddress(hModule, "InitializePlatformImgui");
	dooms::graphics::PlatformImgui::ShutDownPlatformImgui = (PlatformImgui::GRAPHICS_SHUTDOWNPLATFORMIMGUI)GetProcAddress(hModule, "ShutDownPlatformImgui");
	dooms::graphics::PlatformImgui::PreRenderPlatformImgui = (PlatformImgui::GRAPHICS_PRERENDERPLATFORMIMGUI)GetProcAddress(hModule, "PreRenderPlatformImgui");
	dooms::graphics::PlatformImgui::PostRenderPlatformImgui = (PlatformImgui::GRAPHICS_POSTRENDERPLATFORMIMGUI)GetProcAddress(hModule, "PostRenderPlatformImgui");

}

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
