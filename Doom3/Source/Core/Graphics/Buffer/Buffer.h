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

			Buffer();
			~Buffer();

		public:
			virtual void BindBuffer() = 0;
			virtual void UnBindBuffer() = 0;
			virtual void BufferData(GLsizeiptr size, const void* data) = 0;
		};
	}
}