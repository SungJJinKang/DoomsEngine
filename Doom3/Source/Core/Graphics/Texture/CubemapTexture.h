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


			void TexImage1D(int level, const void* data) const noexcept override;

			void TexImage1D(int face, int level, const void* data) const noexcept;


			void TexImage2D(int level, const void* data) const noexcept override;

			void TexImage2D(int face, int level, const void* data) const noexcept;

		};
	}
}