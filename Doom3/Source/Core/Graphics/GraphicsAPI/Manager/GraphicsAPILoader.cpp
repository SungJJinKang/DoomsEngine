#include "GraphicsAPILoader.h"

#include <cassert>
#include <string>

#include <Windows.h>

#include "GraphicsAPIManager.h"
#include "EngineGUI/PrintText.h"
#include "../GraphicsAPI.h"
#include "../Input/GraphicsAPIInput.h"
#include "../PlatformImgui/PlatformImgui.h"
#include <Macros/Path.h>

#define OPENGL_DLL_FILE_NAME TEXT("OpenGLGraphicsAPI.dll")
#define DX11_DLL_FILE_NAME TEXT("DX11GraphicsAPI.dll")
#define DW_FLAGS 0x00000000

void dooms::graphics::GraphicsAPILoader::FetchExportedFunctionAddress()
{
	D_ASSERT(mAPIModule != nullptr);
	HMODULE hModule = reinterpret_cast<HMODULE>(mAPIModule);

	
	dooms::graphics::GraphicsAPI::FlushCMDQueue = (GraphicsAPI::GRAPHICS_FLUSH_CMD_QUEUE)GetProcAddress(hModule, "FlushCMDQueue");
	//D_ASSERT(dooms::graphics::GraphicsAPI::FlushCMDQueue != nullptr);
	dooms::graphics::GraphicsAPI::GetCurrentAPIType = (GraphicsAPI::GRAPHICS_GETCURRENTAPITYPE)GetProcAddress(hModule, "GetCurrentAPIType");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetCurrentAPIType != nullptr);
	dooms::graphics::GraphicsAPI::ActivateTextureUnit = (GraphicsAPI::GRAPHICS_ACTIVATETEXTUREUNIT)GetProcAddress(hModule, "ActivateTextureUnit");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ActivateTextureUnit != nullptr);
	dooms::graphics::GraphicsAPI::CreateBufferObject = (GraphicsAPI::GRAPHICS_ALLOCATEBUFFERMEMORY)GetProcAddress(hModule, "CreateBufferObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateBufferObject != nullptr);
	dooms::graphics::GraphicsAPI::AllocateRenderBufferMemory = (GraphicsAPI::GRAPHICS_ALLOCATERENDERBUFFERMEMORY)GetProcAddress(hModule, "AllocateRenderBufferMemory");
	//D_ASSERT(dooms::graphics::GraphicsAPI::AllocateRenderBufferMemory != nullptr);
	dooms::graphics::GraphicsAPI::Attach2DColorTextureToFrameBuffer = (GraphicsAPI::GRAPHICS_ATTACH2DCOLORTEXTURETOFRAMEBUFFER)GetProcAddress(hModule, "Attach2DColorTextureToFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::Attach2DColorTextureToFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::Attach2DDepthStencilTextureToFrameBuffer = (GraphicsAPI::GRAPHICS_ATTACH2DDEPTHSTENCILTEXTURETOFRAMEBUFFER)GetProcAddress(hModule, "Attach2DDepthStencilTextureToFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::Attach2DDepthStencilTextureToFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::CopyRenderTargetView = (GraphicsAPI::GRAPHICS_COPYRENDERTARGETVIEW)GetProcAddress(hModule, "CopyRenderTargetView");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CopyRenderTargetView != nullptr);
	dooms::graphics::GraphicsAPI::AttachRenderBufferToFrameBuffer = (GraphicsAPI::GRAPHICS_ATTACHRENDERBUFFERTOFRAMEBUFFER)GetProcAddress(hModule, "AttachRenderBufferToFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::AttachRenderBufferToFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::AttachShaderToMaterial = (GraphicsAPI::GRAPHICS_ATTACHSHADERTOMATERIAL)GetProcAddress(hModule, "AttachShaderToMaterial");
	//D_ASSERT(dooms::graphics::GraphicsAPI::AttachShaderToMaterial != nullptr);
	dooms::graphics::GraphicsAPI::DetachShaderFromMaterial = (GraphicsAPI::GRAPHICS_DETACHSHADERFROMMATERIAL)GetProcAddress(hModule, "DetachShaderToMaterial");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DetachShaderToMaterial != nullptr);
	dooms::graphics::GraphicsAPI::BindVertexDataBuffer = (GraphicsAPI::GRAPHICS_BINDVERTEXDATABUFFER)GetProcAddress(hModule, "BindVertexDataBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindVertexDataBuffer != nullptr);
	dooms::graphics::GraphicsAPI::BindBuffer = (GraphicsAPI::GRAPHICS_BINDBUFFER)GetProcAddress(hModule, "BindBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindBuffer != nullptr);
	dooms::graphics::GraphicsAPI::BindInputLayoutForD3D = (GraphicsAPI::GRAPHICS_BINDINPUTLAYOUTFORD3D)GetProcAddress(hModule, "BindInputLayoutForD3D");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindInputLayoutForD3D != nullptr);
	dooms::graphics::GraphicsAPI::BindConstantBuffer = (GraphicsAPI::GRAPHICS_BINDCONSTANTBUFFER)GetProcAddress(hModule, "BindConstantBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindConstantBuffer != nullptr);
	dooms::graphics::GraphicsAPI::BindFrameBuffer = (GraphicsAPI::GRAPHICS_BINDFRAMEBUFFER)GetProcAddress(hModule, "BindFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::BindBackBuffer = (GraphicsAPI::GRAPHICS_BINDBACKBUFFER)GetProcAddress(hModule, "BindBackBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindBackBuffer != nullptr);
	dooms::graphics::GraphicsAPI::BindShader = (GraphicsAPI::GRAPHICS_BINDMATERIAL)GetProcAddress(hModule, "BindShader");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindShader != nullptr);
	dooms::graphics::GraphicsAPI::BindRenderBuffer = (GraphicsAPI::GRAPHICS_BINDRENDERBUFFER)GetProcAddress(hModule, "BindRenderBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindRenderBuffer != nullptr);
	dooms::graphics::GraphicsAPI::BindTextureObject = (GraphicsAPI::GRAPHICS_BINDTEXTUREOBJECT)GetProcAddress(hModule, "BindTextureObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindTextureObject != nullptr);
	dooms::graphics::GraphicsAPI::BindTextureObjectAndActivateTextureUnit = (GraphicsAPI::GRAPHICS_BINDTEXTUREOBJECTANDACTIVATETEXTUREUNIT)GetProcAddress(hModule, "BindTextureObjectAndActivateTextureUnit");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindTextureObjectAndActivateTextureUnit != nullptr);
	dooms::graphics::GraphicsAPI::BindVertexArrayObject = (GraphicsAPI::GRAPHICS_BINDVERTEXARRAYOBJECT)GetProcAddress(hModule, "BindVertexArrayObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindVertexArrayObject != nullptr);
	dooms::graphics::GraphicsAPI::BindIndexBufferObject = (GraphicsAPI::GRAPHICS_BINDINDEXBUFFEROBJECT)GetProcAddress(hModule, "BindIndexBufferObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindIndexBufferObject != nullptr);
	dooms::graphics::GraphicsAPI::BlitFrameBuffer = (GraphicsAPI::GRAPHICS_BLITFRAMEBUFFER)GetProcAddress(hModule, "BlitFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BlitFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::CheckFrameBufferIsSuccesfullyCreated = (GraphicsAPI::GRAPHICS_CHECKFRAMEBUFFERISSUCCESFULLYCREATED)GetProcAddress(hModule, "CheckFrameBufferIsSuccesfullyCreated");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CheckFrameBufferIsSuccesfullyCreated != nullptr);
	dooms::graphics::GraphicsAPI::ClearBackFrameBufferColorBuffer = (GraphicsAPI::GRAPHICS_CLEARBACKFRAMEBUFFERCOLORBUFFER)GetProcAddress(hModule, "ClearBackFrameBufferColorBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearBackFrameBufferColorBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearBackFrameBufferDepthBuffer = (GraphicsAPI::GRAPHICS_CLEARBACKFRAMEBUFFERDEPTHBUFFER)GetProcAddress(hModule, "ClearBackFrameBufferDepthBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearBackFrameBufferDepthBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearBackFrameBufferStencilBuffer = (GraphicsAPI::GRAPHICS_CLEARBACKFRAMEBUFFERSTENCILBUFFER)GetProcAddress(hModule, "ClearBackFrameBufferStencilBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearBackFrameBufferStencilBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearBackFrameBufferDepthStencilBuffer = (GraphicsAPI::GRAPHICS_CLEARBACKFRAMEBUFFERDEPTHSTENCILBUFFER)GetProcAddress(hModule, "ClearBackFrameBufferDepthStencilBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearBackFrameBufferStencilBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearFrameBufferColorBuffer = (GraphicsAPI::GRAPHICS_CLEARFRAMEBUFFERCOLORBUFFER)GetProcAddress(hModule, "ClearFrameBufferColorBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearFrameBufferColorBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearFrameBufferDepthBuffer = (GraphicsAPI::GRAPHICS_CLEARFRAMEBUFFERDEPTHBUFFER)GetProcAddress(hModule, "ClearFrameBufferDepthBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearFrameBufferDepthBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearFrameBufferStencilBuffer = (GraphicsAPI::GRAPHICS_CLEARFRAMEBUFFERSTENCILBUFFER)GetProcAddress(hModule, "ClearFrameBufferStencilBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearFrameBufferStencilBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearFrameBufferDepthStencilBuffer = (GraphicsAPI::GRAPHICS_CLEARFRAMEBUFFERDEPTHSTENCILBUFFER)GetProcAddress(hModule, "ClearFrameBufferStencilBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearFrameBufferDepthStencilBuffer != nullptr);
	dooms::graphics::GraphicsAPI::ClearSpecificBuffer = (GraphicsAPI::GRAPHICS_CLEARSPECIFICBUFFER)GetProcAddress(hModule, "ClearSpecificBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ClearSpecificBuffer != nullptr);
	dooms::graphics::GraphicsAPI::CompileShader = (GraphicsAPI::GRAPHICS_COMPILESHADER)GetProcAddress(hModule, "CompileShader");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CompileShader != nullptr);

	dooms::graphics::GraphicsAPI::CreateInputLayoutForD3D = (GraphicsAPI::GRAPHICS_CREATEINPUTLAYOUTFORD3D)GetProcAddress(hModule, "CreateInputLayoutForD3D");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateInputLayoutForD3D != nullptr);
	dooms::graphics::GraphicsAPI::BindInputLayoutForD3D = (GraphicsAPI::GRAPHICS_BINDINPUTLAYOUTFORD3D)GetProcAddress(hModule, "BindInputLayoutForD3D");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindInputLayoutForD3D != nullptr);
	dooms::graphics::GraphicsAPI::DestoryInputLayoutForD3D = (GraphicsAPI::GRAPHICS_DESTORYINPUTLAYOUTFORD3D)GetProcAddress(hModule, "DestoryInputLayoutForD3D");
	//D_ASSERT(dooms::graphics::GraphicsAPI::BindInputLayoutForD3D != nullptr);

	/*
	dooms::graphics::GraphicsAPI::CompileShaders = (GraphicsAPI::GRAPHICS_COMPILESHADERS)GetProcAddress(hModule, "CompileShaders");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CompileShaders != nullptr);
	*/
	
	dooms::graphics::GraphicsAPI::CreateMaterial = (GraphicsAPI::GRAPHICS_CREATEMATERIAL)GetProcAddress(hModule, "CreateMaterial");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateMaterial != nullptr);
	dooms::graphics::GraphicsAPI::CreateRenderBufferObject = (GraphicsAPI::GRAPHICS_CREATERENDERBUFFEROBJECT)GetProcAddress(hModule, "CreateRenderBufferObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateRenderBufferObject != nullptr);
	dooms::graphics::GraphicsAPI::CreateShaderObject = (GraphicsAPI::GRAPHICS_CREATESHADEROBJECT)GetProcAddress(hModule, "CreateShaderObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateShaderObject != nullptr);
	dooms::graphics::GraphicsAPI::CreateTextureObject = (GraphicsAPI::GRAPHICS_CREATEXTUREOBJECT)GetProcAddress(hModule, "CreateTextureObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateTextureObject != nullptr);
	dooms::graphics::GraphicsAPI::CreateTextureViewObject = (GraphicsAPI::GRAPHICS_CREATETEXTUREVIEWOBJECT)GetProcAddress(hModule, "CreateTextureViewObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateTextureViewObject != nullptr);
	dooms::graphics::GraphicsAPI::CreateVertexArrayObject = (GraphicsAPI::GRAPHICS_CREATEVERTEXARRAYOBJECT)GetProcAddress(hModule, "CreateVertexArrayObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::CreateVertexArrayObject != nullptr);
	dooms::graphics::GraphicsAPI::Allocate2DTextureObject = (GraphicsAPI::GRAPHICS_ALLOCATE2DTEXTUREOBJECT)GetProcAddress(hModule, "Allocate2DTextureObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::Allocate2DTextureObject != nullptr);
	dooms::graphics::GraphicsAPI::DefineVertexAttributeLayout = (GraphicsAPI::GRAPHICS_DEFINEVERTEXATTRIBUTELAYOUT)GetProcAddress(hModule, "DefineVertexAttributeLayout");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DefineVertexAttributeLayout != nullptr);
	dooms::graphics::GraphicsAPI::DeinitializeGraphicsAPI = (GraphicsAPI::GRAPHICS_DEINITIALIZEGRAPHICSAPI)GetProcAddress(hModule, "DeinitializeGraphicsAPI");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DeinitializeGraphicsAPI != nullptr);
	dooms::graphics::GraphicsAPI::DestroyBuffer = (GraphicsAPI::GRAPHICS_DESTROYBUFFER)GetProcAddress(hModule, "DestroyBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyBuffer != nullptr);
	dooms::graphics::GraphicsAPI::DestroyFrameBuffer = (GraphicsAPI::GRAPHICS_DESTROYFRAMEBUFFER)GetProcAddress(hModule, "DestroyFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::DestroyMaterial = (GraphicsAPI::GRAPHICS_DESTROYMATERIAL)GetProcAddress(hModule, "DestroyMaterial");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyMaterial != nullptr);
	dooms::graphics::GraphicsAPI::DestroyRenderBuffer = (GraphicsAPI::GRAPHICS_DESTROYRENDERBUFFER)GetProcAddress(hModule, "DestroyRenderBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyRenderBuffer != nullptr);
	dooms::graphics::GraphicsAPI::DestroyShaderObject = (GraphicsAPI::GRAPHICS_DESTROYSHADEROBJECT)GetProcAddress(hModule, "DestroyShaderObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyShaderObject != nullptr);
	dooms::graphics::GraphicsAPI::DestroyTextureObject = (GraphicsAPI::GRAPHICS_DESTROYTEXTUREOBJECT)GetProcAddress(hModule, "DestroyTextureObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyTextureObject != nullptr);
	dooms::graphics::GraphicsAPI::DestroyTextureViewObject = (GraphicsAPI::GRAPHICS_DESTROYTEXTUREVIEWOBJECT)GetProcAddress(hModule, "DestroyTextureViewObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyTextureViewObject != nullptr);
	dooms::graphics::GraphicsAPI::DestroyVertexArrayObject = (GraphicsAPI::GRAPHICS_DESTROYVERTEXARRAYOBJECT)GetProcAddress(hModule, "DestroyVertexArrayObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DestroyVertexArrayObject != nullptr);
	dooms::graphics::GraphicsAPI::Draw = (GraphicsAPI::GRAPHICS_DRAW)GetProcAddress(hModule, "Draw");
	//D_ASSERT(dooms::graphics::GraphicsAPI::Draw != nullptr);
	dooms::graphics::GraphicsAPI::DrawIndexed = (GraphicsAPI::GRAPHICS_DRAWINDEXED)GetProcAddress(hModule, "DrawIndexed");
	//D_ASSERT(dooms::graphics::GraphicsAPI::DrawIndexed != nullptr);
	dooms::graphics::GraphicsAPI::EnableVertexAttributeArrayIndex = (GraphicsAPI::GRAPHICS_ENABLEVERTEXATTRIBUTEARRAYINDEX)GetProcAddress(hModule, "EnableVertexAttributeArrayIndex");
	//D_ASSERT(dooms::graphics::GraphicsAPI::EnableVertexAttributeArrayIndex != nullptr);
	dooms::graphics::GraphicsAPI::FetchTexturePixels = (GraphicsAPI::GRAPHICS_FETCHTEXTUREPIXELS)GetProcAddress(hModule, "FetchTexturePixels");
	//D_ASSERT(dooms::graphics::GraphicsAPI::FetchTexturePixels != nullptr);
	dooms::graphics::GraphicsAPI::GenerateFrameBuffer = (GraphicsAPI::GRAPHICS_GENERATEFRAMEBUFFER)GetProcAddress(hModule, "GenerateFrameBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GenerateFrameBuffer != nullptr);
	dooms::graphics::GraphicsAPI::GetConstantBufferBindingPoint = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERBINDINGPOINT)GetProcAddress(hModule, "GetConstantBufferBindingPoint");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetConstantBufferBindingPoint != nullptr);
	dooms::graphics::GraphicsAPI::GetConstantBufferBlockCount = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERBLOCKCOUNT)GetProcAddress(hModule, "GetConstantBufferBlockCount");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetConstantBufferBlockCount != nullptr);
	dooms::graphics::GraphicsAPI::GetConstantBufferDataSize = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERDATASIZE)GetProcAddress(hModule, "GetConstantBufferDataSize");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetConstantBufferDataSize != nullptr);
	dooms::graphics::GraphicsAPI::GetConstantBufferUniformLocation = (GraphicsAPI::GRAPHICS_GETCONSTANTBUFFERUNIFORMLOCATION)GetProcAddress(hModule, "GetConstantBufferUniformLocation");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetConstantBufferUniformLocation != nullptr);
	dooms::graphics::GraphicsAPI::GetDrawCall = (GraphicsAPI::GRAPHICS_GETDRAWCALL)GetProcAddress(hModule, "GetDrawCall");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetDrawCall != nullptr);
	dooms::graphics::GraphicsAPI::GetDebugFunction = (GraphicsAPI::GRAPHICS_GETDEBUGFUNCTION)GetProcAddress(hModule, "GetDebugFunction");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetDebugFunction != nullptr);
	dooms::graphics::GraphicsAPI::GetFrameBufferHeight = (GraphicsAPI::GRAPHICS_GETFRAMEBUFFERHEIGHT)GetProcAddress(hModule, "GetFrameBufferHeight");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetFrameBufferHeight != nullptr);
	dooms::graphics::GraphicsAPI::GetFrameBufferWidth = (GraphicsAPI::GRAPHICS_GETFRAMEBUFFERWIDTH)GetProcAddress(hModule, "GetFrameBufferWidth");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetFrameBufferWidth != nullptr);
	dooms::graphics::GraphicsAPI::GetPlatformVersion = (GraphicsAPI::GRAPHICS_GETPLATFORMVERSION)GetProcAddress(hModule, "GetPlatformVersion");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetPlatformVersion != nullptr);
	dooms::graphics::GraphicsAPI::GetPlatformWindow = (GraphicsAPI::GRAPHICS_GETPLATFORMWINDOW)GetProcAddress(hModule, "GetPlatformWindow");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetPlatformWindow != nullptr);
	dooms::graphics::GraphicsAPI::GetTextureMetaDataFloat = (GraphicsAPI::GRAPHICS_GETTEXTUREMETADATAFLOAT)GetProcAddress(hModule, "GetTextureMetaDataFloat");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetTextureMetaDataFloat != nullptr);
	dooms::graphics::GraphicsAPI::GetTextureMetaDataInt = (GraphicsAPI::GRAPHICS_GETTEXTUREMETADATAINT)GetProcAddress(hModule, "GetTextureMetaDataInt");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetTextureMetaDataInt != nullptr);
	dooms::graphics::GraphicsAPI::GetViewPort = (GraphicsAPI::GRAPHICS_GETVIEWPORT)GetProcAddress(hModule, "GetViewPort");
	//D_ASSERT(dooms::graphics::GraphicsAPI::GetViewPort != nullptr);
	dooms::graphics::GraphicsAPI::InitializeGraphicsAPI = (GraphicsAPI::GRAPHICS_INITIALIZEGRAPHICSAPI)GetProcAddress(hModule, "InitializeGraphicsAPI");
	//D_ASSERT(dooms::graphics::GraphicsAPI::InitializeGraphicsAPI != nullptr);
	dooms::graphics::GraphicsAPI::LinkMaterial = (GraphicsAPI::GRAPHICS_LINKMATERIAL)GetProcAddress(hModule, "LinkMaterial");
	//D_ASSERT(dooms::graphics::GraphicsAPI::LinkMaterial != nullptr);
	dooms::graphics::GraphicsAPI::MapBufferObjectToClientAddress = (GraphicsAPI::GRAPHICS_MAPBUFFEROBJECTTOCLIENTADDRESS)GetProcAddress(hModule, "MapBufferObjectToClientAddress");
	//D_ASSERT(dooms::graphics::GraphicsAPI::MapBufferObjectToClientAddress != nullptr);
	dooms::graphics::GraphicsAPI::RangedMapBufferObjectToClientAddress = (GraphicsAPI::GRAPHICS_RANGEDMAPBUFFEROBJECTTOCLIENTADDRESS)GetProcAddress(hModule, "RangedMapBufferObjectToClientAddress");
	//D_ASSERT(dooms::graphics::GraphicsAPI::RangedMapBufferObjectToClientAddress != nullptr);
	dooms::graphics::GraphicsAPI::UnMapBufferObjectMappedToClientAddress = (GraphicsAPI::GRAPHICS_UNMAPBUFFEROBJECMAPPEDTTOCLIENTADDRESS)GetProcAddress(hModule, "UnMapBufferObjectMappedToClientAddress");
	//D_ASSERT(dooms::graphics::GraphicsAPI::UnMapBufferObjectMappedToClientAddress != nullptr);
	dooms::graphics::GraphicsAPI::ReadPixels = (GraphicsAPI::GRAPHICS_READPIXELS)GetProcAddress(hModule, "ReadPixels");
	//D_ASSERT(dooms::graphics::GraphicsAPI::ReadPixels != nullptr);
	dooms::graphics::GraphicsAPI::SetBlendFactor = (GraphicsAPI::GRAPHICS_SETBLENDFACTOR)GetProcAddress(hModule, "SetBlendFactor");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetBlendFactor != nullptr);
	dooms::graphics::GraphicsAPI::SetCullFace = (GraphicsAPI::GRAPHICS_SETCULLFACE)GetProcAddress(hModule, "SetCullFace");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetCullFace != nullptr);
	dooms::graphics::GraphicsAPI::SetDebugFunction = (GraphicsAPI::GRAPHICS_SETDEBUGFUNCTION)GetProcAddress(hModule, "SetDebugFunction");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetDebugFunction != nullptr);
	dooms::graphics::GraphicsAPI::SetDepthFunc = (GraphicsAPI::GRAPHICS_SETDEPTHFUNC)GetProcAddress(hModule, "SetDepthFunc");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetDepthFunc != nullptr);
	dooms::graphics::GraphicsAPI::SetDepthMask = (GraphicsAPI::GRAPHICS_SETDEPTHMASK)GetProcAddress(hModule, "SetDepthMask");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetDepthMask != nullptr);
	
	/*
	dooms::graphics::GraphicsAPI::SetDrawBuffers = (GraphicsAPI::GRAPHICS_SETDRAWBUFFERS)GetProcAddress(hModule, "SetDrawBuffers");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetDrawBuffers != nullptr);
	*/

	dooms::graphics::GraphicsAPI::SetFrontFaceWinding = (GraphicsAPI::GRAPHICS_SETFRONTFACEWINDING)GetProcAddress(hModule, "SetFrontFaceWinding");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetFrontFaceWinding != nullptr);
	dooms::graphics::GraphicsAPI::SetIsAlphaTestEnabled = (GraphicsAPI::GRAPHICS_SETISALPHATESTENABLED)GetProcAddress(hModule, "SetIsAlphaTestEnabled");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetIsAlphaTestEnabled != nullptr);
	dooms::graphics::GraphicsAPI::SetIsBlendEnabled = (GraphicsAPI::GRAPHICS_SETISBLENDENABLED)GetProcAddress(hModule, "SetIsBlendEnabled");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetIsBlendEnabled != nullptr);
	dooms::graphics::GraphicsAPI::SetIsDepthTestEnabled = (GraphicsAPI::GRAPHICS_SETISDEPTHTESTENABLED)GetProcAddress(hModule, "SetIsDepthTestEnabled");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetIsDepthTestEnabled != nullptr);
	dooms::graphics::GraphicsAPI::SetIsStencilTestEnabled = (GraphicsAPI::GRAPHICS_SETISSTENCILTESTENABLED)GetProcAddress(hModule, "SetIsStencilTestEnabled");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetIsStencilTestEnabled != nullptr);
	dooms::graphics::GraphicsAPI::SetIsStencilFunc = (GraphicsAPI::GRAPHICS_SETISSTENCILFUNC)GetProcAddress(hModule, "SetIsStencilFunc");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetIsStencilFunc != nullptr);
	dooms::graphics::GraphicsAPI::SetIsStencilOp = (GraphicsAPI::GRAPHICS_SETISSTENCILOP)GetProcAddress(hModule, "SetIsStencilOp");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetIsStencilOp != nullptr);\
	
	dooms::graphics::GraphicsAPI::SetMagFilter = (GraphicsAPI::GRAPHICS_SETMAGFILTER)GetProcAddress(hModule, "SetMagFilter");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetMagFilter != nullptr);
	dooms::graphics::GraphicsAPI::SetMinFilter = (GraphicsAPI::GRAPHICS_SETMINFILTER)GetProcAddress(hModule, "SetMinFilter");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetMinFilter != nullptr);

	/*
	dooms::graphics::GraphicsAPI::SetReadBuffer = (GraphicsAPI::GRAPHICS_SETREADBUFFER)GetProcAddress(hModule, "SetReadBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetReadBuffer != nullptr);
	dooms::graphics::GraphicsAPI::SetDrawBuffer = (GraphicsAPI::GRAPHICS_SETDRAWBUFFER)GetProcAddress(hModule, "SetDrawBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetDrawBuffer != nullptr);
	*/

	dooms::graphics::GraphicsAPI::SetTextureParameterFloat = (GraphicsAPI::GRAPHICS_SETTEXTUREPARAMETERFLOAT)GetProcAddress(hModule, "SetTextureParameterFloat");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetTextureParameterFloat != nullptr);
	dooms::graphics::GraphicsAPI::SetTextureParameterInt = (GraphicsAPI::GRAPHICS_SETTEXTUREPARAMETERINT)GetProcAddress(hModule, "SetTextureParameterInt");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetTextureParameterInt != nullptr);
	dooms::graphics::GraphicsAPI::SetTextureWrapMode_R = (GraphicsAPI::GRAPHICS_SETTEXTUREWRAPMODER)GetProcAddress(hModule, "SetTextureWrapMode_R");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetTextureWrapMode_R != nullptr);
	dooms::graphics::GraphicsAPI::SetTextureWrapMode_S = (GraphicsAPI::GRAPHICS_SETTEXTUREWRAPMODES)GetProcAddress(hModule, "SetTextureWrapMode_S");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetTextureWrapMode_S != nullptr);
	dooms::graphics::GraphicsAPI::SetTextureWrapMode_T = (GraphicsAPI::GRAPHICS_SETTEXTUREWRAPMODET)GetProcAddress(hModule, "SetTextureWrapMode_T");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetTextureWrapMode_T != nullptr);
	dooms::graphics::GraphicsAPI::SetViewport = (GraphicsAPI::GRAPHICS_SETVIEWPORT)GetProcAddress(hModule, "SetViewport");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetViewport != nullptr);
	dooms::graphics::GraphicsAPI::SetVSync = (GraphicsAPI::GRAPHICS_SETVSYNC)GetProcAddress(hModule, "SetVSync");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetVSync != nullptr);
	dooms::graphics::GraphicsAPI::SwapBuffer = (GraphicsAPI::GRAPHICS_SWAPBUFFER)GetProcAddress(hModule, "SwapBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SwapBuffer != nullptr);
	dooms::graphics::GraphicsAPI::UnBindBuffer = (GraphicsAPI::GRAPHICS_UNBINDBUFFER)GetProcAddress(hModule, "UnBindBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::UnBindBuffer != nullptr);
	dooms::graphics::GraphicsAPI::UnBindTextureObject = (GraphicsAPI::GRAPHICS_UNBINDTEXTUREOBJECT)GetProcAddress(hModule, "UnBindTextureObject");
	//D_ASSERT(dooms::graphics::GraphicsAPI::UnBindTextureObject != nullptr);
	dooms::graphics::GraphicsAPI::UpdateDataToBuffer = (GraphicsAPI::GRAPHICS_UPDATEDATATOBUFFER)GetProcAddress(hModule, "UpdateDataToBuffer");
	//D_ASSERT(dooms::graphics::GraphicsAPI::UpdateDataToBuffer != nullptr);
	dooms::graphics::GraphicsAPI::UploadPixelsTo2DTexture = (GraphicsAPI::GRAPHICS_UPDATEPIXELSTO2DTEXTURE)GetProcAddress(hModule, "UploadPixelsTo2DTexture");
	//D_ASSERT(dooms::graphics::GraphicsAPI::UploadPixelsTo2DTexture != nullptr);
	dooms::graphics::GraphicsAPI::SetWindowTitle = (GraphicsAPI::GRAPHICS_SETWINDOWTITLE)GetProcAddress(hModule, "SetWindowTitle");
	//D_ASSERT(dooms::graphics::GraphicsAPI::SetWindowTitle != nullptr);

	dooms::input::GraphicsAPIInput::InitializeGraphisAPIInput = (dooms::input::GraphicsAPIInput::GRAPHICS_INITIALIZEGRAPHICSAPIINPUT)GetProcAddress(hModule, "InitializeGraphisAPIInput");
	//D_ASSERT(dooms::input::GraphicsAPIInput::InitializeGraphisAPIInput != nullptr);
	dooms::input::GraphicsAPIInput::DeInitializeGraphisAPIInput = (dooms::input::GraphicsAPIInput::GRAPHICS_DEINITIALIZEGRAPHICSAPIINPUT)GetProcAddress(hModule, "DeInitializeGraphisAPIInput");
	//D_ASSERT(dooms::input::GraphicsAPIInput::DeInitializeGraphisAPIInput != nullptr);
	dooms::input::GraphicsAPIInput::PollEvents = (dooms::input::GraphicsAPIInput::GRAPHICS_POLLEVENTS)GetProcAddress(hModule, "PollEvents");
	//D_ASSERT(dooms::input::GraphicsAPIInput::PollEvents != nullptr);
	dooms::input::GraphicsAPIInput::SetCursorMode = (dooms::input::GraphicsAPIInput::GRAPHICS_SETCURSORMODE)GetProcAddress(hModule, "SetCursorMode");
	//D_ASSERT(dooms::input::GraphicsAPIInput::SetCursorMode != nullptr);
	dooms::input::GraphicsAPIInput::SetCursorEnterCallback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETCURSORENTERCALLBACK)GetProcAddress(hModule, "SetCursorEnterCallback");
	//D_ASSERT(dooms::input::GraphicsAPIInput::SetCursorEnterCallback != nullptr);
	dooms::input::GraphicsAPIInput::SetCursorPosition_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETCURSORPOSITIONCALLBACK)GetProcAddress(hModule, "SetCursorPosition_Callback");
	//D_ASSERT(dooms::input::GraphicsAPIInput::SetCursorPosition_Callback != nullptr);
	dooms::input::GraphicsAPIInput::SetScroll_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETSCROLLCALLBACK)GetProcAddress(hModule, "SetScroll_Callback");
	//D_ASSERT(dooms::input::GraphicsAPIInput::SetScroll_Callback != nullptr);
	dooms::input::GraphicsAPIInput::SetKey_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETKEYCALLBACK)GetProcAddress(hModule, "SetKey_Callback");
	//D_ASSERT(dooms::input::GraphicsAPIInput::SetKey_Callback != nullptr);
	dooms::input::GraphicsAPIInput::SetMouseButton_Callback = (dooms::input::GraphicsAPIInput::GRAPHICS_SETMOUSEBUTTONCALLBACK)GetProcAddress(hModule, "SetMouseButton_Callback");
	//D_ASSERT(dooms::input::GraphicsAPIInput::SetMouseButton_Callback != nullptr);
	dooms::input::GraphicsAPIInput::GetKeyCurrentAction = (dooms::input::GraphicsAPIInput::GRAPHICS_GETKEYCURRENTACTION)GetProcAddress(hModule, "GetKeyCurrentAction");
	//D_ASSERT(dooms::input::GraphicsAPIInput::GetKeyCurrentAction != nullptr);

	dooms::graphics::PlatformImgui::InitializePlatformImgui = (PlatformImgui::GRAPHICS_INITIALIZEPLATFORMIMGUI)GetProcAddress(hModule, "InitializePlatformImgui");
	//D_ASSERT(dooms::graphics::PlatformImgui::InitializePlatformImgui != nullptr);
	dooms::graphics::PlatformImgui::ShutDownPlatformImgui = (PlatformImgui::GRAPHICS_SHUTDOWNPLATFORMIMGUI)GetProcAddress(hModule, "ShutDownPlatformImgui");
	//D_ASSERT(dooms::graphics::PlatformImgui::ShutDownPlatformImgui != nullptr);
	dooms::graphics::PlatformImgui::PreRenderPlatformImgui = (PlatformImgui::GRAPHICS_PRERENDERPLATFORMIMGUI)GetProcAddress(hModule, "PreRenderPlatformImgui");
	//D_ASSERT(dooms::graphics::PlatformImgui::PreRenderPlatformImgui != nullptr);
	dooms::graphics::PlatformImgui::PostRenderPlatformImgui = (PlatformImgui::GRAPHICS_POSTRENDERPLATFORMIMGUI)GetProcAddress(hModule, "PostRenderPlatformImgui");
	//D_ASSERT(dooms::graphics::PlatformImgui::PostRenderPlatformImgui != nullptr);

}

