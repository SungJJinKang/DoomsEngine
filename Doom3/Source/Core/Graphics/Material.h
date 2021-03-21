#pragma once
#include <string>
#include <vector>
#include <array>

#include "Graphics_Core.h"
#include "Texture/Texture.h"
#include "OverlapBindChecker.h"
#include "ZeroResetMoveContainer.h"

#include "../Math/LightMath_Cpp/Vector1.h"
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Math/LightMath_Cpp/Vector4.h"

#include "../Math/LightMath_Cpp/Matrix1x1.h"
#include "../Math/LightMath_Cpp/Matrix2x2.h"
#include "../Math/LightMath_Cpp/Matrix3x3.h"
#include "../Math/LightMath_Cpp/Matrix4x4.h"

#include "Asset/ShaderAsset.h"
#include "Asset/TextureAsset.h"

namespace doom
{
	class ShaderAsset;
	class TextureAsset;
	namespace graphics
	{
		enum eUniformLocation : unsigned int
		{
			ModelMatrix = 0
		};
		/// <summary>
		/// Texture binding point
		/// Bindin != location
		/// </summary>
		enum eTextureBindingPoint : unsigned int
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
		class Material
		{

		private:
			static inline constexpr const char* MATERIAL_TAG = "Material";

			BufferID mProgramID;
			::doom::asset::ShaderAsset* mShaderAsset;
			static constexpr inline unsigned int MAX_TEXTURE_COUNT{ 7 };
			std::array<Texture*, MAX_TEXTURE_COUNT> mTargetTextures{ nullptr };
			std::array<UniformBufferObject*, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects{ nullptr };

	
			
		public:
			Material();
			Material(::doom::asset::ShaderAsset* shaderAsset);
			~Material();

			Material(const Material&) = delete;
			Material& operator=(const Material&) noexcept = delete;

			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;

			bool IsGenerated();
			void SetShaderAsset(::doom::asset::ShaderAsset* shaderAsset);

			void AddTexture(unsigned int bindingPoint, Texture* texture);
			void AddTexture(unsigned int bindingPoint, ::doom::asset::TextureAsset* textureAsset);
			void AddTextures(std::array<Texture*, MAX_TEXTURE_COUNT> textures);

			void UseProgram()
			{
				D_ASSERT(this->mProgramID != 0);

				if (OverlapBindChecker::GetBoundID(MATERIAL_TAG) != this->mProgramID)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(MATERIAL_TAG, this->mProgramID);
					for (unsigned int i = 0; i < this->mTargetTextures.size(); i++)
					{
						if (this->mTargetTextures[i] != nullptr)
						{
							this->mTargetTextures[i]->BindTextureWithUnit(i);
						}
					}
					glUseProgram(this->mProgramID);
				}
			}

			[[nodiscard]] int GetUniformLocation(const char* str) noexcept
			{
				return glGetUniformLocation(this->mProgramID, str);
			}

			void SetBool(int location, bool value1)
			{
				glUniform1i(location, static_cast<int>(value1));
			}
			void SetBool(const char* str, bool value1)
			{
				glUniform1i(GetUniformLocation(str), static_cast<int>(value1));
			}

			void SetBool(int location, bool value1, bool value2)
			{
				glUniform2i(location, static_cast<int>(value1), static_cast<int>(value2));
			}
			void SetBool(const char* str, bool value1, bool value2)
			{
				glUniform2i(GetUniformLocation(str), static_cast<int>(value1), static_cast<int>(value2));
			}

