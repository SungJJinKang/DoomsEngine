#include "UniformBufferObject.h"

#include "../Graphics_Core.h"

doom::graphics::UniformBufferObject::UniformBufferObject() 
	: Buffer(), mUniformBufferTempData{nullptr}, mSizeInByte{ 0 }, mBindingPoint{ 0 }
{

}

doom::graphics::UniformBufferObject::~UniformBufferObject()
{
	DeleteBuffers();
}

doom::graphics::UniformBufferObject::UniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize) 
	: Buffer(), mUniformBufferTempData{ nullptr }, mSizeInByte{ uniformBlockSize }, mBindingPoint{ bindingPoint }
{
	GenerateUniformBufferObject(bindingPoint, uniformBlockSize);
}

void doom::graphics::UniformBufferObject::GenerateUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSizeInByte)
{
	D_ASSERT(IsBufferGenerated() == false); // prevent overlap generating buffer

	Buffer::GenBuffer();

	BindBuffer();
	glBufferData(GL_UNIFORM_BUFFER, uniformBlockSizeInByte, NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, mBufferID);

	mSizeInByte = uniformBlockSizeInByte;
	mUniformBufferTempData = new char[uniformBlockSizeInByte];
	std::memset(mUniformBufferTempData, 0x00, uniformBlockSizeInByte);
}

void doom::graphics::UniformBufferObject::DeleteBuffers()
{
	Buffer::DeleteBuffers();
	if (mUniformBufferTempData != nullptr)
	{
		delete[] mUniformBufferTempData;
		mUniformBufferTempData = nullptr;
	}
	
}

void doom::graphics::UniformBufferObject::BufferData() noexcept
{
	if (IsBufferGenerated() == false)
		return;

	if (bmIsDirty == false)
		return;

	BindBuffer();
	glBufferData(GL_UNIFORM_BUFFER, mSizeInByte, mUniformBufferTempData, GL_STATIC_DRAW);
	bmIsDirty = false;
}

void doom::graphics::UniformBufferObject::StoreDataAtTempBuffer(const void* sourceData, const unsigned int sizeInByteOfSourceData, const unsigned int offsetInUniformBlock)
{
	D_ASSERT(offsetInUniformBlock + sizeInByteOfSourceData <= mSizeInByte);
	//D_DEBUG_LOG({ "Store Data At Uniform Buffer Object TempBuffer ", std::to_string(sizeInByteOfSourceData) , std::to_string(offsetInUniformBlock) }, eLogType::D_LOG);
	std::memcpy(mUniformBufferTempData + offsetInUniformBlock, sourceData, sizeInByteOfSourceData);
	bmIsDirty = true;
}

unsigned int doom::graphics::UniformBufferObject::GetAlignedOffset(const std::string elementName)
{
	//Check mUniformBlockOffset
	//if doesn't exist, get offset and cache that value
	return 0;
}