unsigned int dooms::graphics::GraphicsAPILoader::FreeGraphicsAPILibrary()
{
	bool isFreeLibrarySuccess = false;
	if (mAPIModule != nullptr)
	{
		isFreeLibrarySuccess = FreeLibrary(reinterpret_cast<HMODULE>(mAPIModule));      //2: unload the DLL
		D_ASSERT(isFreeLibrarySuccess == true);
		if(isFreeLibrarySuccess == true)
		{
			mAPIModule = nullptr;
		}
	}
	else
	{
		isFreeLibrarySuccess = true;
	}
	return isFreeLibrarySuccess == true ? 1 : 0;
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
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType
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
	case GraphicsAPI::eGraphicsAPIType::OpenGL:
		dllFileName = OPENGL_DLL_FILE_NAME;
		break;

	case GraphicsAPI::eGraphicsAPIType::DX11_10: 
		dllFileName = DX11_DLL_FILE_NAME;
		break;

	default: 
		assert(false);
	}

#ifdef UNICODE
	dllFileName = dooms::path::_GetCurrentPathUnicode(dllFileName);
#else
	dllFileName = dooms::path::_GetCurrentPath(dllFileName);
#endif

#ifdef UNICODE
	mAPIModule = LoadLibraryExW(dllFileName.c_str(), NULL, DW_FLAGS);
#else
	mAPIModule = LoadLibraryExA(dllFileName.c_str(), NULL, dwFlags);
#endif
	
	if (mAPIModule == NULL)
	{//FAIL
		const DWORD errorCode = GetLastError();

		D_ASSERT_LOG(false, "Fail to Load Graphics API Library - Error Code : %d", errorCode);
		dooms::ui::PrintText("Fail to Load Graphics API Library - Error Code : %d", errorCode);
	}
	else
	{
		FetchExportedFunctionAddress();
	}

	return mAPIModule;
}

bool dooms::graphics::GraphicsAPILoader::UnLoadGraphicsAPILibrary()
{
	return FreeGraphicsAPILibrary();
}
