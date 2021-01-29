#include "UniformBlock.h"

#include "../Graphics_Core.h"

doom::graphics::UniformBlock::UniformBlock() : Buffer()
{

}

inline void doom::graphics::UniformBlock::BindBuffer() noexcept
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->mBufferID);
}

inline void doom::graphics::UniformBlock::UnBindBuffer() noexcept
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

inline void doom::graphics::UniformBlock::BufferData(GLsizeiptr size, const void* data) noexcept
{
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
}
