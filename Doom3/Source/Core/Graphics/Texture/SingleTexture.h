#pragma once

#include "Texture.h"

namespace doom
{
	namespace graphics
	{
		class SingleTexture : public Texture
		{
			DOBJECT_CLASS_BODY(SingleTexture, doom::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(Texture)

		private:

		public:
			SingleTexture() = delete;
			virtual ~SingleTexture() = default;
			SingleTexture(const SingleTexture&) = delete;
			SingleTexture& operator=(const SingleTexture&) noexcept = delete;

			SingleTexture(SingleTexture&&) noexcept = default;
			SingleTexture& operator=(SingleTexture&&) noexcept = default;

			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data);

			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data);


			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);


			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			SingleTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas);

			void Tex2DMipMapImages(std::vector<const DirectX::Image*> mipmapDatas);
			virtual void TexImage1D(INT32 level, const void* data) const noexcept final;
			virtual void TexImage2D(INT32 level, const void* data) const noexcept final;
			void TexImage1D(INT32 level, const DirectX::Image* directXImage) const noexcept;
			void TexImage2D(INT32 level, const DirectX::Image* directXImage) const noexcept;
		};
	}
}