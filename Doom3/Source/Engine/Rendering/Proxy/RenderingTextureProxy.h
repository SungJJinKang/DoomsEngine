#include <Core.h>

#include "RenderingProxy.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "Rendering/Buffer/BufferID.h"

namespace DirectX
{
	class ScratchImage;
}

namespace dooms
{
	namespace graphics
	{
		class RenderingTextureViewProxy;

		class RenderingTextureProxy : public RenderingProxy
		{
		public:

			virtual ~RenderingTextureProxy();

			struct FRenderingTextureProxyInitializer
			{
				std::unique_ptr<DirectX::ScratchImage> ScratchImage;
				std::vector<const void*> TextureData;
				graphics::GraphicsAPI::eTargetTexture TargetTexture;
				graphics::GraphicsAPI::eTextureBindTarget TextureBindTarget;
				std::vector<UINT32> Width;
				std::vector<UINT32> Height;
				std::vector<UINT32> SrcRowPitch;
				std::vector<UINT32> SrcDepthPitch;
				INT32 MipMapLevelCount;

				/// <summary>
				/// Size in bytes of All Images ( All mipmaps )
				/// </summary>
				size_t EntireImageSize;
				graphics::GraphicsAPI::eTextureComponentFormat ComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )
				graphics::GraphicsAPI::eTextureInternalFormat InternalFormat;
				graphics::GraphicsAPI::eTextureCompressedInternalFormat CompressedInternalFormat;
				graphics::GraphicsAPI::eDataType DataType;
				graphics::GraphicsAPI::eBindFlag BindFlags;
			};

			void InitRenderingTextureProxy(FRenderingTextureProxyInitializer& Initializer);

			void AllocateTextureResourceObject();
			void DestroyTextureResourceObject();


			graphics::GraphicsAPI::eTextureComponentFormat GetTextureComponentFormat() const;
			graphics::GraphicsAPI::eTextureInternalFormat GetTextureInternalFormat() const;
			graphics::GraphicsAPI::eTextureCompressedInternalFormat GetTextureCompressedInternalFormat() const;
			UINT32 GetTextureWidth(const size_t mipLevelIndex = 0) const;
			UINT32 GetTextureHeight(const size_t mipLevelIndex = 0) const;
			UINT32 GetMipMapLevel() const;
			UINT64 GetEntireImageSize() const;
			graphics::GraphicsAPI::eDataType GetTextureDataType() const;
			FORCE_INLINE graphics::GraphicsAPI::eTextureBindTarget GetTextureBindTarget() const
			{
				return TextureBindTarget;
			}

			dooms::graphics::RenderingTextureViewProxy* GenerateTextureView
			(
				const UINT32 DefaultBindingPosition,
				const graphics::GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage
			) const;

			FORCE_INLINE dooms::graphics::BufferID GetTextureResourceObject() const
			{
				return TextureResourceObject;
			}

		private:
			
			dooms::graphics::BufferID TextureResourceObject;

			std::unique_ptr<DirectX::ScratchImage> ScratchImage;
			std::vector<const void*> TextureData;
			graphics::GraphicsAPI::eTargetTexture TargetTexture;
			graphics::GraphicsAPI::eTextureBindTarget TextureBindTarget;
			std::vector<UINT32> Width;
			std::vector<UINT32> Height;
			std::vector<UINT32> SrcRowPitch;
			std::vector<UINT32> SrcDepthPitch;
			INT32 MipMapLevelCount;

			/// <summary>
			/// Size in bytes of All Images ( All mipmaps )
			/// </summary>
			size_t EntireImageSize;
			graphics::GraphicsAPI::eTextureComponentFormat ComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )
			graphics::GraphicsAPI::eTextureInternalFormat InternalFormat;
			graphics::GraphicsAPI::eTextureCompressedInternalFormat CompressedInternalFormat;
			graphics::GraphicsAPI::eDataType DataType;
			graphics::GraphicsAPI::eBindFlag BindFlags;

		};
	}
}