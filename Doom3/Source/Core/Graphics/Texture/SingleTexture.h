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
				eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data);

			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data);


			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);


			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);

			void Tex2DMipMapImages(std::vector<const DirectX::Image*> mipmapDatas);
			virtual void TexImage1D(int level, const void* data) const noexcept final;
			virtual void TexImage2D(int level, const void* data) const noexcept final;
			void TexImage1D(int level, const DirectX::Image* directXImage) const noexcept;
			void TexImage2D(int level, const DirectX::Image* directXImage) const noexcept;
		};
	}
}