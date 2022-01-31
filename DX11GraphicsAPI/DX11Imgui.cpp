#include "PlatformImgui/PlatformImgui.h"
#include "DX11GraphicsAPI.h"

#include <cassert>

//#include "imgui/backends/imgui_impl_dx10.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"

namespace dooms
{
	namespace input
	{
		DOOMS_ENGINE_GRAPHICS_API bool InitializePlatformImgui(void* platformWindow, const char* apiVersion, ImGuiContext* const imGuiContext, ImGuiMemAllocFunc p_alloc_func, ImGuiMemFreeFunc p_free_func, void* p_user_data)
		{
			assert(imGuiContext != nullptr);
			assert(platformWindow != nullptr);

			ImGui::SetCurrentContext(imGuiContext);
			ImGui::SetAllocatorFunctions(p_alloc_func, p_free_func, p_user_data);
			
			bool isSuccess = true;

			isSuccess &= ImGui_ImplDX11_Init(dooms::graphics::dx11::GetDevice(), dooms::graphics::dx11::GetDeviceContext());
			isSuccess &= ImGui_ImplWin32_Init(platformWindow);

			return isSuccess;
		}

		DOOMS_ENGINE_GRAPHICS_API bool ShutDownPlatformImgui()
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();

			return true;
		}

		DOOMS_ENGINE_GRAPHICS_API void PreRenderPlatformImgui()
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
		}

		DOOMS_ENGINE_GRAPHICS_API void PostRenderPlatformImgui()
		{
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	}
}