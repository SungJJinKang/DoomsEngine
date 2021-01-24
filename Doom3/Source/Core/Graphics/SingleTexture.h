#pragma once

#include "Texture.h"

namespace doom
{
	namespace graphics
	{
		class SingleTexture : public Texture
		{
		private:

		public:
			//SingleTexture
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data);


			void TexImage2D(int level, eInternalFormat internalformat, int width, int height, eDataFormat format, eDataType type, const void* data) final;

		};
	}
}