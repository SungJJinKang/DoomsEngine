#include "Buffer.h"

#include "../Graphics_Core.h"
using namespace doom::graphics;

Buffer::Buffer()
{
	glGenBuffers(1, &(this->mBufferID));
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &(this->mBufferID));
}
