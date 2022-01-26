#include "UniformBufferObject.h"


void dooms::graphics::UniformBufferObject::OnSetPendingKill()
{
	Buffer::OnSetPendingKill();

	DeleteBuffers();
}

dooms::graphics::UniformBufferObject::UniformBufferObject
(
	const std::string& uniformBlockName,
	const UINT64 uniformBufferSize,
	const UINT32 defaultBindingPoint, 
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage,
	const void* const initialData
)
	: mUniformBlockName(uniformBlockName), mUniformBufferSize(0), mDefaultBindingPoint(defaultBindingPoint), mDefaultTargetPipeLineStage(targetPipeLineStage), mUniformBufferTempData(nullptr)
{
	GenerateUniformBufferObject(uniformBufferSize);
}

dooms::graphics::UniformBufferObject::~UniformBufferObject()
{
	DeleteBuffers();
}


void dooms::graphics::UniformBufferObject::GenerateUniformBufferObject(const UINT64 uniformBufferSize, const void* const initialData)
{
	D_ASSERT(IsBufferGenerated() == false); // prevent overlap generating buffer
	if (IsBufferGenerated() == false)
	{
		Buffer::GenBuffer();

		GraphicsAPI::AllocateBufferMemory(mBufferID.GetBufferIDRef(), GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, uniformBufferSize, NULL);

		if(initialData != 0)
		{
			GraphicsAPI::UpdateDataToBuffer(mBufferID, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, 0, uniformBufferSize, initialData);
		}
		
		mUniformBufferSize = uniformBufferSize;

		if (mUniformBufferTempData != nullptr)
		{
			delete[] mUniformBufferTempData;
			mUniformBufferTempData = nullptr;
		}

		mUniformBufferTempData = new char[uniformBufferSize];
		std::memset(mUniformBufferTempData, 0x00, uniformBufferSize);
	}

}

void dooms::graphics::UniformBufferObject::DeleteBuffers()
{
	Buffer::DeleteBuffers();
	if (mUniformBufferTempData != nullptr)
	{
		delete[] mUniformBufferTempData;
		mUniformBufferTempData = nullptr;
	}
	
}

void dooms::graphics::UniformBufferObject::BufferData() noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if (IsBufferGenerated() == true && bmIsDirty == true)
	{
		GraphicsAPI::UpdateDataToBuffer(mBufferID, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, 0, mUniformBufferSize, mUniformBufferTempData);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::BufferSubData(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if (IsBufferGenerated() == true)
	{
		GraphicsAPI::UpdateDataToBuffer(mBufferID, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offsetInUniformBlock, sizeOfSourceData, sourceData);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::StoreDataAtTempBuffer(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock)
{
	D_ASSERT(IsBufferGenerated() == true);
	D_ASSERT(offsetInUniformBlock + sizeOfSourceData <= mUniformBufferSize);

	std::memcpy(mUniformBufferTempData + offsetInUniformBlock, sourceData, sizeOfSourceData);
	bmIsDirty = true;
}

UINT32 dooms::graphics::UniformBufferObject::GetAlignedOffset(const std::string elementName)
{
	//Check mUniformBlockOffset
	//if doesn't exist, get offset and cache that value
	return 0;
}

