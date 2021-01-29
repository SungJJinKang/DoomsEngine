#include "VertexArray.h"

#include "../Graphics_Core.h"
doom::graphics::VertexArray::VertexArray() : Buffer()
{
	glGenVertexArrays(1, &(this->mVertexArrayID));
}

void doom::graphics::VertexArray::BindBuffer()
{
	glBindVertexArray(this->mVertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, this->mBufferID);
}

void doom::graphics::VertexArray::UnBindBuffer()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void doom::graphics::VertexArray::BufferData(GLsizeiptr size, const void* data)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