			void SetBool(int location, bool value1, bool value2, bool value3)
			{
				glUniform3i(location, static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3));
			}
			void SetBool(const char* str, bool value1, bool value2, bool value3)
			{
				glUniform3i(GetUniformLocation(str), static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3));
			}

			void SetBool(int location, bool value1, bool value2, bool value3, bool value4)
			{
				glUniform4i(location, static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3), static_cast<int>(value4));
			}
			void SetBool(const char* str, bool value1, bool value2, bool value3, bool value4)
			{
				glUniform4i(GetUniformLocation(str), static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3), static_cast<int>(value4));
			}

			void SetInt(int location, int value1)
			{
				glUniform1i(location, value1);
			}
			void SetInt(const char* str, int value1)
			{
				glUniform1i(GetUniformLocation(str), value1);
			}

			void SetInt(int location, int value1, int value2)
			{
				glUniform2i(location, value1, value2);
			}
			void SetInt(const char* str, int value1, int value2)
			{
				glUniform2i(GetUniformLocation(str), value1, value2);
			}

			void SetInt(int location, int value1, int value2, int value3)
			{
				glUniform3i(location, value1, value2, value3);
			}
			void SetInt(const char* str, int value1, int value2, int value3)
			{
				glUniform3i(GetUniformLocation(str), value1, value2, value3);
			}

			void SetInt(int location, int value1, int value2, int value3, int value4)
			{
				glUniform4i(location, value1, value2, value3, value4);
			}
			void SetInt(const char* str, int value1, int value2, int value3, int value4)
			{
				glUniform4i(GetUniformLocation(str), value1, value2, value3, value4);
			}

			void SetFloat(int location, float value1)
			{
				glUniform1f(location, value1);
			}
			void SetFloat(const char* str, float value1)
			{
				glUniform1f(GetUniformLocation(str), value1);
			}

			void SetFloat(int location, float value1, float value2)
			{
				glUniform2f(location, value1, value2);
			}
			void SetFloat(const char* str, float value1, float value2)
			{
				glUniform2f(GetUniformLocation(str), value1, value2);
			}

			void SetFloat(int location, float value1, float value2, float value3)
			{
				glUniform3f(location, value1, value2, value3);
			}
			void SetFloat(const char* str, float value1, float value2, float value3)
			{
				glUniform3f(GetUniformLocation(str), value1, value2, value3);
			}

			void SetFloat(int location, float value1, float value2, float value3, float value4)
			{
				glUniform4f(location, value1, value2, value3, value4);
			}
			void SetFloat(const char* str, float value1, float value2, float value3, float value4)
			{
				glUniform4f(GetUniformLocation(str), value1, value2, value3, value4);
			}

			void SetMatrix1x1(int location, const math::Matrix1x1& matrix1x1)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, matrix1x1.data());
			}
			void SetMatrix1x1(const char* str, const math::Matrix1x1& matrix1x1)
			{
				glUniformMatrix4fv(GetUniformLocation(str), 1, GL_FALSE, matrix1x1.data());
			}

			void SetMatrix2x2(int location, const math::Matrix2x2& matrix2x2)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, matrix2x2.data());
			}
			void SetMatrix2x2(const char* str, const math::Matrix2x2& matrix2x2)
			{
				glUniformMatrix4fv(GetUniformLocation(str), 1, GL_FALSE, matrix2x2.data());
			}

			void SetMatrix3x3(int location, const math::Matrix3x3& matrix3x3)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, matrix3x3.data());
			}
			void SetMatrix3x3(const char* str, const math::Matrix3x3& matrix3x3)
			{
				glUniformMatrix4fv(GetUniformLocation(str), 1, GL_FALSE, matrix3x3.data());
			}

			void SetMatrix4x4(int location, const math::Matrix4x4& matrix4x4)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, matrix4x4.data());
			}
			void SetMatrix4x4(const char* str, const math::Matrix4x4& matrix4x4)
			{
				glUniformMatrix4fv(GetUniformLocation(str), 1, GL_FALSE, matrix4x4.data());
			}


			void SetVector1(int location, const math::Vector1& vector1)
			{
				glUniform1f(location, vector1.x);
			}
			void SetVector1(const char* str, const math::Vector1& vector1)
			{
				glUniform1f(GetUniformLocation(str), vector1.x);
			}

			void SetVector2(int location, const math::Vector2& vector2)
			{
				glUniform2f(location, vector2.x, vector2.y);
			}
			void SetVector2(const char* str, const math::Vector2& vector2)
			{
				glUniform2f(GetUniformLocation(str), vector2.x, vector2.y);
			}

			void SetVector3(int location, const math::Vector3& vector3)
			{
				glUniform3f(location, vector3.x, vector3.y, vector3.z);
			}
			void SetVector3(const char* str, const math::Vector3& vector3)
			{
				glUniform3f(GetUniformLocation(str), vector3.x, vector3.y, vector3.z);
			}

			void SetVector4(int location, const math::Vector4& vector4)
			{
				glUniform4f(location, vector4.x, vector4.y, vector4.z, vector4.w);
			}
			void SetVector4(const char* str, const math::Vector4& vector4)
			{
				glUniform4f(GetUniformLocation(str), vector4.x, vector4.y, vector4.z, vector4.w);
			}


			/*	you don't need this function ( from opengl 4.2 and onwards, you can set binding point explicitly like "binding = 1" )
			///
			/// <summary>
			/// Set UniformBlock to specific binding point
			/// if you write shader like this : layout (std140, binding = 0), 
			/// </summary>
			/// <param name="uniformBlockName"></param>
			/// <param name="bindingPoint"></param>
			void SetUniformBlockPoint(const std::string uniformBlockName, unsigned int bindingPoint);
			*/

			/// <summary>
			/// return Uniform Block Count
			/// do iterate from 0 to return value
			/// </summary>
			/// <returns>0 ~ return value</returns>
			int GetUniformBlocksCount();
			void InitUniformBufferObject();
		};
	}
}

