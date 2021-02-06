#include "Buffer.h"

#include "../Graphics_Core.h"
using namespace doom::graphics;

Buffer::Buffer() : mBufferID{ 0 }
{

}

constexpr Buffer::Buffer(Buffer&& buffer) noexcept : mBufferID{ buffer.mBufferID }
{
	buffer.mBufferID = 0;
}

constexpr doom::graphics::Buffer& Buffer::operator=(Buffer&& buffer) noexcept
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


