#include "Buffer.h"

#include "../Graphics_Core.h"
using namespace doom::graphics;

Buffer::Buffer(bool genBuffer) : mBufferID{ 0 }
{
	if (genBuffer == true)
	{
		this->GenBuffer();
	}
}

void Buffer::GenBuffer()
{
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
	}
}
