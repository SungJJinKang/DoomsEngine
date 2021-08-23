#pragma once
#include "Texture.h"

namespace doom
{
	namespace graphics
	{
		class CubemapTexture : public Texture
		{
		public:
			CubemapTexture() = delete;
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data);
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data);
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data);
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data);

			
			virtual ~CubemapTexture() = default;
			CubemapTexture(const CubemapTexture&) = delete;
			CubemapTexture& operator=(const CubemapTexture&) noexcept = delete;

			CubemapTexture(CubemapTexture&&) noexcept = default;
			CubemapTexture& operator=(CubemapTexture&&) noexcept = default;


			inline void TexImage1D(int level, const void* data) noexcept override
			{
				BindTexture();
				for (unsigned int i = 0; i < 6; i++)
				{
					glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(mInternalFormat), mWidth, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
				}
			}

			inline void TexImage1D(int face, int level, const void* data) noexcept
			{
				BindTexture();
				glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(mInternalFormat), mWidth, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
			}


			inline void TexImage2D(int level, const void* data) noexcept override
			{
				BindTexture();
				for (unsigned int i = 0; i < 6; i++)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(mInternalFormat), mWidth, mHeight, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
				}
			}

			inline void TexImage2D(int face, int level, const void* data) noexcept
			{
				BindTexture();
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(mInternalFormat), mWidth,mHeight, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
			}

		};
	}
}