#include "../GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		namespace GraphicsAPI
		{
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETDEBUGFUNCTION GetDebugFunction{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETDRAWCALL GetDrawCall{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETDEBUGFUNCTION SetDebugFunction{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETPLATFORMVERSION GetPlatformVersion{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETPLATFORMWINDOW GetPlatformWindow{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETTIME GetTime{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_INITIALIZEGRAPHICSAPI InitializeGraphicsAPI{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEINITIALIZEGRAPHICSAPI DeinitializeGraphicsAPI{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SWAPBUFFER SwapBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETVSYNC SetVSync{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETISDEPTHTESTENABLED SetIsDepthTestEnabled{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETISSTENCILTESTENABLED SetIsStencilTestEnabled{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETISSTENCILOP SetIsStencilOp{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETISSTENCILFUNC SetIsStencilFunc{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETDEPTHFUNC SetDepthFunc{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETDEPTHMASK SetDepthMask{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETISALPHATESTENABLED SetIsAlphaTestEnabled{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETISBLENDENABLED SetIsBlendEnabled{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETVIEWPORT SetViewport{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETVIEWPORT GetViewPort{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETBLENDFACTOR SetBlendFactor{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETCULLFACE SetCullFace{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETFRONTFACEWINDING SetFrontFaceWinding{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETDRAWBUFFER SetDrawBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETDRAWBUFFERS SetDrawBuffers{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETREADBUFFER SetReadBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CLEARCOLOR ClearColor{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CLEARBUFFER ClearBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CLEARBUFFER1 ClearBuffer1{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CLEARBUFFER2 ClearBuffer2{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CLEARBUFFER3 ClearBuffer3{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CLEARSPECIFICBUFFER ClearSpecificBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CREATEBUFFER CreateBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYBUFFER DestroyBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CREATEVERTEXARRAYOBJECT CreateVertexArrayObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYVERTEXARRAYOBJECT DestroyVertexArrayObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDVERTEXARRAYOBJECT BindVertexArrayObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UNBINDVERTEXARRAYOBJECT UnBindVertexArrayObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ALLOCATEBUFFERMEMORY AllocateBufferMemory{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ENABLEVERTEXATTRIBUTEARRAYINDEX EnableVertexAttributeArrayIndex{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINEVERTEXATTRIBUTELAYOUT DefineVertexAttributeLayout{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDBUFFER BindBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UNBINDBUFFER UnBindBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDBUFFERTOINDEXEDBUFFER BindBufferToIndexedBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEDATATOBUFFER UpdateDataToBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GENERATEFRAMEBUFFER GenerateFrameBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYFRAMEBUFFER DestroyFrameBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDFRAMEBUFFER BindFrameBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CHECKFRAMEBUFFERISSUCCESFULLYCREATED CheckFrameBufferIsSuccesfullyCreated{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDRENDERBUFFER BindRenderBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ATTACH2DTEXTURETOFRAMEBUFFER Attach2DTextureToFrameBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CREATERENDERBUFFEROBJECT CreateRenderBufferObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ALLOCATERENDERBUFFERMEMORY AllocateRenderBufferMemory{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ATTACHRENDERBUFFERTOFRAMEBUFFER AttachRenderBufferToFrameBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYRENDERBUFFER DestroyRenderBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETFRAMEBUFFERWIDTH GetFrameBufferWidth{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETFRAMEBUFFERHEIGHT GetFrameBufferHeight{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DRAW Draw{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DRAWINDEXED DrawIndexed{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CREATEMATERIAL CreateMaterial{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYMATERIAL DestroyMaterial{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_LINKMATERIAL LinkMaterial{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDMATERIAL BindMaterial{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CREATESHADEROBJECT CreateShaderObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYSHADEROBJECT DestroyShaderObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_COMPILESHADER CompileShader{nullptr};

			/*
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_COMPILESHADERS CompileShaders{nullptr};
			*/

			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ATTACHSHADERTOMATERIAL AttachShaderToMaterial{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERBOOL1 UpdateConstantBuffer_bool1{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERBOOL2 UpdateConstantBuffer_bool2{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERBOOL3 UpdateConstantBuffer_bool3{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERBOOL4 UpdateConstantBuffer_bool4{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERINT1 UpdateConstantBuffer_int1{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERINT2 UpdateConstantBuffer_int2{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERINT3 UpdateConstantBuffer_int3{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERINT4 UpdateConstantBuffer_int4{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERFLOAT1 UpdateConstantBuffer_float1{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERFLOAT2 UpdateConstantBuffer_float2{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERFLOAT3 UpdateConstantBuffer_float3{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERFLOAT4 UpdateConstantBuffer_float4{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERMAT2X2F UpdateConstantBuffer_mat2x2f{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERMAT3X3F UpdateConstantBuffer_mat3x3f{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATECONSTANTBUFFERMAT4X4F UpdateConstantBuffer_mat4x4f{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_MAPBUFFEROBJECTTOCLIENTADDRESS MapBufferObjectToClientAddress{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UNMAPBUFFEROBJECMAPPEDTTOCLIENTADDRESS UnMapBufferObjectMappedToClientAddress{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_CREATEXTUREOBJECT CreateTextureObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DESTROYTEXTUREOBJECT DestroyTextureObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDTEXTUREOBJECT BindTextureObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_ACTIVATETEXTUREUNIT ActivateTextureUnit{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BINDTEXTUREOBJECTANDACTIVATETEXTUREUNIT BindTextureObjectAndActivateTextureUnit{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UNBINDTEXTUREOBJECT UnBindTextureObject{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_BLITFRAMEBUFFER BlitFrameBuffer{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETTEXTUREMETADATAFLOAT GetTextureMetaDataFloat{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETTEXTUREMETADATAINT GetTextureMetaDataInt{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETTEXTUREPARAMETERFLOAT SetTextureParameterFloat{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETTEXTUREPARAMETERINT SetTextureParameterInt{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETTEXTUREWRAPMODES SetTextureWrapMode_S{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETTEXTUREWRAPMODET SetTextureWrapMode_T{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETTEXTUREWRAPMODER SetTextureWrapMode_R{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETMINFILTER SetMinFilter{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SETMAGFILTER SetMagFilter{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_FETCHTEXTUREPIXELS FetchTexturePixels{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_READPIXELS ReadPixels{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINE1DTEXTURESTORAGEREQUIREMENT Define1DTextureStorageRequirement{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINE2DTEXTURESTORAGEREQUIREMENT Define2DTextureStorageRequirement{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINE3DTEXTURESTORAGEREQUIREMENT Define3DTextureStorageRequirement{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINE1DCOMPRESSEDTEXTURESTORAGEREQUIREMENT Define1DCompressedTextureStorageRequirement{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINE2DCOMPRESSEDTEXTURESTORAGEREQUIREMENT Define2DCompressedTextureStorageRequirement{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_DEFINE3DCOMPRESSEDTEXTURESTORAGEREQUIREMENT Define3DCompressedTextureStorageRequirement{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEPIXELSTO1DTEXTURE UploadPixelsTo1DTexture{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEPIXELSTO2DTEXTURE UploadPixelsTo2DTexture{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEPIXELSTO3DTEXTURE UploadPixelsTo3DTexture{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEPIXELSTO1DCOMPRESSEDTEXTURE UploadPixelsTo1DCompressedTexture{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEPIXELSTO2DCOMPRESSEDTEXTURE UploadPixelsTo2DCompressedTexture{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_UPDATEPIXELSTO3DCOMPRESSEDTEXTURE UploadPixelsTo3DCompressedTexture{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETCONSTANTBUFFERBINDINGPOINT GetConstantBufferBindingPoint{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETCONSTANTBUFFERDATASIZE GetConstantBufferDataSize{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETCONSTANTBUFFERBLOCKCOUNT GetConstantBufferBlockCount{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_GETCONSTANTBUFFERUNIFORMLOCATION GetConstantBufferUniformLocation{nullptr};
		}
	}
}


