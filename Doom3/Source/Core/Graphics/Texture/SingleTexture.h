#pragma once

#include "Texture.h"

#include "SingleTexture.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS SingleTexture : public Texture
		{
			GENERATE_BODY()
			

		private:

			void AllocateMemoryFor1DTexture(const unsigned int lodCount, const int width);
			void AllocateMemoryFor2DTexture(const unsigned int lodCount, const int width, const int height);

		public:

			SingleTexture();
			virtual ~SingleTexture() = default;
			SingleTexture(const SingleTexture&) = delete;
			SingleTexture& operator=(const SingleTexture&) noexcept = delete;

			SingleTexture(SingleTexture&&) noexcept = default;
			SingleTexture& operator=(SingleTexture&&) noexcept = default;

			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);
			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);

			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			
			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);
			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);

			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
		
			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);
			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);

			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);
			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data);


			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);


			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);
			void InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType,
				dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas);


			void Tex2DMipMapImages(std::vector<const DirectX::Image*> mipmapDatas);
			virtual void TexImage1D(INT32 level, const void* data) const noexcept final;
			virtual void TexImage2D(INT32 level, const void* data) const noexcept final;
			void TexImage1D(INT32 level, const DirectX::Image* directXImage) const noexcept;
			void TexImage2D(INT32 level, const DirectX::Image* directXImage) const noexcept;

			
		};
	}
}