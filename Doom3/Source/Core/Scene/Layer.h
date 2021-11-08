#pragma once

#include <string>

#define MAX_LAYER_COUNT (32)
#define RESERVED_LAYER_COUNT (10)

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
	};

}