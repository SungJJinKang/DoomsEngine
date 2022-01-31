#pragma once
#include <d3d11.h>

namespace dooms
{
	namespace graphics
	{

		namespace dx11
		{
			extern ID3D11Device* GetDevice();
			extern ID3D11DeviceContext* GetDeviceContext();
		}
	}
}
