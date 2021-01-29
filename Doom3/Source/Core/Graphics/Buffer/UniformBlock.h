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

			inline void BindBuffer() noexcept final;
			inline void UnBindBuffer() noexcept final;
			inline void BufferData(GLsizeiptr size, const void* data) noexcept final;
		};
	}
}

