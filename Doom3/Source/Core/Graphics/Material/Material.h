#pragma once
#include <array>

#include "../Graphics_Core.h"
#include "../GraphicsAPI/GraphicsAPI.h"

#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Math/LightMath_Cpp/Vector4.h"

#include "../Math/LightMath_Cpp/Matrix2x2.h"
#include "../Math/LightMath_Cpp/Matrix3x3.h"
#include "../Math/LightMath_Cpp/Matrix4x4.h"

#include "../Buffer/BufferID.h"

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
		class Texture;

		class DOOM_API D_CLASS Material : public DObject
		{
			GENERATE_BODY()
			

		private:
			static inline const char MATERIAL_TAG[]{ "MATERIAL" };

			BufferID mProgramID;
			::dooms::asset::ShaderAsset* mShaderAsset;
			static constexpr inline UINT32 MAX_TEXTURE_COUNT{ 7 };
			std::array<const Texture*, MAX_TEXTURE_COUNT> mTargetTextures{ nullptr };
			std::array<UniformBufferObject*, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects{ nullptr };
			
			void DestroyMaterialBufferObject();

		public:

			Material();
			Material(::dooms::asset::ShaderAsset* shaderAsset);
			
			virtual ~Material();

			Material(const Material&) = delete;
			Material& operator=(const Material&) noexcept = delete;

			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;

			bool IsGenerated() const;
			void SetShaderAsset(::dooms::asset::ShaderAsset* shaderAsset);

			void AddTexture(UINT32 bindingPoint, Texture* texture);
			void AddTexture(UINT32 bindingPoint, ::dooms::asset::TextureAsset* textureAsset);
			void AddTextures(const std::array<const Texture*, MAX_TEXTURE_COUNT>& textures);

			void UseProgram() const;

			INT32 GetUniformLocation(const char* str) const;

			FORCE_INLINE static void SetBool(const INT32 location, const bool value1)
			{
				GraphicsAPI::UpdateConstantBuffer_bool1(location, value1);
			}
			FORCE_INLINE void SetBool(const char* str, const bool value1) const
			{
				GraphicsAPI::UpdateConstantBuffer_bool1(GetUniformLocation(str), value1);
			}

			FORCE_INLINE static void SetBool(const INT32 location, const bool value1, const bool value2)
			{
				GraphicsAPI::UpdateConstantBuffer_bool2(location, value1, value2);
			}
			FORCE_INLINE void SetBool(const char* str, const bool value1, const bool value2) const
			{
				GraphicsAPI::UpdateConstantBuffer_bool2(GetUniformLocation(str), value1, value2);
			}

			FORCE_INLINE static void SetBool(const INT32 location, const bool value1, const bool value2, const bool value3)
			{
				GraphicsAPI::UpdateConstantBuffer_bool3(location, value1, value2, value3);
			}
			FORCE_INLINE void SetBool(const char* str, const bool value1, const bool value2, const bool value3) const
			{
				GraphicsAPI::UpdateConstantBuffer_bool3(GetUniformLocation(str), value1, value2, value3);
			}

			FORCE_INLINE static void SetBool(const INT32 location, const bool value1, const bool value2, const bool value3, const bool value4)
			{
				GraphicsAPI::UpdateConstantBuffer_bool4(location, value1, value2, value3, value4);
			}
			FORCE_INLINE void SetBool(const char* str, const bool value1, const bool value2, const bool value3, const bool value4) const
			{
				GraphicsAPI::UpdateConstantBuffer_bool4(GetUniformLocation(str), value1, value2, value3, value4);
			}

			FORCE_INLINE static void SetInt(const INT32 location, const INT32 value1)
			{
				GraphicsAPI::UpdateConstantBuffer_int1(location, value1);
			}
			FORCE_INLINE void SetInt(const char* str, const INT32 value1) const
			{
				GraphicsAPI::UpdateConstantBuffer_int1(GetUniformLocation(str), value1);
			}

			FORCE_INLINE static void SetInt(const INT32 location, const INT32 value1, const INT32 value2)
			{
				GraphicsAPI::UpdateConstantBuffer_int2(location, value1, value2);
			}
			FORCE_INLINE void SetInt(const char* str, const INT32 value1, const INT32 value2) const
			{
				GraphicsAPI::UpdateConstantBuffer_int2(GetUniformLocation(str), value1, value2);
			}

			FORCE_INLINE static void SetInt(const INT32 location, const INT32 value1, const INT32 value2, const INT32 value3)
			{
				GraphicsAPI::UpdateConstantBuffer_int3(location, value1, value2, value3);
			}
			FORCE_INLINE void SetInt(const char* str, const INT32 value1, const INT32 value2, const INT32 value3) const
			{
				GraphicsAPI::UpdateConstantBuffer_int3(GetUniformLocation(str), value1, value2, value3);
			}

			FORCE_INLINE static void SetInt(const INT32 location, const INT32 value1, const INT32 value2, const INT32 value3, const INT32 value4)
			{
				GraphicsAPI::UpdateConstantBuffer_int4(location, value1, value2, value3, value4);
			}
			FORCE_INLINE void SetInt(const char* str, const INT32 value1, const INT32 value2, INT32 value3, const INT32 value4) const
			{
				GraphicsAPI::UpdateConstantBuffer_int4(GetUniformLocation(str), value1, value2, value3, value4);
			}

			FORCE_INLINE static void SetFloat(const INT32 location, const FLOAT32 value1)
			{
				GraphicsAPI::UpdateConstantBuffer_float1(location, value1);
			}
			FORCE_INLINE void SetFloat(const char* str, const FLOAT32 value1) const
			{
				GraphicsAPI::UpdateConstantBuffer_float1(GetUniformLocation(str), value1);
			}

			FORCE_INLINE static void SetFloat(const INT32 location, const FLOAT32 value1, const FLOAT32 value2)
			{
				GraphicsAPI::UpdateConstantBuffer_float2(location, value1, value2);
			}
			FORCE_INLINE void SetFloat(const char* str, const FLOAT32 value1, const FLOAT32 value2) const
			{
				GraphicsAPI::UpdateConstantBuffer_float2(GetUniformLocation(str), value1, value2);
			}

			FORCE_INLINE static void SetFloat(const INT32 location, const FLOAT32 value1, const FLOAT32 value2, const FLOAT32 value3)
			{
				GraphicsAPI::UpdateConstantBuffer_float3(location, value1, value2, value3);
			}
			FORCE_INLINE void SetFloat(const char* str, const FLOAT32 value1, const FLOAT32 value2, const FLOAT32 value3) const
			{
				GraphicsAPI::UpdateConstantBuffer_float3(GetUniformLocation(str), value1, value2, value3);
			}

			FORCE_INLINE static void SetFloat(const INT32 location, const FLOAT32 value1, const FLOAT32 value2, const FLOAT32 value3, const FLOAT32 value4)
			{
				GraphicsAPI::UpdateConstantBuffer_float4(location, value1, value2, value3, value4);
			}
			FORCE_INLINE void SetFloat(const char* str, const FLOAT32 value1, const FLOAT32 value2, const FLOAT32 value3, const FLOAT32 value4) const
			{
				GraphicsAPI::UpdateConstantBuffer_float4(GetUniformLocation(str), value1, value2, value3, value4);
			}
			
			FORCE_INLINE static void SetMatrix2x2(const INT32 location, const math::Matrix2x2& matrix2x2)
			{
				GraphicsAPI::UpdateConstantBuffer_mat2x2f(location, matrix2x2.data());
			}
			FORCE_INLINE void SetMatrix2x2(const char* str, const math::Matrix2x2& matrix2x2) const
			{
				GraphicsAPI::UpdateConstantBuffer_mat2x2f(GetUniformLocation(str), matrix2x2.data());
			}

			FORCE_INLINE static void SetMatrix3x3(const INT32 location, const math::Matrix3x3& matrix3x3)
			{
				GraphicsAPI::UpdateConstantBuffer_mat3x3f(location, matrix3x3.data());
			}
			FORCE_INLINE void SetMatrix3x3(const char* str, const math::Matrix3x3& matrix3x3) const
			{
				GraphicsAPI::UpdateConstantBuffer_mat3x3f(GetUniformLocation(str), matrix3x3.data());
			}

			FORCE_INLINE static void SetMatrix4x4(const INT32 location, const math::Matrix4x4& matrix4x4)
			{
				GraphicsAPI::UpdateConstantBuffer_mat4x4f(location, matrix4x4.data());
			}
			FORCE_INLINE void SetMatrix4x4(const char* str, const math::Matrix4x4& matrix4x4) const
			{
				GraphicsAPI::UpdateConstantBuffer_mat4x4f(GetUniformLocation(str), matrix4x4.data());
			}


			FORCE_INLINE static void SetVector1(const INT32 location, const float vector1)
			{
				GraphicsAPI::UpdateConstantBuffer_float1(location, vector1);
			}
			FORCE_INLINE void SetVector1(const char* str, const float vector1) const
			{
				GraphicsAPI::UpdateConstantBuffer_float1(GetUniformLocation(str), vector1);
			}

			FORCE_INLINE static void SetVector2(const INT32 location, const math::Vector2& vector2)
			{
				GraphicsAPI::UpdateConstantBuffer_float2(location, vector2.x, vector2.y);
			}
			FORCE_INLINE void SetVector2(const char* str, const math::Vector2& vector2) const
			{
				GraphicsAPI::UpdateConstantBuffer_float2(GetUniformLocation(str), vector2.x, vector2.y);
			}

			FORCE_INLINE static void SetVector3(const INT32 location, const math::Vector3& vector3)
			{
				GraphicsAPI::UpdateConstantBuffer_float3(location, vector3.x, vector3.y, vector3.z);
			}
			FORCE_INLINE void SetVector3(const char* str, const math::Vector3& vector3) const
			{
				GraphicsAPI::UpdateConstantBuffer_float3(GetUniformLocation(str), vector3.x, vector3.y, vector3.z);
			}

			FORCE_INLINE static void SetVector4(const INT32 location, const math::Vector4& vector4)
			{
				GraphicsAPI::UpdateConstantBuffer_float4(location, vector4.x, vector4.y, vector4.z, vector4.w);
			}
			FORCE_INLINE void SetVector4(const char* str, const math::Vector4& vector4) const
			{
				GraphicsAPI::UpdateConstantBuffer_float4(GetUniformLocation(str), vector4.x, vector4.y, vector4.z, vector4.w);
			}


			/*	you don't need this function ( from opengl 4.2 and onwards, you can set binding point explicitly like "binding = 1" )
			///
			/// <summary>
			/// Set UniformBlock to specific binding point
			/// if you write shader like this : layout (std140, binding = 0), 
			/// </summary>
			/// <param name="uniformBlockName"></param>
			/// <param name="bindingPoint"></param>
			void SetUniformBlockPoint(const std::string uniformBlockName, UINT32 bindingPoint);
			*/

			/// <summary>
			/// return Uniform Block Count
			/// do iterate from 0 to return value
			/// </summary>
			/// <returns>0 ~ return value</returns>
			INT32 GetUniformBlocksCount() const;
			void InitUniformBufferObject();
		};
	}
}

