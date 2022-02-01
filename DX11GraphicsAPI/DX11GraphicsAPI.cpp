#include "GraphicsAPI.h"
#include "DX11GraphicsAPI.h"

#include "stdio.h"
#include "assert.h"

#include <windows.h>
#include <d3d11_3.h>
#include <d3dcompiler.h>


#undef NEVER_HAPPEN
#ifdef _DEBUG
#define NEVER_HAPPEN assert(false)
#else
#define NEVER_HAPPEN __assume(0)
#endif

#define MIN(X, Y) ((X < Y) ? (X) : (Y));
#define MAX(X, Y) ((X > Y) ? (X) : (Y));



namespace dooms
{
	namespace graphics
	{

		namespace dx11
		{
            FORCE_INLINE static D3D_PRIMITIVE_TOPOLOGY Convert_ePrimitiveType_To_D3D_PRIMITIVE_TOPOLOGY(const GraphicsAPI::ePrimitiveType primitiveType)
            {
	            switch (primitiveType)
	            {
	            case GraphicsAPI::POINTS:
                    return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
	            case GraphicsAPI::LINES:
                    return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
	            case GraphicsAPI::TRIANGLES:
                    return D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
	            default: 
                    NEVER_HAPPEN;
	            }
            }

            FORCE_INLINE static DXGI_FORMAT ConvertTextureInternalFormat_To_DXGI_FORMAT(const GraphicsAPI::eTextureInternalFormat internalFormat)
            {
                // reference ( opengl format, dxgi table : https://chromium.googlesource.com/angle/angle/+/6ea6f9424890b2a443fafb940ba27e902b4e9157/src/libANGLE/renderer/d3d/d3d11/texture_format_util.cpp )
	            switch(internalFormat)
	            {
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8:
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8:
                    return DXGI_FORMAT_R8G8B8A8_UNORM;
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT16:
                    return DXGI_FORMAT_D16_UNORM;
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT24:
                    return DXGI_FORMAT_D24_UNORM_S8_UINT; // DX11 doesn't have D24 format.
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32:
                    return DXGI_FORMAT_D24_UNORM_S8_UINT; // DX11 doesn't have D24 format.
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32F:
                    return DXGI_FORMAT_D32_FLOAT;
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8:
                    return DXGI_FORMAT_D24_UNORM_S8_UINT;
                case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH32F_STENCIL8:
                    return DXGI_FORMAT_R32G8X24_TYPELESS;

	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_NONE: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_STENCIL_INDEX: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_STENCIL_INDEX8: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RED: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R3_G3_B2: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB4: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB5: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB10: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB12: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA2: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA4: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB5_A1: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8_SNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB10_A2: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB10_A2UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA12: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_SRGB8: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_SRGB8_ALPHA8: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R32F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG32F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB32F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA32F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R11F_G11F_B10F: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB9_E5: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R32I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R32UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG32I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG32UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB32I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB32UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA32I: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA32UI: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RED: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RG: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGBA: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB_ALPHA: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RED_RGTC1: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SIGNED_RED_RGTC1: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RG_RGTC2: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SIGNED_RG_RGTC2: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGBA_BPTC_UNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB_ALPHA_BPTC_UNORM: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB_BPTC_SIGNED_FLOAT: 
	            case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:
                    NEVER_HAPPEN;
	            default:
                    NEVER_HAPPEN;
	            }
            }

            FORCE_INLINE static DXGI_FORMAT ConvertTextureCompressedInternalFormat_To_DXGI_FORMAT(const GraphicsAPI::eTextureCompressedInternalFormat textureInternalFormat)
            {
	            switch (textureInternalFormat)
	            {
	            case GraphicsAPI::COMPRESSED_RGB_S3TC_DXT1_EXT:
                    return DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
	            case GraphicsAPI::COMPRESSED_RGBA_S3TC_DXT5_EXT: 
                    return DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
	            case GraphicsAPI::COMPRESSED_RED_GREEN_RGTC2_EXT: 
                    return DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM;
	            case GraphicsAPI::COMPRESSED_RED_RGTC1_EXT:
                    return DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM;

	            case GraphicsAPI::COMPRESSED_SRGB_S3TC_DXT1_EXT:
	            case GraphicsAPI::COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT: 
	            case GraphicsAPI::COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT: 
	            case GraphicsAPI::COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
                case GraphicsAPI::COMPRESSED_RGBA_S3TC_DXT3_EXT:
                case GraphicsAPI::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE:
                case GraphicsAPI::COMPRESSED_RGB8_ETC2:
                case GraphicsAPI::COMPRESSED_SRGB8_ETC2:
                case GraphicsAPI::COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
                case GraphicsAPI::COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
                case GraphicsAPI::COMPRESSED_RGBA8_ETC2_EAC:
                case GraphicsAPI::COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
                case GraphicsAPI::COMPRESSED_R11_EAC:
                case GraphicsAPI::COMPRESSED_SIGNED_R11_EAC:
                case GraphicsAPI::COMPRESSED_RG11_EAC:
                case GraphicsAPI::COMPRESSED_SIGNED_RG11_EAC:
                case GraphicsAPI::COMPRESSED_RGBA_S3TC_DXT1_EXT:
                    NEVER_HAPPEN;

	            default:
                    NEVER_HAPPEN;
	            }
            }

            FORCE_INLINE static D3D11_DSV_DIMENSION ConvertTextureBindTarget_To_D3D11_DSV_DIMENSION(const GraphicsAPI::eTextureBindTarget textureBindTarget)
            {
                switch (textureBindTarget)
                {
                case GraphicsAPI::TEXTURE_1D:
                    return D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE1D;
                case GraphicsAPI::TEXTURE_2D:
                    return D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
                case GraphicsAPI::TEXTURE_1D_ARRAY:
                    return D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
                case GraphicsAPI::TEXTURE_2D_ARRAY:
                    return D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
                case GraphicsAPI::TEXTURE_2D_MULTISAMPLE:
                    return D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
                case GraphicsAPI::TEXTURE_2D_MULTISAMPLE_ARRAY:
                    return D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
                default:
                    NEVER_HAPPEN;

                }
            }

