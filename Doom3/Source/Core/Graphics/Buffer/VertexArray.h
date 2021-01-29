#pragma once

#include "Buffer.h"
namespace doom
{
	namespace graphics
	{
		class VertexArray : public Buffer
		{
		private:
			unsigned int mVertexArrayID;
		public:
			VertexArray();

			void BindBuffer() final;
			void UnBindBuffer() final;

			void BufferData(GLsizeiptr size, const void* data) final;
		};
	}
}