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
	:
	mUniformBufferObject(),
	mUniformBlockName(uniformBlockName),
	mUniformBufferSize(uniformBufferSize),
	mDefaultBindingPoint(defaultBindingPoint),
	mDefaultTargetPipeLineStage(targetPipeLineStage),
	mUniformBufferTempData(nullptr)
{
	GenerateUniformBufferObject(uniformBufferSize);
}

dooms::graphics::UniformBufferObject::~UniformBufferObject()
{
	DeleteBuffers();
}


std::string dooms::graphics::UniformBufferObject::GetUniformBlockName()
{
	return mUniformBlockName;
}

const std::string& dooms::graphics::UniformBufferObject::GetUniformBlockName() const
{
	return mUniformBlockName;
}

void dooms::graphics::UniformBufferObject::GenerateUniformBufferObject(const UINT64 uniformBufferSize, const void* const initialData)
{
	D_ASSERT(IsBufferGenerated() == false); // prevent overlap generating buffer
	if (IsBufferGenerated() == false)
	{
		mUniformBufferObject = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, uniformBufferSize, initialData);

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
	if(mUniformBufferObject.IsValid())
	{
		dooms::graphics::GraphicsAPI::DestroyBuffer(mUniformBufferObject);
		mUniformBufferObject.Reset();
	}

	if (mUniformBufferTempData != nullptr)
	{
		delete[] mUniformBufferTempData;
		mUniformBufferTempData = nullptr;
	}
	
}



void dooms::graphics::UniformBufferObject::UpdateLocalBufferToGPU() noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if (IsBufferGenerated() == true && bmIsDirty == true)
	{
		GraphicsAPI::UpdateDataToBuffer(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, 0, mUniformBufferSize, mUniformBufferTempData);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::UpdateLocalBufferToGPU(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if (IsBufferGenerated() == true)
	{
		GraphicsAPI::UpdateDataToBuffer(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offsetInUniformBlock, sizeOfSourceData, sourceData);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::UpdateLocalBuffer
(
	const void* sourceData, 
	const UINT32 sizeOfSourceData, 
	const UINT32 offsetInUniformBlock
)
{
	D_ASSERT(IsBufferGenerated() == true);
	D_ASSERT_LOG(static_cast<UINT64>(offsetInUniformBlock) + static_cast<UINT64>(sizeOfSourceData) <= mUniformBufferSize, "Updated data is out of range");

	std::memcpy(mUniformBufferTempData + offsetInUniformBlock, sourceData, sizeOfSourceData);
	bmIsDirty = true;
}


bool dooms::graphics::UniformBufferObject::IsBufferGenerated() const
{
	return mUniformBufferObject.IsValid();
}