            FORCE_INLINE static D3D11_BIND_FLAG Convert_eBindFlag_To_D3D11_BIND_FLAG(const GraphicsAPI::eBindFlag bindFlag)
            {
                long dx11BindFlag = 0;
	            
                if ((GraphicsAPI::eBindFlag::BIND_VERTEX_BUFFER & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_VERTEX_BUFFER;
                }
                    
                if ((GraphicsAPI::eBindFlag::BIND_INDEX_BUFFER & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_INDEX_BUFFER;
                }
                    
	            if (( GraphicsAPI::eBindFlag::BIND_CONSTANT_BUFFER & bindFlag) != 0)
	            {
                    dx11BindFlag |= (long)D3D11_BIND_CONSTANT_BUFFER;
	            }
                   
                if ((GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_SHADER_RESOURCE;
                }
                    
                if ((GraphicsAPI::eBindFlag::BIND_STREAM_OUTPUT & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_STREAM_OUTPUT;
                }
                   
                if ((GraphicsAPI::eBindFlag::BIND_RENDER_TARGET & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_RENDER_TARGET;
                }
                   
                if ((GraphicsAPI::eBindFlag::BIND_DEPTH_STENCIL & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_DEPTH_STENCIL;
                }
                
                if ((GraphicsAPI::eBindFlag::BIND_UNORDERED_ACCESS & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_UNORDERED_ACCESS;
                }
              
                if ((GraphicsAPI::eBindFlag::BIND_DECODER & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_DECODER;
                }
                
                if ((GraphicsAPI::eBindFlag::BIND_VIDEO_ENCODER & bindFlag) != 0)
                {
                    dx11BindFlag |= (long)D3D11_BIND_VIDEO_ENCODER;
                }

                return (D3D11_BIND_FLAG)dx11BindFlag;
            }

            FORCE_INLINE D3D11_STENCIL_OP Convert_eStencilOption_TO_D3D12_STENCIL_OP(const graphics::GraphicsAPI::eStencilOption stencilOption)
            {
	            switch (stencilOption)
	            {
	            case GraphicsAPI::KEEP: 
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP;
                    break;
	            case GraphicsAPI::STENCIL_OPTION_ZERO: 
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_ZERO;
                    break;
	            case GraphicsAPI::REPLACE:
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_REPLACE;
                    break;
	            case GraphicsAPI::INCR:
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_INCR;
                    break;
	            case GraphicsAPI::INCR_WRAP:
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_INCR_SAT;
                    break;
	            case GraphicsAPI::DECR: 
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_DECR;
                    break;
	            case GraphicsAPI::DECR_WRAP: 
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_DECR_SAT;
                    break;
	            case GraphicsAPI::INVERT: 
                    return D3D11_STENCIL_OP::D3D11_STENCIL_OP_INVERT;
                    break;
	            default:
                    NEVER_HAPPEN;
	            }
            }

            FORCE_INLINE D3D11_BLEND Convert_eBlendFactor_TO_D3D11_BLEND(const graphics::GraphicsAPI::eBlendFactor blendFactor)
            {
	            switch (blendFactor)
	            {
	            case GraphicsAPI::ZERO: 
                    return D3D11_BLEND::D3D11_BLEND_ZERO;
	            case GraphicsAPI::ONE: 
                    return D3D11_BLEND::D3D11_BLEND_ONE;
	            case GraphicsAPI::SRC_COLOR: 
                    return D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
	            case GraphicsAPI::ONE_MINUS_SRC_COLOR: 
                    return D3D11_BLEND::D3D11_BLEND_INV_SRC_COLOR;
	            case GraphicsAPI::DST_COLOR: 
                    return D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
	            case GraphicsAPI::ONE_MINUS_DST_COLOR:
                    return D3D11_BLEND::D3D11_BLEND_INV_DEST_COLOR;
	            case GraphicsAPI::SRC_ALPHA: 
                    return D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	            case GraphicsAPI::ONE_MINUS_SRC_ALPHA: 
                    return D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	            case GraphicsAPI::DST_ALPHA:
                    return D3D11_BLEND::D3D11_BLEND_DEST_ALPHA;
	            case GraphicsAPI::ONE_MINUS_DST_ALPHA:
                    return D3D11_BLEND::D3D11_BLEND_INV_DEST_ALPHA;
	            case GraphicsAPI::CONSTANT_COLOR:
                    return D3D11_BLEND::D3D11_BLEND_BLEND_FACTOR;
	            case GraphicsAPI::ONE_MINUS_CONSTANT_COLOR: 
                    return D3D11_BLEND::D3D11_BLEND_INV_BLEND_FACTOR;
	            default:
                    NEVER_HAPPEN;
	            }
            }

            static HINSTANCE g_hInst = nullptr;
            static HWND g_hWnd = nullptr;
            static  D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;
            static D3D_FEATURE_LEVEL g_featureLevel = D3D_FEATURE_LEVEL_11_0;
            static ID3D11Device* g_pd3dDevice = nullptr;
            static ID3D11Device1* g_pd3dDevice1 = nullptr;
            static ID3D11DeviceContext* g_pImmediateContext = nullptr;
            static  ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
            static IDXGISwapChain* g_pSwapChain = nullptr;
            static  IDXGISwapChain1* g_pSwapChain1 = nullptr;
            static ID3D11RenderTargetView* BackBufferRenderTargetView = nullptr;
            static ID3D11Texture2D* g_pDepthStencil = nullptr;
            static ID3D11DepthStencilView* BackBufferDepthStencilView = nullptr;
            static ID3D11SamplerState* g_pSamplerLinear = nullptr;
            static unsigned int SyncInterval = 0;
            static unsigned int DrawCallCounter = 0;
            static HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, int width, int height);
            static HRESULT InitDevice();
            static void CleanupDevice();
            static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
            
            static HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, int width, int height)
			{
                assert(hInstance != NULL);
				// Register class
                WNDCLASSEX wcex; // https://goodgaym.tistory.com/32
                wcex.cbSize = sizeof(WNDCLASSEX);
                wcex.style = CS_HREDRAW | CS_VREDRAW;
                wcex.lpfnWndProc = WndProc;
                wcex.cbClsExtra = 0;
                wcex.cbWndExtra = 0;
                wcex.hInstance = hInstance;
                wcex.hIcon = NULL;
                wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
                wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.lpszMenuName = nullptr;
                wcex.lpszClassName = L"SUNG JIN KANG GAME ENGINE WINDOW CLASS";
                wcex.hIconSm = NULL;
                if (!RegisterClassEx(&wcex))
                    return E_FAIL;

				// Create window
				g_hInst = hInstance;
				RECT rc = { 0, 0, width, height };
				AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
				g_hWnd = CreateWindow(L"SUNG JIN KANG GAME ENGINE WINDOW CLASS", L"SUNG JIN KANG",
					WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
					CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
					nullptr);
				if (!g_hWnd)
				{
                    printf("Fail to CreateWindow : %u", GetLastError());
                    return E_FAIL;
				}
					

				ShowWindow(g_hWnd, nCmdShow);

				return S_OK;
			}

            static HRESULT InitDevice()
            {
                HRESULT hr = S_OK;

                RECT rc;
                GetClientRect(g_hWnd, &rc);
                UINT width = rc.right - rc.left;
                UINT height = rc.bottom - rc.top;

                UINT createDeviceFlags = (D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT);
#ifdef _DEBUG
                createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

                D3D_DRIVER_TYPE driverTypes[] = // https://docs.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_driver_type
                {
                    D3D_DRIVER_TYPE_HARDWARE,
                    D3D_DRIVER_TYPE_WARP,
                    D3D_DRIVER_TYPE_REFERENCE,
                };
                UINT numDriverTypes = ARRAYSIZE(driverTypes);

                D3D_FEATURE_LEVEL featureLevels[] =
                {
                    D3D_FEATURE_LEVEL_11_1,
                    D3D_FEATURE_LEVEL_11_0
                };
                UINT numFeatureLevels = ARRAYSIZE(featureLevels);

                for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
                {
                    g_driverType = driverTypes[driverTypeIndex];
                    hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
                        D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);

                    if (hr == E_INVALIDARG)
                    {
                        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
                        hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                            D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
                    }

                    if (SUCCEEDED(hr))
                        break;
                }
                if (FAILED(hr))
                    return hr;

                // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
                IDXGIFactory1* dxgiFactory = nullptr;
                {
                    IDXGIDevice* dxgiDevice = nullptr;
                    hr = g_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
                    if (SUCCEEDED(hr))
                    {
                        IDXGIAdapter* adapter = nullptr;
                        hr = dxgiDevice->GetAdapter(&adapter);
                        if (SUCCEEDED(hr))
                        {
                            hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                            adapter->Release();
                        }
                        dxgiDevice->Release();
                    }
                }
                if (FAILED(hr))
                    return hr;

                // Create swap chain
                IDXGIFactory2* dxgiFactory2 = nullptr;
                hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
                if (dxgiFactory2)
                {
                    // DirectX 11.1 or later
                    hr = g_pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&g_pd3dDevice1));
                    if (SUCCEEDED(hr))
                    {
                        (void)g_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&g_pImmediateContext1));
                    }

                    DXGI_SWAP_CHAIN_DESC1 sd = {};
                    sd.Width = width;
                    sd.Height = height;
                    sd.Format = dooms::graphics::dx11::ConvertTextureInternalFormat_To_DXGI_FORMAT(GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8);
                    sd.SampleDesc.Count = 1;
                    sd.SampleDesc.Quality = 0;
                    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    sd.BufferCount = 1;

                    hr = dxgiFactory2->CreateSwapChainForHwnd(g_pd3dDevice, g_hWnd, &sd, nullptr, nullptr, &g_pSwapChain1);
                    if (SUCCEEDED(hr))
                    {
                        hr = g_pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&g_pSwapChain));
                    }

                    dxgiFactory2->Release();
                }
                else
                {
                    // DirectX 11.0 systems
                    DXGI_SWAP_CHAIN_DESC sd = {};
                    sd.BufferCount = 1;
                    sd.BufferDesc.Width = width;
                    sd.BufferDesc.Height = height;
                    sd.BufferDesc.Format = dooms::graphics::dx11::ConvertTextureInternalFormat_To_DXGI_FORMAT(GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8);
                    sd.BufferDesc.RefreshRate.Numerator = 60;
                    sd.BufferDesc.RefreshRate.Denominator = 1;
                    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    sd.OutputWindow = g_hWnd;
                    sd.SampleDesc.Count = 1;
                    sd.SampleDesc.Quality = 0;
                    sd.Windowed = TRUE;

                    hr = dxgiFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChain);
                }

                // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
                dxgiFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

                dxgiFactory->Release();

                if (FAILED(hr))
                    return hr;

                // Create a render target view
                ID3D11Texture2D* pBackBuffer = nullptr; // https://vsts2010.tistory.com/517
                hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
                if (FAILED(hr))
                    return hr;

                hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &BackBufferRenderTargetView);
                pBackBuffer->Release();
                if (FAILED(hr))
                    return hr;

                {
                    ID3D11RasterizerState* state;
                    D3D11_RASTERIZER_DESC desc;

                    desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
                    desc.CullMode = D3D11_CULL_BACK;
                    desc.FrontCounterClockwise = true;
                    desc.DepthBias = 0;
                    desc.DepthBias = 0;
                    desc.SlopeScaledDepthBias = 0.0f;
                    desc.DepthBiasClamp = 0.0f;
                    desc.DepthClipEnable = true;
                    desc.ScissorEnable = false;
                    desc.MultisampleEnable = false;
                    desc.AntialiasedLineEnable = false;

                    HRESULT hr = dx11::g_pd3dDevice->CreateRasterizerState(&desc, &state);
                    assert(FAILED(hr) == false);
                    dx11::g_pImmediateContext->RSSetState(state);
                    state->Release();
                }

                {
                    ID3D11BlendState* state;
                    D3D11_BLEND_DESC desc;

                    desc.AlphaToCoverageEnable = false;
                    desc.IndependentBlendEnable = false;
                    desc.RenderTarget[0].BlendEnable = false;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ZERO; //
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
                    desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
                    desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

                    hr = dx11::g_pd3dDevice->CreateBlendState(&desc, &state);
                    assert(FAILED(hr) == false);
                    dx11::g_pImmediateContext->OMSetBlendState(state, NULL, 0xFFFFFFFF);
                    state->Release();
                }

