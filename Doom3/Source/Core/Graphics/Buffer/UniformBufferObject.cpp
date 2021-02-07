#include "UniformBufferObject.h"

#include "../Graphics_Core.h"

doom::graphics::UniformBufferObject::UniformBufferObject() : Buffer(), mUniformBufferTempData{}, mSizeInByte{ 0 }, mBindingPoint{ 0 }
{

}

doom::graphics::UniformBufferObject::~UniformBufferObject()
{
	this->DeleteBuffers();
}

doom::graphics::UniformBufferObject::UniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize) : Buffer(), mUniformBufferTempData{}, mSizeInByte{ uniformBlockSize }, mBindingPoint{ bindingPoint }
{
	this->GenUniformBufferObject(bindingPoint, uniformBlockSize);
}

void doom::graphics::UniformBufferObject::GenUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize)
{
	D_ASSERT(this->IsBufferGenerated() == false); // prevent overlap generating buffer

	Buffer::GenBuffer();

	this->BindBuffer();
	glBufferData(GL_UNIFORM_BUFFER, uniformBlockSize, NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, this->mUniformBufferID);

	this->mUniformBufferTempData = new char[uniformBlockSize];
}

void doom::graphics::UniformBufferObject::DeleteBuffers()
{
	Buffer::DeleteBuffers();
	delete this->mUniformBufferTempData;
}

void doom::graphics::UniformBufferObject::StoreDataAtTempBuffer(const void* sourceData, unsigned int sizeInByteOfSourceData, unsigned int offsetInUniformBlock)
{
	D_ASSERT(offsetInUniformBlock + sizeInByteOfSourceData <= this->mSizeInByte);
	std::memcpy(this->mUniformBufferTempData + offsetInUniformBlock, sourceData, sizeInByteOfSourceData);
}

unsigned int doom::graphics::UniformBufferObject::GetAlignedOffset(const std::string elementName)
{
	//Check mUniformBlockOffset
	//if doesn't exist, get offset and cache that value
	return 0;
}

