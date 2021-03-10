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
			inline void TexImage1D(int level, const void* data) noexcept final
			{
				this->BindTexture();
				if (this->mInternalFormat != eTextureInternalFormat::NONE)
				{
					glTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(this->mInternalFormat), this->mWidth, 0, static_cast<unsigned int>(this->mDataFormat), static_cast<unsigned int>(this->mDataType), data);
				}
				else if (this->mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
				{
					//glCompressedTexImage1D()
				}
				else
				{
					NEVER_HAPPEN;
				}
			
			}
			inline void TexImage2D(int level, const void* data) noexcept final
			{
				this->BindTexture();
				glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(this->mInternalFormat), this->mWidth, this->mHeight, 0, static_cast<unsigned int>(this->mDataFormat), static_cast<unsigned int>(this->mDataType), data);
				if (this->mInternalFormat != eTextureInternalFormat::NONE)
				{

				}
				else if (this->mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
				{

				}
				else
				{
					NEVER_HAPPEN;
				}
			}
			void TexImage1D(int level, const DirectX::Image* directXImage) noexcept;
			void TexImage2D(int level, const DirectX::Image* directXImage) noexcept;
		};
	}
}