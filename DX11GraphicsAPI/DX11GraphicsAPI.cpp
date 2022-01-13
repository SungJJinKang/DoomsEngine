#include "GraphicsAPI.h"

#include "stdio.h"
#include "assert.h"

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "DDSTextureLoader.h"
#include "resource.h"


#undef NEVER_HAPPEN
#ifdef _DEBUG
#define NEVER_HAPPEN assert(false)
#else
#define NEVER_HAPPEN __assume(0)
#endif

#define MIN(X, Y) ((X < Y) ? (X) : (Y));
#define MAX(X, Y) ((X > Y) ? (X) : (Y));


// https://anteru.net/blog/2013/porting-from-directx11-to-opengl-4-2-tales-from-the-trenches/
// https://anteru.net/blog/2013/porting-from-directx11-to-opengl-4-2-textures-samplers/

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 Tex;
};

struct CBNeverChanges
{
	DirectX::XMMATRIX mView;
};

struct CBChangeOnResize
{
	DirectX::XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMFLOAT4 vMeshColor;
};


namespace dooms
{
	namespace graphics
	{

		namespace dx11
		{
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
                    return DXGI_FORMAT_D24_UNORM_S8_UINT;
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

            static HINSTANCE                           g_hInst = nullptr;
            static HWND                                g_hWnd = nullptr;
            static  D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
            static D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
            static ID3D11Device* g_pd3dDevice = nullptr;
            static ID3D11Device1* g_pd3dDevice1 = nullptr;
            static ID3D11DeviceContext* g_pImmediateContext = nullptr;
            static  ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
            static IDXGISwapChain* g_pSwapChain = nullptr;
            static  IDXGISwapChain1* g_pSwapChain1 = nullptr;
            static ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
            static ID3D11Texture2D* g_pDepthStencil = nullptr;
            static ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
            static ID3D11VertexShader* g_pVertexShader = nullptr;
            static  ID3D11PixelShader* g_pPixelShader = nullptr;
            static ID3D11InputLayout* g_pVertexLayout = nullptr;
            static ID3D11Buffer* g_pVertexBuffer = nullptr;
            static ID3D11Buffer* g_pIndexBuffer = nullptr;
            static  ID3D11Buffer* g_pCBNeverChanges = nullptr;
            static  ID3D11Buffer* g_pCBChangeOnResize = nullptr;
            static ID3D11Buffer* g_pCBChangesEveryFrame = nullptr;
            static  ID3D11ShaderResourceView* g_pTextureRV = nullptr;
            static  ID3D11SamplerState* g_pSamplerLinear = nullptr;
            static  DirectX::XMMATRIX                            g_World;
            static DirectX::XMMATRIX                            g_View;
            static  DirectX::XMMATRIX                            g_Projection;
            static  DirectX::XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);


            static HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
            static HRESULT InitDevice();
            static void CleanupDevice();
            static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
            static void Render();

            //--------------------------------------------------------------------------------------
			// Helper for compiling shaders with D3DCompile
			//
			// With VS 11, we could load up prebuilt .cso files instead...
			//--------------------------------------------------------------------------------------
            static HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
            {
                HRESULT hr = S_OK;

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

                ID3DBlob* pErrorBlob = nullptr;
                
                hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
                    dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
                if (FAILED(hr))
                {
                    if (pErrorBlob)
                    {
                        OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
                        pErrorBlob->Release();
                    }
                    return hr;
                }
                if (pErrorBlob) pErrorBlob->Release();

                return S_OK;
            }

            
            static HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
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
                wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
                wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
                wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.lpszMenuName = nullptr;
                wcex.lpszClassName = L"SUNG JIN KANG GAME ENGINE WINDOW CLASS";
                wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
                if (!RegisterClassEx(&wcex))
                    return E_FAIL;

				// Create window
				g_hInst = hInstance;
				RECT rc = { 0, 0, 800, 600 };
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

                UINT createDeviceFlags = 0;
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
                    D3D_FEATURE_LEVEL_11_0,
                    D3D_FEATURE_LEVEL_10_1,
                    D3D_FEATURE_LEVEL_10_0,
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

                hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
                pBackBuffer->Release();
                if (FAILED(hr))
                    return hr;

