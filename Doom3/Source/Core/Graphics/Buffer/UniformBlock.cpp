#include "UniformBlock.h"

#include "../Graphics_Core.h"

doom::graphics::UniformBlock::UniformBlock() : Buffer()
{

}

void doom::graphics::UniformBlock::BindBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->mBufferID);
}

void doom::graphics::UniformBlock::UnBindBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void doom::graphics::UniformBlock::BufferData(GLsizeiptr size, const void* data)
{
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
}
