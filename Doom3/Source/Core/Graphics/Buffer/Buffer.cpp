#include "Buffer.h"

#include "../Graphics_Core.h"
using namespace doom::graphics;

Buffer::Buffer() : mBufferID{ 0 }
{

}

Buffer::Buffer(Buffer&& buffer) noexcept : mBufferID{ buffer.mBufferID }
{
	buffer.mBufferID = 0;
}

doom::graphics::Buffer& Buffer::operator=(Buffer&& buffer) noexcept
{
	this->mBufferID = buffer.mBufferID;
	buffer.mBufferID = 0;
	return *this;
}

void Buffer::GenBuffer()
{
	D_ASSERT(this->mBufferID == 0);

	glGenBuffers(1, &(this->mBufferID));
}

void doom::graphics::Buffer::GenBufferIfNotGened()
{
	if (this->IsBufferGenerated() == true)
	{
		return;
	}
		
	this->GenBuffer();
}

int64_t Buffer::GetBufferParameteri64v(eBufferBindingTarget bindingTarget, eBufferParameter bufferParameter)
{
	int64_t value;
	glGetBufferParameteri64v(static_cast<unsigned int>(bindingTarget), static_cast<unsigned int>(bufferParameter), &value);
	return value;
}

int64_t Buffer::GetNamedBufferParameteri64v(eBufferParameter bufferParameter)
{
	int64_t value;
	glGetNamedBufferParameteri64v(this->mBufferID, static_cast<unsigned int>(bufferParameter), &value);
	return value;
}

Buffer::~Buffer()
{
	this->DeleteBuffers();
}

void Buffer::DeleteBuffers()
{
	if (this->mBufferID != 0)
	{
		glDeleteBuffers(1, &(this->mBufferID));
		this->mBufferID = 0;
	}
}

bool Buffer::IsBufferGenerated()
{
	return this->mBufferID != 0;
}

