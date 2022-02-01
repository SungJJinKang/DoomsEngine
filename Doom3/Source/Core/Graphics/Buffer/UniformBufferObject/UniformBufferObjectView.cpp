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

