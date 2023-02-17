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


			void SetBool1(const UINT64 offset, const bool value1);
			void SetBool1(const char* const str, const bool value1);
			void SetBool2(const UINT64 offset, const bool* const values);
			void SetBool2(const char* const str, const bool* const values);
			void SetBool3(const UINT64 offset, const bool* const values);
			void SetBool3(const char* const str, const bool* const values);
			void SetBool4(const UINT64 offset, const bool* const values);
			void SetBool4(const char* const str, const bool* const values);
			void SetInt1(const UINT64 offset, const INT32 value1);
			void SetInt1(const char* const str, const INT32 value1);
			void SetInt2(const UINT64 offset, const INT32* const values);
			void SetInt2(const char* const str, const INT32* const values);
			void SetInt3(const UINT64 offset, const INT32* const values);
			void SetInt3(const char* const str, const INT32* const values);
			void SetInt4(const UINT64 offset, const INT32* const values);
			void SetInt4(const char* const str, const INT32* const values);
			void SetFloat1(const UINT64 offset, const float value1);
			void SetFloat1(const char* const str, const float value1);
			void SetFloat2(const UINT64 offset, const float* const values);
			void SetFloat2(const char* const str, const float* const values);
			void SetFloat3(const UINT64 offset, const float* const values);
			void SetFloat3(const char* const str, const float* const values);
			void SetFloat4(const UINT64 offset, const float* const values);
			void SetFloat4(const char* const str, const float* const values);
			void SetMat3x3(const UINT64 offset, const math::Matrix3x3& value);
			void SetMat3x3(const char* const str, const math::Matrix3x3& value);
			void SetMat4x4(const UINT64 offset, const math::Matrix4x4& value);
			void SetMat4x4(const char* const str, const math::Matrix4x4& value);
			void SetVector2(const UINT64 offset, const math::Vector2& vector2);
			void SetVector2(const char* const str, const math::Vector2& vector2);
			void SetVector3(const UINT64 offset, const math::Vector3& vector3);
			void SetVector3(const char* const str, const math::Vector3& vector3);
			void SetVector4(const UINT64 offset, const math::Vector4& vector4);
			void SetVector4(const char* const str, const math::Vector4& vector4);
		};
	}
}