                {
                    ID3D11DepthStencilState* DepthStencilState;
                    D3D11_DEPTH_STENCIL_DESC dsDesc;

                    // Depth test parameters
                    dsDesc.DepthEnable = true;
                    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

                    // Stencil test parameters
                    dsDesc.StencilEnable = false;
                    dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
                    dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

                    // Stencil operations if pixel is front-facing
                    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
                    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

                    // Stencil operations if pixel is back-facing
                    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
                    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

                    // Create depth stencil state
                    hr = dx11::g_pd3dDevice->CreateDepthStencilState(&dsDesc, &DepthStencilState);
                    assert(FAILED(hr) == false);
                    dx11::g_pImmediateContext->OMSetDepthStencilState(DepthStencilState, 1);
                    DepthStencilState->Release();
                }

                {
                    // Create depth stencil texture
                    D3D11_TEXTURE2D_DESC descDepth = {};
                    descDepth.Width = width;
                    descDepth.Height = height;
                    descDepth.MipLevels = 1;
                    descDepth.ArraySize = 1;
                    descDepth.Format = dooms::graphics::dx11::ConvertTextureInternalFormat_To_DXGI_FORMAT(GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT24);
                    descDepth.SampleDesc.Count = 1;
                    descDepth.SampleDesc.Quality = 0;
                    descDepth.Usage = D3D11_USAGE_DEFAULT;
                    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
                    descDepth.CPUAccessFlags = 0;
                    descDepth.MiscFlags = 0;
                    hr = g_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
                    if (FAILED(hr))
                        return hr;

                    // Create the depth stencil view
                    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
                    descDSV.Format = descDepth.Format;
                    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
                    descDSV.Texture2D.MipSlice = 0;
                    hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &BackBufferDepthStencilView);
                    if (FAILED(hr))
                        return hr;
                }

                g_pImmediateContext->OMSetRenderTargets(1, &BackBufferRenderTargetView, BackBufferDepthStencilView);


                // Test
                // Setup the viewport
                D3D11_VIEWPORT vp;
                vp.Width = (FLOAT)width;
                vp.Height = (FLOAT)height;
                vp.MinDepth = 0.0f;
                vp.MaxDepth = 1.0f;
                vp.TopLeftX = 0;
                vp.TopLeftY = 0;
                g_pImmediateContext->RSSetViewports(1, &vp);

                {
                    D3D11_SAMPLER_DESC sampDesc = {};
                    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
                    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
                    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
                    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
                    sampDesc.MinLOD = 0;
                    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
                    hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
                    assert(FAILED(hr) == false);
                    if (FAILED(hr))
                        return hr;

                    for(size_t i = 0 ; i < D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT ; i++)
                    {
                        g_pImmediateContext->PSSetSamplers(i, 1, &g_pSamplerLinear);
                    }
                }
               
                /*
                // Compile the vertex shader
                ID3DBlob* pVSBlob = nullptr;
                hr = CompileShaderFromFile(L"Assets/DX11Test/Tutorial07.fxh", "VS", "vs_4_0", &pVSBlob);
                if (FAILED(hr))
                {
                    MessageBox(nullptr,
                        L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
                    return hr;
                }

                // Create the vertex shader
                hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
                if (FAILED(hr))
                {
                    pVSBlob->Release();
                    return hr;
                }

                // Define the input layout
                D3D11_INPUT_ELEMENT_DESC layout[] =
                {
                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                };
                UINT numElements = ARRAYSIZE(layout);

                // Create the input layout
                hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
                    pVSBlob->GetBufferSize(), &g_pVertexLayout);
                pVSBlob->Release();
                if (FAILED(hr))
                    return hr;

                // Set the input layout
                g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

                // Compile the pixel shader
                ID3DBlob* pPSBlob = nullptr;
                hr = CompileShaderFromFile(L"Assets/DX11Test/Tutorial07.fxh", "PS", "ps_4_0", &pPSBlob);
                if (FAILED(hr))
                {
                    MessageBox(nullptr,
                        L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
                    return hr;
                }

                // Create the pixel shader
                hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
                pPSBlob->Release();
                if (FAILED(hr))
                    return hr;

                // Create vertex buffer
                SimpleVertex vertices[] =
                {
                    {DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
                    { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
                    { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
                    { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },

                    { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
                    { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
                    { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
                    { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

                    { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
                    { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
                    { DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
                    { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },

                    { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
                    { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
                    { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
                    { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },

                    { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
                    { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
                    { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
                    { DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },

                    { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
                    { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
                    { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
                    { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
                };

                D3D11_BUFFER_DESC bd = {};
                bd.Usage = D3D11_USAGE_DEFAULT;
                bd.ByteWidth = sizeof(SimpleVertex) * 24;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = 0;

                D3D11_SUBRESOURCE_DATA InitData = {};
                InitData.pSysMem = vertices;
                hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
                if (FAILED(hr))
                    return hr;

                // Set vertex buffer
                UINT stride = sizeof(SimpleVertex);
                UINT offset = 0;
                g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

                // Create index buffer
                // Create vertex buffer
                WORD indices[] =
                {
                    3,1,0,
                    2,1,3,

                    6,4,5,
                    7,4,6,

                    11,9,8,
                    10,9,11,

                    14,12,13,
                    15,12,14,

                    19,17,16,
                    18,17,19,

                    22,20,21,
                    23,20,22
                };

                bd.Usage = D3D11_USAGE_DEFAULT;
                bd.ByteWidth = sizeof(WORD) * 36;
                bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
                bd.CPUAccessFlags = 0;
                InitData.pSysMem = indices;
                hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
                if (FAILED(hr))
                    return hr;

                // Set index buffer
                g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

                // Set primitive topology
                g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

                // Create the constant buffers
                bd.Usage = D3D11_USAGE_DEFAULT;
                bd.ByteWidth = sizeof(CBNeverChanges);
                bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                bd.CPUAccessFlags = 0;
                hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pCBNeverChanges);
                if (FAILED(hr))
                    return hr;

                bd.ByteWidth = sizeof(CBChangeOnResize);
                hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
                if (FAILED(hr))
                    return hr;

                bd.ByteWidth = sizeof(CBChangesEveryFrame);
                hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
                if (FAILED(hr))
                    return hr;

                // Load the Texture
                hr = DirectX::CreateDDSTextureFromFile(g_pd3dDevice, L"Assets/DX11Test/seafloor.dds", nullptr, &g_pTextureRV);
                if (FAILED(hr))
                    return hr;

                // Create the sample state
                D3D11_SAMPLER_DESC sampDesc = {};
                sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
                sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
                sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
                sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
                sampDesc.MinLOD = 0;
                sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
                hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
                if (FAILED(hr))
                    return hr;

                // Initialize the world matrices
                g_World = DirectX::XMMatrixIdentity();

                // Initialize the view matrix
                DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
                DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
                DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
                g_View = DirectX::XMMatrixLookAtLH(Eye, At, Up);

                CBNeverChanges cbNeverChanges;
                cbNeverChanges.mView = XMMatrixTranspose(g_View);
                g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);

                // Initialize the projection matrix
                g_Projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

                CBChangeOnResize cbChangesOnResize;
                cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
                g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
                */

                return S_OK;
            }
            
            //--------------------------------------------------------------------------------------
			// Clean up the objects we've created
			//--------------------------------------------------------------------------------------
            static void CleanupDevice()
            {
                if (g_pImmediateContext) g_pImmediateContext->ClearState();
                if (g_pDepthStencil) g_pDepthStencil->Release();
                if (BackBufferDepthStencilView) BackBufferDepthStencilView->Release();
                if (BackBufferRenderTargetView) BackBufferRenderTargetView->Release();
                if (g_pSwapChain1) g_pSwapChain1->Release();
                if (g_pSwapChain) g_pSwapChain->Release();
                if (g_pImmediateContext1) g_pImmediateContext1->Release();
                if (g_pImmediateContext) g_pImmediateContext->Release();
                if (g_pd3dDevice1) g_pd3dDevice1->Release();
                if (g_pd3dDevice) g_pd3dDevice->Release();
            }

            //--------------------------------------------------------------------------------------
			// Called every time the application receives a message
			//--------------------------------------------------------------------------------------
            static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
            {
                PAINTSTRUCT ps;
                HDC hdc;

                switch (message)
                {
                case WM_PAINT:
                    hdc = BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                    break;

                case WM_DESTROY:
                    PostQuitMessage(0);
                    break;

                    // Note that this tutorial does not handle resizing (WM_SIZE) requests,
                    // so we created the window without the resize border.

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }

                return 0;
            }

            ID3D11Device* GetDevice()
            {
                return g_pd3dDevice;
            }

            ID3D11DeviceContext* GetDeviceContext()
            {
                return g_pImmediateContext;
            }
		}

        DOOMS_ENGINE_GRAPHICS_API void FlushCMDQueue()
		{
            dx11::g_pImmediateContext->Flush();
		}

        DOOMS_ENGINE_GRAPHICS_API GraphicsAPI::eGraphicsAPIType GetCuurentAPIType()
        {
            return GraphicsAPI::eGraphicsAPIType::DX11_10;
        }

		DOOMS_ENGINE_GRAPHICS_API double GetTime()
		{
            __int64 currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
            
			return currTime;
		}

        DOOMS_ENGINE_GRAPHICS_API GraphicsAPI::eGraphicsAPIType GetCurrentAPIType()
        {
            return GraphicsAPI::eGraphicsAPIType::DX11_10;
        }

		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphicsAPI(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum)
		{
			HINSTANCE hInstance = GetModuleHandle(NULL);
            if(hInstance == NULL)
            {
                printf("Fail to GetModuleHandle : %u", GetLastError());
            }

			if (FAILED(dx11::InitWindow(hInstance, true, screenWidth, screenHeight)))
			{
                assert(0);
                return 0;
			}

			if (FAILED(dx11::InitDevice()))
			{
				dx11::CleanupDevice();
                assert(0);
				return 0;
			}

		
			return 1;

		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeinitializeGraphicsAPI()
		{
            dx11::CleanupDevice();
			return 0;
		}

        DOOMS_ENGINE_GRAPHICS_API unsigned int GetDrawCall()
        {
            return dx11::DrawCallCounter;
        }

		DOOMS_ENGINE_GRAPHICS_API void SwapBuffer() noexcept
		{
            MSG msg = { 0 };
            while (WM_QUIT != msg.message)
            {
                if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                {
                    //dx11::g_pImmediateContext->Flush();
                    HRESULT hr = dx11::g_pSwapChain->Present(dx11::SyncInterval, 0); // Swap Back buffer
                    if(FAILED(hr))
                    {
                        hr = dx11::g_pd3dDevice->GetDeviceRemovedReason();
                        assert(false);
	                    //getdevicerea
                    }
                    break;
                }
            }
          
            dx11::DrawCallCounter = 0;
		}

        DOOMS_ENGINE_GRAPHICS_API void SetViewport(const unsigned int index, const int startX, const int startY, const unsigned int width, const unsigned int height)
        {
            // Fetch existing viewports

            UINT vpCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
            D3D11_VIEWPORT vp[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

            dx11::g_pImmediateContext->RSGetViewports(&vpCount, vp);
            assert(vpCount > index);
            
            vpCount = MAX(index + 1, vpCount);

            vp[index].Width = (FLOAT)width;
            vp[index].Height = (FLOAT)height;
            vp[index].MinDepth = 0.0f;
            vp[index].MaxDepth = 1.0f;
            vp[index].TopLeftX = (FLOAT)startX;
            vp[index].TopLeftY = (FLOAT)startY;
            dx11::g_pImmediateContext->RSSetViewports(vpCount, vp);
        }


        DOOMS_ENGINE_GRAPHICS_API bool GetViewPort(const unsigned int index, int* const startX, int* const startY, int* const width, int* const height)
        {
            bool isSuccess = false;

            // https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-rsgetviewports
            UINT vpCount = MIN(index + 1, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE);
            D3D11_VIEWPORT* vp = new D3D11_VIEWPORT[vpCount];
         
            dx11::g_pImmediateContext->RSGetViewports(&vpCount, vp);
            assert(vpCount > index);

            if(vpCount > index)
            {
                *startX = vp[index].TopLeftX;
                *startY = vp[index].TopLeftY;
                *width = vp[index].Width;
                *height = vp[index].Height;

                isSuccess = true;
            }

            delete[] vp;
            return isSuccess;
        }
        

        DOOMS_ENGINE_GRAPHICS_API void SetWindowTitle(const char* const title)
        {
            assert(dx11::g_hWnd != nullptr);
            SetWindowTextA(dx11::g_hWnd, title);
        }

        DOOMS_ENGINE_GRAPHICS_API void SetWindowTitleW(const wchar_t* const title)
        {
            assert(dx11::g_hWnd != nullptr);
            SetWindowTextW(dx11::g_hWnd, title);
        }

        DOOMS_ENGINE_GRAPHICS_API const char* GetPlatformVersion()
        {
            if(dx11::g_featureLevel == D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1)
            {
                return "D3D11_1";
            }
            else if (dx11::g_featureLevel == D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
            {
                return "D3D11_0";
            }
            else
            {
                NEVER_HAPPEN;
            }
        }

        DOOMS_ENGINE_GRAPHICS_API void* GetPlatformWindow()
        {
            return dx11::g_hWnd;
        }
        
        DOOMS_ENGINE_GRAPHICS_API void SetVSync(const bool isEnabled)
        {
            dx11::SyncInterval = (isEnabled == true ? 1 : 0);
        }

        DOOMS_ENGINE_GRAPHICS_API void SetIsDepthTestEnabled(const bool isEnabled)
        {
            UINT ref;
            ID3D11DepthStencilState* state;
            D3D11_DEPTH_STENCIL_DESC desc;

            dx11::g_pImmediateContext->OMGetDepthStencilState(&state, &ref);
            state->GetDesc(&desc);

            desc.DepthEnable = isEnabled;

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetDepthStencilState(state, ref);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetIsStencilTestEnabled(const bool isEnabled)
        {
            UINT ref;
            ID3D11DepthStencilState* state;
            D3D11_DEPTH_STENCIL_DESC desc;

            dx11::g_pImmediateContext->OMGetDepthStencilState(&state, &ref);
            state->GetDesc(&desc);

            desc.StencilEnable = isEnabled;

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetDepthStencilState(state, ref);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetIsStencilFunc
        (
            const GraphicsAPI::eTestFuncType testFuncType,
            const int ref,
            const unsigned int mask
        )
        {
            UINT DUMMNY;
            ID3D11DepthStencilState* state;
            D3D11_DEPTH_STENCIL_DESC desc;

            dx11::g_pImmediateContext->OMGetDepthStencilState(&state, &DUMMNY);
            state->GetDesc(&desc);
            
            switch (testFuncType)
            {
            case GraphicsAPI::ALWAYS:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
                break;
            case GraphicsAPI::NEVER:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
                break;
            case GraphicsAPI::LESS:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
                break;
            case GraphicsAPI::EQUAL:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_EQUAL;
                break;
            case GraphicsAPI::LEQUAL:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
                break;
            case GraphicsAPI::GREATER:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
                break;
            case GraphicsAPI::NOTEQUAL:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NOT_EQUAL;
                break;
            case GraphicsAPI::GEQUAL:
                desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER_EQUAL;
                break;
            default:
                NEVER_HAPPEN;
            }

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetDepthStencilState(state, ref);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetIsStencilOp
        (
            const GraphicsAPI::eStencilOption stencilFailOption,
            const GraphicsAPI::eStencilOption actionWhenStencilTestPass_And_DepthTestFail,
            const GraphicsAPI::eStencilOption actionWhenStencilTestPass_And_DepthTestPass
        )
        {
            UINT ref;
            ID3D11DepthStencilState* state;
            D3D11_DEPTH_STENCIL_DESC desc;

            dx11::g_pImmediateContext->OMGetDepthStencilState(&state, &ref);
            state->GetDesc(&desc);

            desc.BackFace.StencilFailOp = dx11::Convert_eStencilOption_TO_D3D12_STENCIL_OP(stencilFailOption);
            desc.BackFace.StencilDepthFailOp = dx11::Convert_eStencilOption_TO_D3D12_STENCIL_OP(actionWhenStencilTestPass_And_DepthTestFail);
            desc.BackFace.StencilPassOp = dx11::Convert_eStencilOption_TO_D3D12_STENCIL_OP(actionWhenStencilTestPass_And_DepthTestPass);

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetDepthStencilState(state, ref);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetDepthFunc(const GraphicsAPI::eTestFuncType depthFuncType)
        {
            UINT ref;
            ID3D11DepthStencilState* state;
            D3D11_DEPTH_STENCIL_DESC desc;

            dx11::g_pImmediateContext->OMGetDepthStencilState(&state, &ref);
            state->GetDesc(&desc);

            switch (depthFuncType)
            {
            case GraphicsAPI::ALWAYS:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
                break;
            case GraphicsAPI::NEVER:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
                break;
            case GraphicsAPI::LESS:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
                break;
            case GraphicsAPI::EQUAL:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_EQUAL;
                break;
            case GraphicsAPI::LEQUAL:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
                break;
            case GraphicsAPI::GREATER:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
                break;
            case GraphicsAPI::NOTEQUAL:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NOT_EQUAL;
                break;
            case GraphicsAPI::GEQUAL:
                desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER_EQUAL;
                break;
            default:
                NEVER_HAPPEN;
            }

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetDepthStencilState(state, ref);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetDepthMask(const bool isWriteDepthBuffer)
        {
            UINT ref;
            ID3D11DepthStencilState* state;
            D3D11_DEPTH_STENCIL_DESC desc;

            dx11::g_pImmediateContext->OMGetDepthStencilState(&state, &ref);
            state->GetDesc(&desc);

            desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetDepthStencilState(state, ref);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetIsAlphaTestEnabled(const bool isEnabled)
        {
            /*
            Direct3D 10 and higher does not implement an alpha test(or alpha testing state).
			This can be controlled using a pixel shader or with depth / stencil functionality.
			*/
        }

        DOOMS_ENGINE_GRAPHICS_API void SetIsBlendEnabled(const bool isEnabled)
        {
            ID3D11BlendState* state;
            float BlendFactor[4];
            unsigned int SampleMask;

            D3D11_BLEND_DESC desc;

            dx11::g_pImmediateContext->OMGetBlendState(&state, BlendFactor, &SampleMask);
            state->GetDesc(&desc);

            for(size_t i = 0 ; i < 8 ; i++)
            {
                desc.RenderTarget[i].BlendEnable = isEnabled;
            }

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateBlendState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetBlendState(state, BlendFactor, SampleMask);
            state->Release();
        }

       
        
        DOOMS_ENGINE_GRAPHICS_API void SetBlendFactor
        (
            const GraphicsAPI::eBlendFactor sourceBlendFactor,
            const GraphicsAPI::eBlendFactor destinationBlendFactor
        )
        {
            ID3D11BlendState* state;
            float BlendFactor[4];
            unsigned int SampleMask;

            D3D11_BLEND_DESC desc;

            dx11::g_pImmediateContext->OMGetBlendState(&state, BlendFactor, &SampleMask);
            state->GetDesc(&desc);

            for (size_t i = 0; i < 8; i++)
            {
                desc.RenderTarget[i].SrcBlend = dx11::Convert_eBlendFactor_TO_D3D11_BLEND(sourceBlendFactor);
                desc.RenderTarget[i].DestBlend = dx11::Convert_eBlendFactor_TO_D3D11_BLEND(destinationBlendFactor);
            }

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateBlendState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->OMSetBlendState(state, BlendFactor, SampleMask);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetCullFace(const GraphicsAPI::eCullFace cullFace)
        {
            ID3D11RasterizerState* state;
            D3D11_RASTERIZER_DESC desc;
            dx11::g_pImmediateContext->RSGetState(&state);
            state->GetDesc(&desc);

            switch (cullFace)
            {
            case GraphicsAPI::CULLFACE_FRONT: 
                desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
                break;
            case GraphicsAPI::CULLFACE_BACK: 
                desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
                break;
            case GraphicsAPI::CULLFACE_FRONT_AND_BACK: 
                desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
                break;
            default:
                NEVER_HAPPEN;
            }

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateRasterizerState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->RSSetState(state);
            state->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void SetFrontFaceWinding(const GraphicsAPI::eWinding winding)
        {
            ID3D11RasterizerState* state;
            D3D11_RASTERIZER_DESC desc;
            dx11::g_pImmediateContext->RSGetState(&state);
            state->GetDesc(&desc);

            switch (winding)
            {
            case GraphicsAPI::CW:
                desc.FrontCounterClockwise = false;
                break;
            case GraphicsAPI::CCW: 
                desc.FrontCounterClockwise = true;
                break;
            default:
                NEVER_HAPPEN;
            }

            state->Release();
            HRESULT hr = dx11::g_pd3dDevice->CreateRasterizerState(&desc, &state);
            assert(FAILED(hr) == false);
            dx11::g_pImmediateContext->RSSetState(state);
            state->Release();
        }




        DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferColorBuffer(const float r, const float g, const float b, const float a)
        {
            FLOAT color[4] = { r, g, b, a };
            dx11::g_pImmediateContext->ClearRenderTargetView(dx11::BackBufferRenderTargetView, color);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferDepthBuffer(const double depthValue)
        {
            dx11::g_pImmediateContext->ClearDepthStencilView(dx11::BackBufferDepthStencilView, D3D11_CLEAR_DEPTH, depthValue, 0);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferStencilBuffer(const int stencilValue)
        {
            dx11::g_pImmediateContext->ClearDepthStencilView(dx11::BackBufferDepthStencilView, D3D11_CLEAR_STENCIL, 0.0f, stencilValue);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferDepthStencilBuffer(const double depthValue, const int stencilValue)
        {
            dx11::g_pImmediateContext->ClearDepthStencilView(dx11::BackBufferDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depthValue, stencilValue);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferColorBuffer
        (
            unsigned long long textureViewObject,
            const unsigned int colorTextureIndex,
            const float r,
            const float g,
            const float b,
            const float a
        )
        {
            ID3D11RenderTargetView* const renderTargetView = reinterpret_cast<ID3D11RenderTargetView*>(textureViewObject);

            FLOAT color[4] = { r, g, b, a };
            dx11::g_pImmediateContext->ClearRenderTargetView(renderTargetView, color);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferDepthBuffer(unsigned long long textureViewObject, const double depthValue)
        {
            ID3D11DepthStencilView* const depthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(textureViewObject);

            dx11::g_pImmediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, depthValue, 0);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferStencilBuffer(unsigned long long textureViewObject, const int stencilValue)
        {
            ID3D11DepthStencilView* const depthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(textureViewObject);

            dx11::g_pImmediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_STENCIL, 0, stencilValue);
        }

        DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferDepthStencilBuffer(unsigned long long textureViewObject, const double depthValue, const int stencilValue)
        {
            ID3D11DepthStencilView* const depthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(textureViewObject);

            dx11::g_pImmediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depthValue, stencilValue);
        }

        DOOMS_ENGINE_GRAPHICS_API unsigned long long GenerateFrameBuffer()
        {
            return 0;
        }

        DOOMS_ENGINE_GRAPHICS_API void DestroyFrameBuffer(unsigned long long frameBufferObject)
        {
        }

        DOOMS_ENGINE_GRAPHICS_API unsigned long long Attach2DColorTextureToFrameBuffer
        (
            const unsigned long long frameBufferObject,
            const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint,
            const GraphicsAPI::eTextureBindTarget textureBindTarget,
            const unsigned long long textureBufferObject,
            const unsigned int lodLevel
        )
		{
            assert(textureBufferObject != 0);

            ID3D11Texture2D* const textureResource = reinterpret_cast<ID3D11Texture2D*>(textureBufferObject);

            ID3D11RenderTargetView* renderTargetView;
           
			const HRESULT hr = dx11::g_pd3dDevice->CreateRenderTargetView(textureResource, nullptr, &renderTargetView);
            assert(FAILED(hr) == false);
            return reinterpret_cast<unsigned long long>(renderTargetView);
		}

        DOOMS_ENGINE_GRAPHICS_API unsigned long long Attach2DDepthStencilTextureToFrameBuffer
        (
            const unsigned long long frameBufferObject,
            const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint,
            const GraphicsAPI::eTextureBindTarget textureBindTarget,
            const unsigned long long textureBufferObject,
            const unsigned int lodLevel
        )
        {
            assert(textureBufferObject != 0);

            ID3D11Texture2D* const textureResource = reinterpret_cast<ID3D11Texture2D*>(textureBufferObject);

            ID3D11DepthStencilView* depthStencilView;

            const HRESULT hr = dx11::g_pd3dDevice->CreateDepthStencilView(textureResource, nullptr, &depthStencilView);
            assert(FAILED(hr) == false);
            return reinterpret_cast<unsigned long long>(depthStencilView);
        }

        DOOMS_ENGINE_GRAPHICS_API unsigned long long CopyRenderTargetView(const unsigned long long renderTargetView)
        {
            assert(renderTargetView != 0);

            ID3D11RenderTargetView* const d3d11RenderTargetView = reinterpret_cast<ID3D11RenderTargetView*>(renderTargetView);

            ID3D11Resource* d3d11Resource = nullptr;
            d3d11RenderTargetView->GetResource(&d3d11Resource);

            ID3D11RenderTargetView* copyedRenderTargetView;

            const HRESULT hr = dx11::g_pd3dDevice->CreateRenderTargetView(d3d11Resource, nullptr, &copyedRenderTargetView);
            assert(FAILED(hr) == false);
            return reinterpret_cast<unsigned long long>(copyedRenderTargetView);
        }

        DOOMS_ENGINE_GRAPHICS_API unsigned long long Allocate2DTextureObject
        (
            const GraphicsAPI::eTextureBindTarget textureBindTarget,
            const unsigned int lodCount,
            const GraphicsAPI::eTextureInternalFormat textureInternalFormat,
            const GraphicsAPI::eTextureCompressedInternalFormat textureCompressedInternalFormat,
            const unsigned long long width,
            const unsigned long long height,
            const GraphicsAPI::eBindFlag bindFlag
        )
		{
            DXGI_FORMAT internalFormat;
            if (textureInternalFormat != GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
            {
                internalFormat = dooms::graphics::dx11::ConvertTextureInternalFormat_To_DXGI_FORMAT(textureInternalFormat);
            }
            else if (textureCompressedInternalFormat != GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
            {
                internalFormat = dooms::graphics::dx11::ConvertTextureCompressedInternalFormat_To_DXGI_FORMAT(textureCompressedInternalFormat);
            }
            else
            {
                NEVER_HAPPEN;
            }

            D3D11_TEXTURE2D_DESC textureDesc = {};
            textureDesc.Width = width;
            textureDesc.Height = height;
            textureDesc.MipLevels = lodCount;
            textureDesc.ArraySize = 1;
            textureDesc.Format = internalFormat;
            textureDesc.SampleDesc.Count = 1;
            //textureDesc.SampleDesc.Quality = 0;
            textureDesc.Usage = D3D11_USAGE_DEFAULT;
            textureDesc.BindFlags = dx11::Convert_eBindFlag_To_D3D11_BIND_FLAG(bindFlag);
            textureDesc.CPUAccessFlags = 0;
            textureDesc.MiscFlags = 0;

            ID3D11Texture2D* textureResourceObject;

            HRESULT hr = dx11::g_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &textureResourceObject);
            assert(FAILED(hr) == false);
            if(FAILED(hr))
            {
                return 0;
            }

            /*
            ID3D11ShaderResourceView* textureView;

            D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
            SRVDesc.Format = internalFormat;
            SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            SRVDesc.Texture2D.MipLevels = textureDesc.MipLevels;

            hr = dx11::g_pd3dDevice->CreateShaderResourceView(textureObject,
                &SRVDesc,
                &textureView
            );
            assert(FAILED(hr) == false);
            if (FAILED(hr))
            {
                return 0;
            }

            textureObject->Release();
            */

            return reinterpret_cast<unsigned long long>(textureResourceObject);
		}


        DOOMS_ENGINE_GRAPHICS_API void UploadPixelsTo2DTexture
        (
            const unsigned long long textureResourceObject,
            const GraphicsAPI::eTextureBindTarget textureBindTarget,
            const GraphicsAPI::eTargetTexture targetTexture,
            const unsigned int lodLevel,
            const unsigned int xOffset,
            const unsigned int yOffset,
            const unsigned long long width,
            const unsigned long long height,
            const GraphicsAPI::eTextureComponentFormat textureComponentFormat,
            const GraphicsAPI::eDataType dataType,
            const GraphicsAPI::eTextureInternalFormat textureInternalFormat,
            const GraphicsAPI::eTextureCompressedInternalFormat textureCompressedInternalFormat,
            const void* const pixelDatas,
            const size_t srcRowPitch, // understanding RowPitch https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-updatesubresource
            const size_t srcDepthPitch
        )
        {
            ID3D11Texture2D* const textureResource = reinterpret_cast<ID3D11Texture2D*>(textureResourceObject);

            const UINT res = D3D11CalcSubresource(lodLevel, 0, 1);

            /*
            D3D11_BOX offsetBOX{};
            offsetBOX.left = xOffset;
            offsetBOX.top = yOffset;
            offsetBOX.front = 0;
            offsetBOX.back = 0;
            offsetBOX.bottom = 0;
            offsetBOX.right = 0;
            */

            dx11::g_pImmediateContext->UpdateSubresource
			(
                textureResource, 
                res,
                nullptr, //&offsetBOX,
                pixelDatas, 
                srcRowPitch,
                srcDepthPitch
            );
            
        }

        DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateTextureViewObject(const unsigned long long textureObject)
        {
            assert(textureObject != 0);

            ID3D11Texture2D* const textureResource = reinterpret_cast<ID3D11Texture2D*>(textureObject);

            D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};

            D3D11_TEXTURE2D_DESC desc;
            textureResource->GetDesc(&desc);

            SRVDesc.Format = desc.Format;
            SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            SRVDesc.Texture2D.MipLevels = desc.MipLevels;

            ID3D11ShaderResourceView* shaderResourceView;

            const HRESULT hr = dx11::g_pd3dDevice->CreateShaderResourceView(textureResource,
                &SRVDesc,
                &shaderResourceView
            );
            assert(FAILED(hr) == false);

            if (FAILED(hr))
            {
                return 0;
            }
            else
            {
                return reinterpret_cast<unsigned long long>(shaderResourceView);
            }
        }

        DOOMS_ENGINE_GRAPHICS_API void DestroyTextureViewObject(unsigned long long textureViewObject)
		{
            assert(textureViewObject != 0);

            ID3D11ShaderResourceView* const shaderResourceView = reinterpret_cast<ID3D11ShaderResourceView*>(textureViewObject);
            shaderResourceView->Release();
		}

        DOOMS_ENGINE_GRAPHICS_API void DestroyTextureObject(unsigned long long textureObject)
        {
            assert(textureObject != 0);
            ID3D11Texture2D* const ID3D11TextureBuffer = reinterpret_cast<ID3D11Texture2D*>(textureObject);
            ID3D11TextureBuffer->Release();
        }

        DOOMS_ENGINE_GRAPHICS_API void BindTextureObject
        (
            const unsigned long long textureViewObject,
            const GraphicsAPI::eTextureBindTarget textureBindTarget,
            const unsigned int bindingLocation,
            const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
        )
        {
            ID3D11ShaderResourceView* const shaderResourceView = reinterpret_cast<ID3D11ShaderResourceView*>(textureViewObject);

            switch (targetPipeLineStage)
            {
            case GraphicsAPI::VERTEX_SHADER:
                dx11::g_pImmediateContext->VSSetShaderResources(bindingLocation, 1, &shaderResourceView);
                break;
            case GraphicsAPI::HULL_SHADER:
                dx11::g_pImmediateContext->HSSetShaderResources(bindingLocation, 1, &shaderResourceView);
                break;
            case GraphicsAPI::DOMAIN_SHADER:
                dx11::g_pImmediateContext->DSSetShaderResources(bindingLocation, 1, &shaderResourceView);
                break;
            case GraphicsAPI::GEOMETRY_SHADER:
                dx11::g_pImmediateContext->GSSetShaderResources(bindingLocation, 1, &shaderResourceView);
                break;
            case GraphicsAPI::PIXEL_SHADER:
                dx11::g_pImmediateContext->PSSetShaderResources(bindingLocation, 1, &shaderResourceView);
                break;
            case GraphicsAPI::COMPUTE_SHADER:
                dx11::g_pImmediateContext->CSSetShaderResources(bindingLocation, 1, &shaderResourceView);
                break;
            default:
                NEVER_HAPPEN;
            }
        }

        DOOMS_ENGINE_GRAPHICS_API void BindFrameBuffer
        (
            const unsigned int renderTargetCount,
            unsigned long long* const renderTargetViewObject,
            const unsigned int coloreTextureCount,
            unsigned long long depthStencilViewObject
        )
        {
            dx11::g_pImmediateContext->OMSetRenderTargets
			(
                renderTargetCount, 
                reinterpret_cast<ID3D11RenderTargetView* const*>(renderTargetViewObject),
                reinterpret_cast<ID3D11DepthStencilView*>(depthStencilViewObject)
            );
        }

        DOOMS_ENGINE_GRAPHICS_API void BindBackBuffer()
        {
	        dx11::g_pImmediateContext->OMSetRenderTargets(1, &dx11::BackBufferRenderTargetView, dx11::BackBufferDepthStencilView);
        }

        DOOMS_ENGINE_GRAPHICS_API void BindShader(const unsigned long long materialObject, const GraphicsAPI::eGraphicsPipeLineStage shaderType)
        {
            if (shaderType == GraphicsAPI::VERTEX_SHADER)
            {
                ID3D11VertexShader* const vertexShader = reinterpret_cast<ID3D11VertexShader*>(materialObject);
                dx11::g_pImmediateContext->VSSetShader(vertexShader, nullptr, 0);
            }
            else if (shaderType == GraphicsAPI::PIXEL_SHADER)
            {
                ID3D11PixelShader* const pixelShader = reinterpret_cast<ID3D11PixelShader*>(materialObject);
                dx11::g_pImmediateContext->PSSetShader(pixelShader, nullptr, 0);
            }
            else if (shaderType == GraphicsAPI::COMPUTE_SHADER)
            {
                ID3D11ComputeShader* const computeShader = reinterpret_cast<ID3D11ComputeShader*>(materialObject);
                dx11::g_pImmediateContext->CSSetShader(computeShader, nullptr, 0);
            }
            else if (shaderType == GraphicsAPI::GEOMETRY_SHADER)
            {
                ID3D11GeometryShader* const geometryShader = reinterpret_cast<ID3D11GeometryShader*>(materialObject);
                dx11::g_pImmediateContext->GSSetShader(geometryShader, nullptr, 0);
            }
            else if (shaderType == GraphicsAPI::DOMAIN_SHADER)
            {
                ID3D11DomainShader* const domainShader = reinterpret_cast<ID3D11DomainShader*>(materialObject);
                dx11::g_pImmediateContext->DSSetShader(domainShader, nullptr, 0);
            }
            else if (shaderType == GraphicsAPI::HULL_SHADER)
            {
                ID3D11HullShader* const hullShader = reinterpret_cast<ID3D11HullShader*>(materialObject);
                dx11::g_pImmediateContext->HSSetShader(hullShader, nullptr, 0);
            }
            else
            {
                NEVER_HAPPEN;
	        }
        }

        DOOMS_ENGINE_GRAPHICS_API bool CompileShader
        (
            unsigned long long& shaderObject,
            const GraphicsAPI::eGraphicsPipeLineStage shaderType,
            const char* const shaderText,
            const unsigned long long shaderTextSize
        )
        {
            bool isCompileShaderSuccess = false;

            const char* shaderTarget = nullptr;
            const char* entryPoint = nullptr;
            switch (shaderType)
            {
            case GraphicsAPI::VERTEX_SHADER:
                shaderTarget = "vs_5_0";
                entryPoint = "main";
                break;
            case GraphicsAPI::HULL_SHADER:
                shaderTarget = "hs_5_0";
                entryPoint = "main";
                break;
            case GraphicsAPI::DOMAIN_SHADER:
                shaderTarget = "ds_5_0";
                entryPoint = "main";
                break;
            case GraphicsAPI::GEOMETRY_SHADER:
                shaderTarget = "gs_5_0";
                entryPoint = "main";
                break;
            case GraphicsAPI::PIXEL_SHADER:
                shaderTarget = "ps_5_0";
                entryPoint = "main";
                break;
            case GraphicsAPI::COMPUTE_SHADER:
                shaderTarget = "cs_5_0";
                entryPoint = "main";
                break;
            default:
                NEVER_HAPPEN;
                isCompileShaderSuccess = false;
            }

            DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
            // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
            // Setting this flag improves the shader debugging experience, but still allows 
            // the shaders to be optimized and to run exactly the way they will run in 
            // the release configuration of this program.
            dwShaderFlags |= D3DCOMPILE_DEBUG;

            // Disable optimizations to further improve shader debugging
            dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
            ID3DBlob* shaderBlob = nullptr;
            ID3DBlob* errorBlob = nullptr;
            
            HRESULT hr = D3DCompile
			(
                shaderText,
                shaderTextSize,
                nullptr,
                NULL,
                NULL,
                entryPoint,
                shaderTarget,
                dwShaderFlags,
                NULL,
                &shaderBlob,
                &errorBlob
            );

            if (FAILED(hr) == false)
            {
                isCompileShaderSuccess = true;
            }
            else
            {
                if (errorBlob)
                {
                    OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
                    errorBlob->Release();
                    assert(false);
                }
                isCompileShaderSuccess = false;
            }
            if (errorBlob)
            {
                errorBlob->Release();
            }

            shaderObject =  reinterpret_cast<unsigned long long>(shaderBlob);

            return isCompileShaderSuccess;
        }

        DOOMS_ENGINE_GRAPHICS_API void DestroyShaderObject(unsigned long long shaderObject)
        {
            assert(shaderObject != 0);

            ID3DBlob* const shaderBlob = reinterpret_cast<ID3DBlob*>(shaderObject);
            if(shaderBlob != nullptr)
            {
                shaderBlob->Release();
            }
        }

        /// <summary>
        /// Release shader view
        /// </summary>
        /// <param name="shaderView"></param>
        /// <returns></returns>
        DOOMS_ENGINE_GRAPHICS_API void DestroyMaterial(unsigned long long shaderView)
        {
            assert(shaderView != 0);
            IUnknown* const ID3D11ShaderView = reinterpret_cast<IUnknown*>(shaderView);
            if(ID3D11ShaderView != nullptr)
            {
                ID3D11ShaderView->Release();
            }
        }

        DOOMS_ENGINE_GRAPHICS_API bool AttachShaderToMaterial
        (
            unsigned long long& shaderView,
            const unsigned long long materialObject,
            const unsigned long long shaderObject,
            const GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage // only used in dx11
        )
        {
            bool isSuccess = false;

            assert(shaderObject != 0);
            ID3DBlob* const shaderBlob = reinterpret_cast<ID3DBlob*>(shaderObject);

            if(shaderBlob != nullptr)
            {
                if (targetGraphicsPipeLineStage == GraphicsAPI::VERTEX_SHADER)
                {
                    ID3D11VertexShader* vertexShader = nullptr;
                    const HRESULT hr = dx11::g_pd3dDevice->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &vertexShader);
                    if (FAILED(hr) == false)
                    {
                        shaderView = reinterpret_cast<unsigned long long>(vertexShader);
                        isSuccess = true;
                    }
                }
                else if (targetGraphicsPipeLineStage == GraphicsAPI::HULL_SHADER)
                {
                    ID3D11HullShader* hullShader = nullptr;
                    const HRESULT hr = dx11::g_pd3dDevice->CreateHullShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &hullShader);
                    if (FAILED(hr) == false)
                    {
                        shaderView = reinterpret_cast<unsigned long long>(hullShader);
                        isSuccess = true;
                    }
                }
                else if (targetGraphicsPipeLineStage == GraphicsAPI::DOMAIN_SHADER)
                {
                    ID3D11DomainShader* domainShader = nullptr;
                    const HRESULT hr = dx11::g_pd3dDevice->CreateDomainShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &domainShader);
                    if (FAILED(hr) == false)
                    {
                        shaderView = reinterpret_cast<unsigned long long>(domainShader);
                        isSuccess = true;
                    }
                }
                else if (targetGraphicsPipeLineStage == GraphicsAPI::GEOMETRY_SHADER)
                {
                    ID3D11GeometryShader* geometryShader = nullptr;
                    const HRESULT hr = dx11::g_pd3dDevice->CreateGeometryShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &geometryShader);
                    if (FAILED(hr) == false)
                    {
                        shaderView = reinterpret_cast<unsigned long long>(geometryShader);
                        isSuccess = true;
                    }
                }
                else if (targetGraphicsPipeLineStage == GraphicsAPI::PIXEL_SHADER)
                {
                    ID3D11PixelShader* pixelShader = nullptr;
                    const HRESULT hr = dx11::g_pd3dDevice->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &pixelShader);
                    if (FAILED(hr) == false)
                    {
                        shaderView = reinterpret_cast<unsigned long long>(pixelShader);
                        isSuccess = true;
                    }
                }
                else if (targetGraphicsPipeLineStage == GraphicsAPI::COMPUTE_SHADER)
                {
                    ID3D11ComputeShader* computeShader = nullptr;
                    const HRESULT hr = dx11::g_pd3dDevice->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &computeShader);
                    if (FAILED(hr) == false)
                    {
                        shaderView = reinterpret_cast<unsigned long long>(computeShader);
                        isSuccess = true;
                    }
                }
                else
                {
                    NEVER_HAPPEN;
                }
            }
	        
            assert(isSuccess == true);

            return isSuccess;
        }

        DOOMS_ENGINE_GRAPHICS_API bool DetachShaderFromMaterial
        (
            unsigned long long shaderView,
            const unsigned long long materialObject,
            const unsigned long long shaderObject
        )
        {
            bool isSuccess = false;

            assert(shaderView != 0);
            IUnknown* const ID3D11ShaderView = reinterpret_cast<IUnknown*>(shaderView);
            if (ID3D11ShaderView != nullptr)
            {
                ID3D11ShaderView->Release();
                isSuccess = true;
            }

            return isSuccess;
        }

        DOOMS_ENGINE_GRAPHICS_API void BindIndexBufferObject
        (
            const unsigned long long indexBufferObject//, 
            //const unsigned long long offset
        )
        {
            assert(indexBufferObject != 0);
            ID3D11Buffer* const indexBuffer = reinterpret_cast<ID3D11Buffer*>(indexBufferObject);
            dx11::g_pImmediateContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        }

        DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateInputLayoutForD3D
		(
            const void* const inputElementDesces,
            const unsigned int inputElementCount,
            unsigned long long vertexShaderBlobObject
        )
        {
            assert(inputElementDesces != nullptr);
            assert(inputElementCount > 0);
            assert(vertexShaderBlobObject != 0);

            if(inputElementDesces != nullptr && inputElementCount > 0 && vertexShaderBlobObject != 0)
            {
                ID3DBlob* const vertexShaderBlob = reinterpret_cast<ID3DBlob*>(vertexShaderBlobObject);

                ID3D11InputLayout* vertexLayout = nullptr;

                HRESULT hr = dx11::g_pd3dDevice->CreateInputLayout
                (
                    reinterpret_cast<const D3D11_INPUT_ELEMENT_DESC*>(inputElementDesces),
                    inputElementCount,
                    vertexShaderBlob->GetBufferPointer(),
                    vertexShaderBlob->GetBufferSize(),
                    &vertexLayout
                );

                assert(FAILED(hr) == false);
                if (FAILED(hr))
                    return hr;
                
                return reinterpret_cast<unsigned long long>(vertexLayout);
            }
            else
            {
                assert(false);
                return 0;
            }           
        }

        DOOMS_ENGINE_GRAPHICS_API void BindInputLayoutForD3D(const unsigned long long inputLayoutObject)
		{
            ID3D11InputLayout* const inputLayout = reinterpret_cast<ID3D11InputLayout*>(inputLayoutObject);
			dx11::g_pImmediateContext->IASetInputLayout(inputLayout);
		}

        DOOMS_ENGINE_GRAPHICS_API void DestoryInputLayoutForD3D(unsigned long long inputLayoutObject)
        {
            ID3D11InputLayout* const inputLayout = reinterpret_cast<ID3D11InputLayout*>(inputLayoutObject);
            inputLayout->Release();
        }
        
       

        DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateBufferObject
        (
            const GraphicsAPI::eBufferTarget bufferTarget,
            const unsigned long long bufferSize,
            const void* const initialData
        )
        {
            D3D11_BUFFER_DESC bd = {};
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.ByteWidth = bufferSize;
            bd.CPUAccessFlags = 0;
            bd.MiscFlags = 0;
            bd.StructureByteStride = 0;

            switch (bufferTarget)
            {
            case GraphicsAPI::ARRAY_BUFFER:
               
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                break;

            case GraphicsAPI::ELEMENT_ARRAY_BUFFER:
                bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
                break;

            case GraphicsAPI::UNIFORM_BUFFER:
                bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                break;

            default:
                NEVER_HAPPEN;
            }

            ID3D11Buffer* buffer;

            D3D11_SUBRESOURCE_DATA* data = NULL;


            D3D11_SUBRESOURCE_DATA initData = {};
            if(initialData != nullptr)
            {
                initData.pSysMem = initialData;
                data = &initData;
            }
            
         
            const HRESULT hr = dx11::g_pd3dDevice->CreateBuffer(&bd, data, &buffer);
            assert(FAILED(hr) == false);

            return reinterpret_cast<unsigned long long>(buffer);
        }

        DOOMS_ENGINE_GRAPHICS_API void EnableVertexAttributeArrayIndex(const unsigned int vertexAttributeIndex)
        {

        }

        DOOMS_ENGINE_GRAPHICS_API void DefineVertexAttributeLayout
        (
            const unsigned long long vertexBufferObject,
            const unsigned int vertexAttributeIndex,
            const unsigned int componentCount,
            const unsigned int stride,
            const unsigned int offset
        )
        {

        }

        DOOMS_ENGINE_GRAPHICS_API void UpdateDataToBuffer
        (
            const unsigned long long bufferObject,
            const GraphicsAPI::eBufferTarget bindBufferTarget,
            const unsigned long long offset,
            const unsigned long long dataSize,
            const void* const data
        )
        {
            assert(bufferObject != 0);
            ID3D11Resource* const bufferResource = reinterpret_cast<ID3D11Resource*>(bufferObject);
            
            dx11::g_pImmediateContext->UpdateSubresource(bufferResource, NULL, nullptr, data, 0, 0);
        }

        DOOMS_ENGINE_GRAPHICS_API void BindConstantBuffer
        (
            const unsigned long long bufferObject,
            const unsigned int bindingPoint,
            const GraphicsAPI::eGraphicsPipeLineStage pipeLineStage
        )
        {
            ID3D11Buffer* const buffer = reinterpret_cast<ID3D11Buffer*>(bufferObject);

            switch (pipeLineStage)
            {
            case GraphicsAPI::VERTEX_SHADER:
                dx11::g_pImmediateContext->VSSetConstantBuffers(bindingPoint, 1, &buffer);
                break;
            case GraphicsAPI::HULL_SHADER:
                dx11::g_pImmediateContext->HSSetConstantBuffers(bindingPoint, 1, &buffer);
                break;
            case GraphicsAPI::DOMAIN_SHADER:
                dx11::g_pImmediateContext->DSSetConstantBuffers(bindingPoint, 1, &buffer);
                break;
            case GraphicsAPI::GEOMETRY_SHADER:
                dx11::g_pImmediateContext->GSSetConstantBuffers(bindingPoint, 1, &buffer);
                break;
            case GraphicsAPI::PIXEL_SHADER:
                dx11::g_pImmediateContext->PSSetConstantBuffers(bindingPoint, 1, &buffer);
                break;
            case GraphicsAPI::COMPUTE_SHADER:
                dx11::g_pImmediateContext->CSSetConstantBuffers(bindingPoint, 1, &buffer);
                break;
            default:
                NEVER_HAPPEN;
            }
        }

        DOOMS_ENGINE_GRAPHICS_API void BindVertexDataBuffer
        (
            const unsigned long long bufferObject,
            const unsigned int bindingPosition,
            const unsigned int stride,
            const unsigned int offset
        )
        {
            ID3D11Buffer* const buffer = reinterpret_cast<ID3D11Buffer*>(bufferObject);
            dx11::g_pImmediateContext->IASetVertexBuffers(bindingPosition, 1, &buffer, &stride, &offset);
        }

        DOOMS_ENGINE_GRAPHICS_API void BindBuffer
        (
            const unsigned long long bufferObject,
            const unsigned int bindingPosition,
            const GraphicsAPI::eBufferTarget bindBufferTarget,
            const GraphicsAPI::eGraphicsPipeLineStage targetPipeLienStage
        )
        {
            assert(bufferObject != 0);

            ID3D11Buffer* const buffer = reinterpret_cast<ID3D11Buffer*>(bufferObject);

            switch (bindBufferTarget)
            {
            case GraphicsAPI::ELEMENT_ARRAY_BUFFER:
                BindIndexBufferObject(bufferObject);
                break;
            case GraphicsAPI::TEXTURE_BUFFER:
                BindTextureObject(bufferObject, GraphicsAPI::eTextureBindTarget::TEXTURE_2D, bindingPosition, targetPipeLienStage);
                break;
            case GraphicsAPI::UNIFORM_BUFFER:
                BindConstantBuffer(bufferObject, bindingPosition, targetPipeLienStage);
                break;
            default:
                NEVER_HAPPEN;
            }
        }

        DOOMS_ENGINE_GRAPHICS_API void DestroyBuffer(unsigned long long bufferID)
        {
            ID3D11Buffer* buffer = reinterpret_cast<ID3D11Buffer*>(bufferID);
            buffer->Release();
        }
        
        DOOMS_ENGINE_GRAPHICS_API void BindRenderBuffer(const unsigned long long renderBufferObject)
        {
            // DX11 doesn't have "Binding" concept

            //glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
        }

        DOOMS_ENGINE_GRAPHICS_API void Draw
        (
            const GraphicsAPI::ePrimitiveType primitiveType,
            const unsigned long long vertexCount,
            const unsigned long long startVertexLocation
        )
        {
            assert((unsigned int)primitiveType < GraphicsAPI::ePrimitiveType::END);

            dx11::g_pImmediateContext->IASetPrimitiveTopology(dx11::Convert_ePrimitiveType_To_D3D_PRIMITIVE_TOPOLOGY(primitiveType));
            dx11::g_pImmediateContext->Draw(vertexCount, startVertexLocation);
            dx11::DrawCallCounter++;
        }


        DOOMS_ENGINE_GRAPHICS_API void DrawIndexed
        (
            const GraphicsAPI::ePrimitiveType primitiveType,
            const unsigned long long indiceCount,
            const void* const indices
        )
        {
            assert((unsigned int)primitiveType < GraphicsAPI::ePrimitiveType::END);

            dx11::g_pImmediateContext->IASetPrimitiveTopology(dx11::Convert_ePrimitiveType_To_D3D_PRIMITIVE_TOPOLOGY(primitiveType));
            dx11::g_pImmediateContext->DrawIndexed(indiceCount, 0, 0);
            dx11::DrawCallCounter++;
        }

        DOOMS_ENGINE_GRAPHICS_API void BlitFrameBuffer
        (
            const unsigned long long ReadFrameBufferObject,
            const unsigned int ReadBindingPoint,
            const unsigned long long DrawFrameBufferObject,
            const unsigned int DrawBindingPoint,
            const int srcX0, const int srcY0, const int srcX1, const int srcY1,
            const int dstX0, const int dstY0, const int dstX1, const int dstY1,
            const GraphicsAPI::eBufferBitType mask,
            const GraphicsAPI::eImageInterpolation filter
        )
		{
            if( (mask & GraphicsAPI::COLOR_BUFFER) != 0 )
            {
                ID3D11Resource* fromResource = nullptr;
                if (ReadFrameBufferObject != 0)
                {
                    fromResource = reinterpret_cast<ID3D11Resource*>(ReadFrameBufferObject);
                }
                else
                {
                    ID3D11Texture2D* pBackBuffer = nullptr; // https://vsts2010.tistory.com/517
                    const HRESULT hr = dx11::g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
                    assert(FAILED(hr) == false);
                    if (FAILED(hr))
                    {
                        return;
                    }

                    fromResource = pBackBuffer;
                }

                ID3D11Resource* toResource = nullptr;
                if (DrawFrameBufferObject != 0)
                {
                    toResource = reinterpret_cast<ID3D11Resource*>(ReadFrameBufferObject);
                }
                else
                {
                    ID3D11Texture2D* pBackBuffer = nullptr; // https://vsts2010.tistory.com/517
                    const HRESULT hr = dx11::g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
                    assert(FAILED(hr) == false);
                    if (FAILED(hr))
                    {
                        return;
                    }

                    toResource = pBackBuffer;
                }

                assert(fromResource != nullptr);
                assert(toResource != nullptr);

                dx11::g_pImmediateContext->CopyResource
                (
                    fromResource,
                    toResource
                );
            }

            if
			(
                ((mask & GraphicsAPI::DEPTH_BUFFER) != 0) ||
                ((mask & GraphicsAPI::STENCIL_BUFFER) != 0) ||
                ((mask & GraphicsAPI::DEPTH_STENCIL_BUFFER) != 0)
            )
            {
                ID3D11Resource* fromResource = nullptr;
                if (ReadFrameBufferObject != 0)
                {
                    fromResource = reinterpret_cast<ID3D11Resource*>(ReadFrameBufferObject);
                }
                else
                {
                    assert(dx11::BackBufferDepthStencilView != nullptr);
                    dx11::BackBufferDepthStencilView->GetResource(&fromResource);
                }

                ID3D11Resource* toResource = nullptr;
                if (DrawFrameBufferObject != 0)
                {
                    toResource = reinterpret_cast<ID3D11Resource*>(ReadFrameBufferObject);
                }
                else
                {
                    assert(dx11::BackBufferDepthStencilView != nullptr);
                    dx11::BackBufferDepthStencilView->GetResource(&toResource);
                }

                assert(fromResource != nullptr);
                assert(toResource != nullptr);

                dx11::g_pImmediateContext->CopyResource
                (
                    fromResource,
                    toResource
                );
            }

		}


        DOOMS_ENGINE_GRAPHICS_API unsigned char* ReadPixels
        (
            const unsigned long long frameBufferObject,
            const GraphicsAPI::eBufferMode bufferMode,
            const unsigned long long bufferSize,
            const int startX,
            const int startY,
            const int width,
            const int height,
            const GraphicsAPI::eTextureComponentFormat pixelFormat,
            const GraphicsAPI::eDataType dataType
        )
        {
            assert(0);
            return nullptr;
        }

	}
}
