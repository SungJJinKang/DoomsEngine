#include "UniformBufferObjectView.h"

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