#include "UniformBufferObjectView.h"

#include "UniformBufferObject.h"

dooms::graphics::UniformBufferObjectView::UniformBufferObjectView
(
	UniformBufferObject* const ubo,
	const UINT32 defaultBindingPoint,
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
)
	: mTargetUniformBufferObject(ubo), mDefaultBindingPoint(defaultBindingPoint), mDefaultTargetPipeLineStage(targetPipeLineStage)
{
}

void dooms::graphics::UniformBufferObjectView::UpadteLocalBuffer
(
	const void* sourceData, 
	const UINT32 sizeOfSourceData,
	const char* const targetUniformVariableName
)
{
	D_ASSERT(IsValid(mTargetUniformBufferObject));
	if(IsValid(mTargetUniformBufferObject))
	{
		const UINT32 uniformVariableOffset = GetOrUpdateUniformVaraibleOffsetInUniformBlock(targetUniformVariableName);

		mTargetUniformBufferObject->UpdateLocalBuffer(sourceData, sizeOfSourceData, uniformVariableOffset);
	}
}

void dooms::graphics::UniformBufferObjectView::BindUniformBufferObject() const noexcept
{
	D_ASSERT(IsValid(mTargetUniformBufferObject) == true);
	if(IsValid(mTargetUniformBufferObject) == true)
	{
		mTargetUniformBufferObject->BindBuffer();
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

UINT32 dooms::graphics::UniformBufferObjectView::UpdateUniformVariableOffsetCache(const char* const targetUniformVariableName)
{
	UINT32 uniformVariableOffset = (UINT32)-1;

	const auto node = mUniformVariableOffsetCache.find(targetUniformVariableName);
	if (node == mUniformVariableOffsetCache.end())
	{
		// TODO
	}
	else
	{
		uniformVariableOffset = node->second;
	}

	D_ASSERT(uniformVariableOffset != ((UINT32)-1));
	return uniformVariableOffset;
}

UINT32 dooms::graphics::UniformBufferObjectView::GetOrUpdateUniformVaraibleOffsetInUniformBlock
(
	const char* const targetUniformVariableName
)
{
	UINT32 uniformVariableOffset = (UINT32)-1;

	const auto node = mUniformVariableOffsetCache.find(targetUniformVariableName);
	if (node == mUniformVariableOffsetCache.end())
	{
		uniformVariableOffset = UpdateUniformVariableOffsetCache(targetUniformVariableName);
	}
	else
	{
		uniformVariableOffset = node->second;
	}


	D_ASSERT(uniformVariableOffset != ((UINT32)-1));
	return uniformVariableOffset;
}