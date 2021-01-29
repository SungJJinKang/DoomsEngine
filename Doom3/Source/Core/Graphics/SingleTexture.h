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
				eTargetTexture target, eInternalFormat internalFormat, unsigned int width, eDataFormat format, eDataType type, const void* data);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data);

			inline void TexImage1D(int level, eInternalFormat internalformat, int width, eDataFormat format, eDataType type, const void* data) noexcept final
			{
				this->BindTexture();
				glTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(internalformat), width, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
			}
			inline void TexImage2D(int level, eInternalFormat internalformat, int width, int height, eDataFormat format, eDataType type, const void* data) noexcept final
			{
				this->BindTexture();
				glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
			}

		};
	}
}