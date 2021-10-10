#include "Buffer.h"


doom::graphics::Buffer::Buffer() : mBufferID{ 0 }
{

}



void doom::graphics::Buffer::GenBuffer()
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

int64_t doom::graphics::Buffer::GetBufferParameteri64v(eBufferBindingTarget bindingTarget, eBufferParameter bufferParameter)
{
	int64_t value;
	glGetBufferParameteri64v(static_cast<unsigned int>(bindingTarget), static_cast<unsigned int>(bufferParameter), &value);
	return value;
}

int64_t doom::graphics::Buffer::GetNamedBufferParameteri64v(eBufferParameter bufferParameter)
{
	int64_t value;
	glGetNamedBufferParameteri64v(mBufferID, static_cast<unsigned int>(bufferParameter), &value);
	return value;
}

doom::graphics::Buffer::~Buffer()
{
	DeleteBuffers();
}

void doom::graphics::Buffer::DeleteBuffers()
{
	if (mBufferID.Get() != 0)
	{
		glDeleteBuffers(1, &(mBufferID));
		mBufferID = 0;
	}
}

bool doom::graphics::Buffer::IsBufferGenerated() const
{
	return mBufferID.Get() != 0;
}

