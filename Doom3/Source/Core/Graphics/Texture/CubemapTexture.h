#pragma once
#include "Texture.h"

#include "CubemapTexture.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS CubemapTexture : public Texture
		{
			GENERATE_BODY()
			

		public:

			CubemapTexture();
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data);
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data);
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data);
			CubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data);

			
			virtual ~CubemapTexture() = default;
			CubemapTexture(const CubemapTexture&) = delete;
			CubemapTexture& operator=(const CubemapTexture&) noexcept = delete;

			CubemapTexture(CubemapTexture&&) noexcept = default;
			CubemapTexture& operator=(CubemapTexture&&) noexcept = default;


			void TexImage1D(INT32 level, const void* data) const noexcept override;

			void TexImage1D(INT32 face, INT32 level, const void* data) const noexcept;


			void TexImage2D(INT32 level, const void* data) const noexcept override;

			void TexImage2D(INT32 face, INT32 level, const void* data) const noexcept;


			void InitializeCubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data);
			void InitializeCubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data);
			void InitializeCubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data);
			void InitializeCubemapTexture(eTextureType textureType,
				eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data);



		};
	}
}