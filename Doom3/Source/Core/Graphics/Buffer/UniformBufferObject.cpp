#include "UniformBufferObject.h"

#include "../Graphics_Core.h"

doom::graphics::UniformBufferObject::UniformBufferObject() : Buffer(), mUniformBufferTempData{}, mSizeInByte{ 0 }, mBindingPoint{ 0 }
{

}

doom::graphics::UniformBufferObject::UniformBufferObject(unsigned int sizeInByte, unsigned int bindingPoint) : Buffer(), mUniformBufferTempData{}, mSizeInByte{ sizeInByte }, mBindingPoint{ bindingPoint }
{
	this->GenUniformBufferObject(sizeInByte, bindingPoint);
}

void doom::graphics::UniformBufferObject::GenUniformBufferObject(unsigned int sizeInByte, unsigned int bindingPoint)
{
	Buffer::GenBuffer();

	this->BindBuffer();
	glBufferData(GL_UNIFORM_BUFFER, sizeInByte, NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, this->mUniformBufferID);

	this->mUniformBufferTempData = new char[sizeInByte];
}

void doom::graphics::UniformBufferObject::DeleteBuffers()
{
	Buffer::DeleteBuffers();
	delete this->mUniformBufferTempData;
}

void doom::graphics::UniformBufferObject::TempBuffer(const void* sourceData, unsigned int sizeInByteOfSourceData, unsigned int offsetInUniformBlock)
{
	D_ASSERT(offsetInUniformBlock + sizeInByteOfSourceData <= this->mSizeInByte);
	std::memcpy(this->mUniformBufferTempData + offsetInUniformBlock, sourceData, sizeInByteOfSourceData);
}

unsigned int doom::graphics::UniformBufferObject::GetAlignedOffset(const std::string elementName)
{
	//Check mUniformBlockOffset
	//if doesn't exist, get offset and cache that value
	
}

