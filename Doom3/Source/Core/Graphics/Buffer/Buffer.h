#pragma once

#include "../Graphics_Core.h"

namespace doom
{
	namespace graphics
	{
		class Buffer
		{
		private:
			
		protected:
			unsigned int mBufferID;

			Buffer(bool genBuffer);
			~Buffer();

			virtual void GenBuffer();
			virtual void DeleteBuffers();

		public:
			inline virtual void BindBuffer() noexcept = 0;
			inline virtual void UnBindBuffer() noexcept = 0;
			inline virtual void BufferData(GLsizeiptr size, const void* data) noexcept = 0;
		};
	}
}