#pragma once

#include <Windows.h>


namespace dooms
{
	namespace imgui
	{
		namespace dx11
		{
            // Win32 message handler
			LRESULT _WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		}
	}
}
