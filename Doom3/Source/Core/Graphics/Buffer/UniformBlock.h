#pragma once

#include "Buffer.h"

namespace doom
{
	namespace graphics
	{
		class UniformBlock : public Buffer
		{
		private:

		public:
			UniformBlock();

			void BindBuffer() final;
			void UnBindBuffer() final;
			void BufferData(GLsizeiptr size, const void* data) final;
		};
	}
}

