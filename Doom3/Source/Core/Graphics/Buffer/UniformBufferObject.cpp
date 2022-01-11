#include "UniformBufferObject.h"


void dooms::graphics::UniformBufferObject::OnSetPendingKill()
{
	Buffer::OnSetPendingKill();

	DeleteBuffers();
}

dooms::graphics::UniformBufferObject::UniformBufferObject() 
	: Buffer(), mUniformBufferTempData{nullptr}, mSizeInByte{ 0 }, mBindingPoint{ 0 }
{

}

dooms::graphics::UniformBufferObject::~UniformBufferObject()
{
	DeleteBuffers();
}

dooms::graphics::UniformBufferObject::UniformBufferObject(UINT32 bindingPoint, UINT32 uniformBlockSize) 
	: Buffer(), mUniformBufferTempData{ nullptr }, mSizeInByte{ uniformBlockSize }, mBindingPoint{ bindingPoint }
{
	GenerateUniformBufferObject(bindingPoint, uniformBlockSize);
}

void dooms::graphics::UniformBufferObject::GenerateUniformBufferObject(UINT32 bindingPoint, UINT32 uniformBlockSizeInByte)
{
	D_ASSERT(IsBufferGenerated() == false); // prevent overlap generating buffer
	if (IsBufferGenerated() == false)
	{
		Buffer::GenBuffer();

		BindBuffer();

		GraphicsAPI::AllocateBufferMemory(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, uniformBlockSizeInByte, NULL);
		GraphicsAPI::UpdateDataToBuffer(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, 0, uniformBlockSizeInByte, 0);
		GraphicsAPI::BindBufferToIndexedBuffer(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, bindingPoint, mBufferID);

		mSizeInByte = uniformBlockSizeInByte;
		mUniformBufferTempData = new char[uniformBlockSizeInByte];
		std::memset(mUniformBufferTempData, 0x00, uniformBlockSizeInByte);
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
		BindBuffer();
		GraphicsAPI::UpdateDataToBuffer(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, 0, mSizeInByte, mUniformBufferTempData);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::BufferSubData(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if (IsBufferGenerated() == true)
	{
		BindBuffer();
		GraphicsAPI::UpdateDataToBuffer(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offsetInUniformBlock, sizeOfSourceData, sourceData);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::StoreDataAtTempBuffer(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock)
{
	D_ASSERT(IsBufferGenerated() == true);
	D_ASSERT(offsetInUniformBlock + sizeOfSourceData <= mSizeInByte);

	std::memcpy(mUniformBufferTempData + offsetInUniformBlock, sourceData, sizeOfSourceData);
	bmIsDirty = true;
}

UINT32 dooms::graphics::UniformBufferObject::GetAlignedOffset(const std::string elementName)
{
	//Check mUniformBlockOffset
	//if doesn't exist, get offset and cache that value
	return 0;
}

