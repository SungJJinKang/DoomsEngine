#pragma once
#include <array>

#include "../Graphics_Core.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Math/LightMath_Cpp/Vector4.h"

#include "../Math/LightMath_Cpp/Matrix2x2.h"
#include "../Math/LightMath_Cpp/Matrix3x3.h"
#include "../Math/LightMath_Cpp/Matrix4x4.h"

#include "../Buffer/BufferID.h"
#include "../Buffer/UniformBufferObject/UniformBufferObjectView.h"

#include <eStatus.h>

#include "Material.reflection.h"
namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
		class TextureAsset;
	}
	
	namespace graphics
	{
		enum D_ENUM eUniformLocation : UINT32
		{
			ModelMatrix = 0
		};
		/// <summary>
		/// Texture binding point
		/// Bindin != location
		/// </summary>
		enum D_ENUM eTextureBindingPoint : UINT32
		{
			AlbedoTexture = 0,
			NormalTexture = 1,
			MetalnessTexture = 2,
			RoughnessTexture = 3,
			SpecularTexture = 4,
			IrradianceTexture = 5,
			SpecularBRDF_LUT = 6
		};

		class UniformBufferObject;
		class TextureView;

		class DOOM_API D_CLASS Material : public DObject
		{
			GENERATE_BODY()
			
			
		private:

			static inline const char MATERIAL_TAG[]{ "MATERIAL" };

			eStatus mMaterialStatus;

			/// <summary>
			/// Used for OpenGL
			///	If Current Graphics API is DirectX, this varaible set to random uuid ( this is for overlap check )
			/// </summary>
			D_PROPERTY()
			BufferID mProgramIDForOpenGL;

			/// <summary>
			/// Used for DirectX
			/// </summary>
			D_PROPERTY()
			std::array<BufferID, GRAPHICS_PIPELINE_STAGE_COUNT> mPipeLineShaderObject;


			D_PROPERTY()
			dooms::asset::ShaderAsset* mShaderAsset;

			D_PROPERTY()
			std::vector<const TextureView*> mTargetTextures{ nullptr };

			D_PROPERTY()
			std::vector<UniformBufferObjectView> mTargetUniformBufferObjectViews;

			bool CreateMeterialObject();
			void OnSetPendingKill() override;
			
		public:

			Material();
			Material(dooms::asset::ShaderAsset* const shaderAsset);
			void DestroyMaterialObjectIfExist();

			virtual ~Material();

			Material(const Material&) = delete;
			Material& operator=(const Material&) noexcept = delete;

			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;
			
			void SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset);
			bool IsHasAnyValidShaderObject() const;

			void AddTexture(UINT32 bindingPoint, TextureView* texture);
			void AddTexture(const UINT32 bindingPoint, const dooms::asset::TextureAsset* const textureAsset);
			void AddTextures(const std::vector<const TextureView*>& textures);

			void UseProgram() const;

			bool IsMaterialCreated() const;

			FORCE_INLINE dooms::asset::ShaderAsset* GetShaderAsset()
			{
				return mShaderAsset;
			}

			FORCE_INLINE const dooms::asset::ShaderAsset* GetShaderAsset() const
			{
				return mShaderAsset;
			}
			
			FORCE_INLINE UniformBufferObjectView* GetUniformBufferObjectViewFromUBOIndex(const size_t uboIndex)
			{
				UniformBufferObjectView* uboView = nullptr;
				D_ASSERT(uboIndex < mTargetUniformBufferObjectViews.size());

				if(uboIndex < mTargetUniformBufferObjectViews.size())
				{
					uboView = mTargetUniformBufferObjectViews.data() + uboIndex;
				}

				return uboView;
			}
			UniformBufferObjectView* GetUniformBufferObjectViewFromUBOName(const char* const uniformBufferObjectName);
		};
	}
}

