#include "Buffer.h"

#include "../Graphics_Core.h"
using namespace doom::graphics;

Buffer::Buffer() : mBufferID{ 0 }
{

}



void Buffer::GenBuffer()
{
	if (mBufferID == 0)
	{
		glGenBuffers(1, &(mBufferID));
	}

}

void doom::graphics::Buffer::GenBufferIfNotGened()
{
	if (IsBufferGenerated() == true)
	{
		return;
	}
		
	GenBuffer();
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
	glGetNamedBufferParameteri64v(mBufferID, static_cast<unsigned int>(bufferParameter), &value);
	return value;
}

Buffer::~Buffer()
{
	DeleteBuffers();
}

void Buffer::DeleteBuffers()
{
	if (mBufferID.Get() != 0)
	{
		glDeleteBuffers(1, &(mBufferID));
		mBufferID = 0;
	}
}

bool Buffer::IsBufferGenerated()
{
	return mBufferID.Get() != 0;
}

