#pragma once

#include <string>

#include <Core.h>

namespace dooms
{

	/// <summary>
	/// what is layer ?
	/// https://docs.unity3d.com/Manual/Layers.html
	/// 
	/// This will be used in camera(render specific layer), light 
	/// </summary>
	struct DOOM_API D_STRUCT Layer
	{
		std::string mLayerName;
		UINT32 mLayerIndex;

		Layer();
		Layer(const char* const layerName);
	};
}
