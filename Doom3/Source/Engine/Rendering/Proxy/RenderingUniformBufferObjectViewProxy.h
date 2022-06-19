#pragma once

#include <Core.h>

#include <string>
#include <unordered_map>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Rendering/Proxy/RenderingProxy.h>
#include <Rendering/Proxy/RenderingUniformBufferProxy.h>

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>

namespace dooms
{
	namespace graphics
	{
		class UniformBufferObject;
		class Material;
		class RenderingUniformBufferProxy;
		class RenderingMaterialProxy;

		class DOOM_API RenderingUniformBufferObjectViewProxy : public RenderingProxy
		{
		private:
			
			RenderingMaterialProxy* TargetMaterialProxy;
			RenderingUniformBufferProxy* TargetUniformBufferProxy;
			UINT32 DefaultBindingPoint;
			GraphicsAPI::eGraphicsPipeLineStage DefaultTargetPipeLineStage;

		public:

			struct FRenderingUniformBufferObjectViewProxyInitializer
			{
				RenderingMaterialProxy* TargetMaterialProxy;
				RenderingUniformBufferProxy* TargetUniformBufferProxy;
				UINT32 DefaultBindingPoint;
				GraphicsAPI::eGraphicsPipeLineStage DefaultTargetPipeLineStage;
			};

			void InitRenderingUniformBufferObjectViewProxy(FRenderingUniformBufferObjectViewProxyInitializer& Initializer);
			
			void BindUniformBufferObject() const noexcept;
			void BindUniformBufferObject(const UINT32 BindingPoint, const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage) const noexcept;
			void UnBindUniformBufferObject() const noexcept;

			RenderingMaterialProxy* GetTargetMaterialProxy() const;
			FORCE_INLINE RenderingUniformBufferProxy* GetTargetUniformBufferProxy() const
			{
				return TargetUniformBufferProxy;
			}


			FORCE_INLINE void SetBool1(const UINT64 offset, const bool value1)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(&value1, offset, sizeof(bool));
			}

			FORCE_INLINE void SetBool1(const char* const str, const bool value1)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(&value1, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(bool));
			}

			FORCE_INLINE void SetBool2(const UINT64 offset, const bool* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(bool) * 2);
			}
			FORCE_INLINE void SetBool2(const char* const str, const bool* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(bool) * 2);
			}

			FORCE_INLINE void SetBool3(const UINT64 offset, const bool* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(bool) * 3);
			}
			FORCE_INLINE void SetBool3(const char* const str, const bool* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(bool) * 3);
			}

			FORCE_INLINE void SetBool4(const UINT64 offset, const bool* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(bool) * 4);
			}
			FORCE_INLINE void SetBool4(const char* const str, const bool* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(bool) * 4);
			}

			FORCE_INLINE void SetInt1(const UINT64 offset, const INT32 value1)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(&value1, offset, sizeof(INT32) * 1);
			}
			FORCE_INLINE void SetInt1(const char* const str, const INT32 value1)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(&value1, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(INT32) * 1);
			}

			FORCE_INLINE void SetInt2(const UINT64 offset, const INT32* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(INT32) * 2);
			}
			FORCE_INLINE void SetInt2(const char* const str, const INT32* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(INT32) * 2);
			}

			FORCE_INLINE void SetInt3(const UINT64 offset, const INT32* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(INT32) * 3);
			}
			FORCE_INLINE void SetInt3(const char* const str, const INT32* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(INT32) * 3);
			}

			FORCE_INLINE void SetInt4(const UINT64 offset, const INT32* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(INT32) * 4);
			}
			FORCE_INLINE void SetInt4(const char* const str, const INT32* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(INT32) * 4);
			}

			FORCE_INLINE void SetFloat1(const UINT64 offset, const float value1)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(&value1, offset, sizeof(float) * 1);
			}
			FORCE_INLINE void SetFloat1(const char* const str, const float value1)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(&value1, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(float) * 1);
			}

			FORCE_INLINE void SetFloat2(const UINT64 offset, const float* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(float) * 2);
			}
			FORCE_INLINE void SetFloat2(const char* const str, const float* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(float) * 2);
			}

			FORCE_INLINE void SetFloat3(const UINT64 offset, const float* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(float) * 3);
			}
			FORCE_INLINE void SetFloat3(const char* const str, const float* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(float) * 3);
			}

			FORCE_INLINE void SetFloat4(const UINT64 offset, const float* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, offset, sizeof(float) * 4);
			}
			FORCE_INLINE void SetFloat4(const char* const str, const float* const values)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(values, GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(float) * 4);
			}

			FORCE_INLINE void SetMat3x3(const UINT64 offset, const math::Matrix3x3& value)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(value.data(), offset, sizeof(math::Matrix3x3));
			}
			FORCE_INLINE void SetMat3x3(const char* const str, const math::Matrix3x3& value)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(value.data(), GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(math::Matrix3x3));
			}

			FORCE_INLINE void SetMat4x4(const UINT64 offset, const math::Matrix4x4& value)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(value.data(), offset, sizeof(math::Matrix4x4));
			}
			FORCE_INLINE void SetMat4x4(const char* const str, const math::Matrix4x4& value)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(value.data(), GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(math::Matrix4x4));
			}

			FORCE_INLINE void SetVector2(const UINT64 offset, const math::Vector2& vector2)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(vector2.data(), offset, sizeof(math::Vector2));
			}
			FORCE_INLINE void SetVector2(const char* const str, const math::Vector2& vector2)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(vector2.data(), GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(math::Vector2));
			}

			FORCE_INLINE void SetVector3(const UINT64 offset, const math::Vector3& vector3)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(vector3.data(), offset, sizeof(math::Vector3));
			}
			FORCE_INLINE void SetVector3(const char* const str, const math::Vector3& vector3)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(vector3.data(), GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(math::Vector3));
			}

			FORCE_INLINE void SetVector4(const UINT64 offset, const math::Vector4& vector4)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(vector4.data(), offset, sizeof(math::Vector4));
			}
			FORCE_INLINE void SetVector4(const char* const str, const math::Vector4& vector4)
			{
				GetTargetUniformBufferProxy()->UpdateDataToGPU(vector4.data(), GetTargetUniformBufferProxy()->GetUniformVariableOffset(str), sizeof(math::Vector4));
			}

		};

	}
}
