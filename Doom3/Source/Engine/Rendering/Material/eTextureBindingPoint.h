#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		/// <summary>
		/// Texture binding point
		/// Bindin != location
		/// </summary>
		enum D_ENUM eTextureBindingPoint : UINT32
		{
			AlbedoTexture = 0,
			NormalTexture = 1,
			MetalnessTexture = 2,
			RoughnessTexture = 3,
			SpecularTexture = 4,
			IrradianceTexture = 5,
			SpecularBRDF_LUT = 6
		};
	}
}