                // Create depth stencil texture
                D3D11_TEXTURE2D_DESC descDepth = {};
                descDepth.Width = width;
                descDepth.Height = height;
                descDepth.MipLevels = 1;
                descDepth.ArraySize = 1;
                descDepth.Format = dooms::graphics::dx11::ConvertTextureInternalFormat_To_DXGI_FORMAT(GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32F);
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
                hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);
                if (FAILED(hr))
                    return hr;

                g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);


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

                return S_OK;
            }

            static void Render()
            {
                // Update our time
                static float t = 0.0f;
                if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
                {
                    t += (float)DirectX::XM_PI * 0.0125f;
                }
                else
                {
                    static ULONGLONG timeStart = 0;
                    ULONGLONG timeCur = GetTickCount64();
                    if (timeStart == 0)
                        timeStart = timeCur;
                    t = (timeCur - timeStart) / 1000.0f;
                }

                // Rotate cube around the origin
                g_World = DirectX::XMMatrixRotationY(t);

                // Modify the color
                g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
                g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
                g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

                //
                // Clear the back buffer
                //
                g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, DirectX::Colors::MidnightBlue);

                //
                // Clear the depth buffer to 1.0 (max depth)
                //
                g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

                //
                // Update variables that change once per frame
                //
                CBChangesEveryFrame cb;
                cb.mWorld = XMMatrixTranspose(g_World);
                cb.vMeshColor = g_vMeshColor;
                g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);

                //
                // Render the cube
                //
                g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
                g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
                g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
                g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
                g_pImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
                g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
                g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
                g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
                g_pImmediateContext->DrawIndexed(36, 0, 0);

                //
                // Present our back buffer to our front buffer
                //
                g_pSwapChain->Present(0, 0);
            }

            //--------------------------------------------------------------------------------------
			// Clean up the objects we've created
			//--------------------------------------------------------------------------------------
            static void CleanupDevice()
            {
                if (g_pImmediateContext) g_pImmediateContext->ClearState();

                if (g_pSamplerLinear) g_pSamplerLinear->Release();
                if (g_pTextureRV) g_pTextureRV->Release();
                if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
                if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
                if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
                if (g_pVertexBuffer) g_pVertexBuffer->Release();
                if (g_pIndexBuffer) g_pIndexBuffer->Release();
                if (g_pVertexLayout) g_pVertexLayout->Release();
                if (g_pVertexShader) g_pVertexShader->Release();
                if (g_pPixelShader) g_pPixelShader->Release();
                if (g_pDepthStencil) g_pDepthStencil->Release();
                if (g_pDepthStencilView) g_pDepthStencilView->Release();
                if (g_pRenderTargetView) g_pRenderTargetView->Release();
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
		}

		

		DOOMS_ENGINE_GRAPHICS_API double GetTime()
		{
			assert(0);
			return 0;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphicsAPI(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum)
		{
			HINSTANCE hInstance = GetModuleHandle(NULL);
            if(hInstance == NULL)
            {
                printf("Fail to GetModuleHandle : %u", GetLastError());
            }

			if (FAILED(dx11::InitWindow(hInstance, true)))
				return 0;

			if (FAILED(dx11::InitDevice()))
			{
				dx11::CleanupDevice();
				return 0;
			}

			// Main message loop
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
					dx11::Render(); // For testing
				}
			}

			dx11::CleanupDevice();

			return (int)msg.wParam;

		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeinitializeGraphicsAPI()
		{
            dx11::CleanupDevice();
			return 0;
		}

		DOOMS_ENGINE_GRAPHICS_API void SwapBuffer() noexcept
		{
			dx11::g_pSwapChain->Present(0, 0); // Swap Back buffer
		}

        DOOMS_ENGINE_GRAPHICS_API void SetViewport(const unsigned int index, const int startX, const int startY, const unsigned int width, const unsigned int height)
        {
            // Fetch existing viewports

            UINT vpCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
            D3D11_VIEWPORT* vp = new D3D11_VIEWPORT[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

            dx11::g_pImmediateContext->RSGetViewports(&vpCount, vp);
            assert(vpCount > index);

            //

            vpCount = MAX(index + 1, vpCount);

            vp[index].Width = (FLOAT)width;
            vp[index].Height = (FLOAT)height;
            vp[index].MinDepth = 0.0f;
            vp[index].MaxDepth = 1.0f;
            vp[index].TopLeftX = (FLOAT)startX;
            vp[index].TopLeftY = (FLOAT)startY;
            dx11::g_pImmediateContext->RSSetViewports(vpCount, vp);

            delete[] vp;
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
	}
}
