#pragma once

#include <Core.h>

#include <string>
#include <unordered_map>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "UniformBufferObject.h"
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix2x2.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>

#include "UniformBufferObjectView.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class UniformBufferObject;
		class Material;

		class DOOM_API D_CLASS  UniformBufferObjectView : public DObject
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			Material* mTargetMaterial;

			D_PROPERTY()
			UniformBufferObject* mTargetUniformBufferObject;

			D_PROPERTY()
			UINT32 mDefaultBindingPoint;
			D_PROPERTY()
			GraphicsAPI::eGraphicsPipeLineStage mDefaultTargetPipeLineStage;

		public:


			UniformBufferObjectView
			(
				Material* const targetMaterial,
				UniformBufferObject* const targetUBO,
				const UINT32 defaultBindingPoint,
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
			);


			UniformBufferObjectView(const UniformBufferObjectView&) = default;
			UniformBufferObjectView(UniformBufferObjectView&&) noexcept = default;
			UniformBufferObjectView& operator=(const UniformBufferObjectView&) = default;
			UniformBufferObjectView& operator=(UniformBufferObjectView&&) noexcept = default;
			
			void BindUniformBufferObject() const noexcept;
			void BindUniformBufferObject(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept;
			void UnBindUniformBufferObject() const noexcept;

			Material* GetTargetMaterial() const;
			FORCE_INLINE UniformBufferObject* GetTargetUniformBufferObject() const
			{
				return mTargetUniformBufferObject;
			}


			FORCE_INLINE void SetBool1(const UINT64 offset, const bool value1)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, offset, sizeof(bool));
			}

			FORCE_INLINE void SetBool1(const char* const str, const bool value1)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool));
			}

			FORCE_INLINE void SetBool2(const UINT64 offset, const bool* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(bool) * 2);
			}
			FORCE_INLINE void SetBool2(const char* const str, const bool* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool) * 2);
			}

			FORCE_INLINE void SetBool3(const UINT64 offset, const bool* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(bool) * 3);
			}
			FORCE_INLINE void SetBool3(const char* const str, const bool* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool) * 3);
			}

			FORCE_INLINE void SetBool4(const UINT64 offset, const bool* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(bool) * 4);
			}
			FORCE_INLINE void SetBool4(const char* const str, const bool* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool) * 4);
			}

			FORCE_INLINE void SetInt1(const UINT64 offset, const INT32 value1)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, offset, sizeof(INT32) * 1);
			}
			FORCE_INLINE void SetInt1(const char* const str, const INT32 value1)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 1);
			}

			FORCE_INLINE void SetInt2(const UINT64 offset, const INT32* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(INT32) * 2);
			}
			FORCE_INLINE void SetInt2(const char* const str, const INT32* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 2);
			}

			FORCE_INLINE void SetInt3(const UINT64 offset, const INT32* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(INT32) * 3);
			}
			FORCE_INLINE void SetInt3(const char* const str, const INT32* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 3);
			}

			FORCE_INLINE void SetInt4(const UINT64 offset, const INT32* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(INT32) * 4);
			}
			FORCE_INLINE void SetInt4(const char* const str, const INT32* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 4);
			}

			FORCE_INLINE void SetFloat1(const UINT64 offset, const float value1)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, offset, sizeof(float) * 1);
			}
			FORCE_INLINE void SetFloat1(const char* const str, const float value1)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 1);
			}

			FORCE_INLINE void SetFloat2(const UINT64 offset, const float* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(float) * 2);
			}
			FORCE_INLINE void SetFloat2(const char* const str, const float* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 2);
			}

			FORCE_INLINE void SetFloat3(const UINT64 offset, const float* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(float) * 3);
			}
			FORCE_INLINE void SetFloat3(const char* const str, const float* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 3);
			}

			FORCE_INLINE void SetFloat4(const UINT64 offset, const float* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(float) * 4);
			}
			FORCE_INLINE void SetFloat4(const char* const str, const float* const values)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 4);
			}

			FORCE_INLINE void SetMat3x3(const UINT64 offset, const math::Matrix3x3& value)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), offset, sizeof(math::Matrix3x3));
			}
			FORCE_INLINE void SetMat3x3(const char* const str, const math::Matrix3x3& value)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Matrix3x3));
			}

			FORCE_INLINE void SetMat4x4(const UINT64 offset, const math::Matrix4x4& value)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), offset, sizeof(math::Matrix4x4));
			}
			FORCE_INLINE void SetMat4x4(const char* const str, const math::Matrix4x4& value)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Matrix4x4));
			}

			FORCE_INLINE void SetVector2(const UINT64 offset, const math::Vector2& vector2)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(vector2.data(), offset, sizeof(math::Vector2));
			}
			FORCE_INLINE void SetVector2(const char* const str, const math::Vector2& vector2)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(vector2.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Vector2));
			}

			FORCE_INLINE void SetVector3(const UINT64 offset, const math::Vector3& vector3)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(vector3.data(), offset, sizeof(math::Vector3));
			}
			FORCE_INLINE void SetVector3(const char* const str, const math::Vector3& vector3)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(vector3.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Vector3));
			}

			FORCE_INLINE void SetVector4(const UINT64 offset, const math::Vector4& vector4)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(vector4.data(), offset, sizeof(math::Vector4));
			}
			FORCE_INLINE void SetVector4(const char* const str, const math::Vector4& vector4)
			{
				GetTargetUniformBufferObject()->UpdateDataToGPU(vector4.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Vector4));
			}

		};

	}
}
