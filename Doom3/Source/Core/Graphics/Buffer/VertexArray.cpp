#include "VertexArray.h"

#include "../Graphics_Core.h"
doom::graphics::VertexArray::VertexArray() : Buffer()
{
	glGenVertexArrays(1, &(this->mVertexArrayID));
}

inline void doom::graphics::VertexArray::BindBuffer() noexcept
{
	glBindVertexArray(this->mVertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, this->mBufferID);
}

inline void doom::graphics::VertexArray::UnBindBuffer() noexcept
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void doom::graphics::VertexArray::BufferData(GLsizeiptr size, const void* data) noexcept
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
