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
			SingleTexture() = delete;
			SingleTexture(const SingleTexture&) = delete;
			SingleTexture& operator=(const SingleTexture&) noexcept = delete;

			SingleTexture(SingleTexture&&) noexcept = default;
			SingleTexture& operator=(SingleTexture&&) noexcept = default;

			SingleTexture(eTextureType textureType,
				eTargetTexture target, eInternalFormat internalFormat, unsigned int width, eDataFormat format, eDataType type, const void* data);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data);

			inline void TexImage1D(int level, const void* data) noexcept final
			{
				this->BindTexture();
				glTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(this->mInternalFormat), this->mWidth, 0, static_cast<unsigned int>(this->mDataFormat), static_cast<unsigned int>(this->mDataType), data);
			}
			inline void TexImage2D(int level, const void* data) noexcept final
			{
				this->BindTexture();
				glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(this->mInternalFormat), this->mWidth, this->mHeight, 0, static_cast<unsigned int>(this->mDataFormat), static_cast<unsigned int>(this->mDataType), data);
			}

		};
	}
}