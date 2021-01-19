#pragma once

#include "Texture.h"

namespace Doom
{
	class CubemapTexture : public Texture
	{
	public:
		
		CubemapTexture(TextureType textureType,
			TargetTexture target, InternalFormat internalFormat, unsigned int width, unsigned int height, DataFormat format, DataType type, const void* data);

		void TexImage2D(int level, InternalFormat internalformat, int width, int height, DataFormat format, DataType type, const void* data) override;
		void TexImage2D(int face, int level, InternalFormat internalformat, int width, int height, DataFormat format, DataType type, const void* data);
	};
}
