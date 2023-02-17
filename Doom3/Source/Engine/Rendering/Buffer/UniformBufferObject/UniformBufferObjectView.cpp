#include "UniformBufferObjectView.h"

#include "UniformBufferObject.h"
#include <Asset/Utility/ShaderAsset/shaderReflectionDataParser.h>

dooms::graphics::UniformBufferObjectView::UniformBufferObjectView
(
	Material* const targetMaterial,
	UniformBufferObject* const targetUBO, 
	const UINT32 defaultBindingPoint,
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
)
	:
	mTargetMaterial(targetMaterial),
	mTargetUniformBufferObject(targetUBO),
	mDefaultBindingPoint(defaultBindingPoint),
	mDefaultTargetPipeLineStage(targetPipeLineStage)
{
}

void dooms::graphics::UniformBufferObjectView::BindUniformBufferObject() const noexcept
{
	D_ASSERT(IsValid(mTargetUniformBufferObject) == true);
	if(IsValid(mTargetUniformBufferObject) == true)
	{
		mTargetUniformBufferObject->BindBuffer(mDefaultBindingPoint, mDefaultTargetPipeLineStage);
	}
}

void dooms::graphics::UniformBufferObjectView::BindUniformBufferObject
(
	const UINT32 bindingPoint,
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
) const noexcept
{
	D_ASSERT(IsValid(mTargetUniformBufferObject) == true);
	if (IsValid(mTargetUniformBufferObject) == true)
	{
		mTargetUniformBufferObject->BindBuffer(bindingPoint, targetPipeLineStage);
	}
}

void dooms::graphics::UniformBufferObjectView::UnBindUniformBufferObject() const noexcept
{
	mTargetUniformBufferObject->UnBindBuffer(mDefaultBindingPoint, mDefaultTargetPipeLineStage);
}

dooms::graphics::Material* dooms::graphics::UniformBufferObjectView::GetTargetMaterial() const
{
	return mTargetMaterial;
}

void dooms::graphics::UniformBufferObjectView::SetBool1(const UINT64 offset, const bool value1)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, offset, sizeof(bool));
}

void dooms::graphics::UniformBufferObjectView::SetBool1(const char* const str, const bool value1)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool));
}

void dooms::graphics::UniformBufferObjectView::SetBool2(const UINT64 offset, const bool* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(bool) * 2);
}

void dooms::graphics::UniformBufferObjectView::SetBool2(const char* const str, const bool* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool) * 2);
}

void dooms::graphics::UniformBufferObjectView::SetBool3(const UINT64 offset, const bool* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(bool) * 3);
}

void dooms::graphics::UniformBufferObjectView::SetBool3(const char* const str, const bool* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool) * 3);
}

void dooms::graphics::UniformBufferObjectView::SetBool4(const UINT64 offset, const bool* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(bool) * 4);
}

void dooms::graphics::UniformBufferObjectView::SetBool4(const char* const str, const bool* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(bool) * 4);
}

void dooms::graphics::UniformBufferObjectView::SetInt1(const UINT64 offset, const INT32 value1)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, offset, sizeof(INT32) * 1);
}

void dooms::graphics::UniformBufferObjectView::SetInt1(const char* const str, const INT32 value1)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 1);
}

void dooms::graphics::UniformBufferObjectView::SetInt2(const UINT64 offset, const INT32* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(INT32) * 2);
}

void dooms::graphics::UniformBufferObjectView::SetInt2(const char* const str, const INT32* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 2);
}

void dooms::graphics::UniformBufferObjectView::SetInt3(const UINT64 offset, const INT32* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(INT32) * 3);
}

void dooms::graphics::UniformBufferObjectView::SetInt3(const char* const str, const INT32* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 3);
}

void dooms::graphics::UniformBufferObjectView::SetInt4(const UINT64 offset, const INT32* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(INT32) * 4);
}

void dooms::graphics::UniformBufferObjectView::SetInt4(const char* const str, const INT32* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(INT32) * 4);
}

void dooms::graphics::UniformBufferObjectView::SetFloat1(const UINT64 offset, const float value1)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, offset, sizeof(float) * 1);
}

void dooms::graphics::UniformBufferObjectView::SetFloat1(const char* const str, const float value1)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(&value1, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 1);
}

void dooms::graphics::UniformBufferObjectView::SetFloat2(const UINT64 offset, const float* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(float) * 2);
}

void dooms::graphics::UniformBufferObjectView::SetFloat2(const char* const str, const float* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 2);
}

void dooms::graphics::UniformBufferObjectView::SetFloat3(const UINT64 offset, const float* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(float) * 3);
}

void dooms::graphics::UniformBufferObjectView::SetFloat3(const char* const str, const float* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 3);
}

void dooms::graphics::UniformBufferObjectView::SetFloat4(const UINT64 offset, const float* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, offset, sizeof(float) * 4);
}

void dooms::graphics::UniformBufferObjectView::SetFloat4(const char* const str, const float* const values)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(values, GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(float) * 4);
}

void dooms::graphics::UniformBufferObjectView::SetMat3x3(const UINT64 offset, const math::Matrix3x3& value)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), offset, sizeof(math::Matrix3x3));
}

void dooms::graphics::UniformBufferObjectView::SetMat3x3(const char* const str, const math::Matrix3x3& value)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Matrix3x3));
}

void dooms::graphics::UniformBufferObjectView::SetMat4x4(const UINT64 offset, const math::Matrix4x4& value)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), offset, sizeof(math::Matrix4x4));
}

void dooms::graphics::UniformBufferObjectView::SetMat4x4(const char* const str, const math::Matrix4x4& value)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(value.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Matrix4x4));
}

void dooms::graphics::UniformBufferObjectView::SetVector2(const UINT64 offset, const math::Vector2& vector2)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(vector2.data(), offset, sizeof(math::Vector2));
}

void dooms::graphics::UniformBufferObjectView::SetVector2(const char* const str, const math::Vector2& vector2)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(vector2.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Vector2));
}

void dooms::graphics::UniformBufferObjectView::SetVector3(const UINT64 offset, const math::Vector3& vector3)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(vector3.data(), offset, sizeof(math::Vector3));
}

void dooms::graphics::UniformBufferObjectView::SetVector3(const char* const str, const math::Vector3& vector3)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(vector3.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Vector3));
}

void dooms::graphics::UniformBufferObjectView::SetVector4(const UINT64 offset, const math::Vector4& vector4)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(vector4.data(), offset, sizeof(math::Vector4));
}

void dooms::graphics::UniformBufferObjectView::SetVector4(const char* const str, const math::Vector4& vector4)
{
	GetTargetUniformBufferObject()->UpdateDataToGPU(vector4.data(), GetTargetUniformBufferObject()->GetUniformVariableOffset(str), sizeof(math::Vector4));
}

