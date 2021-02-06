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

			constexpr Buffer();
			Buffer(bool dummyForGenBuffer);
			~Buffer();

			Buffer(const Buffer&) = delete;
			Buffer& operator=(const Buffer&) noexcept = delete;

			constexpr Buffer(Buffer&& buffer) noexcept;
			constexpr Buffer& operator=(Buffer&& buffer) noexcept;

			virtual void GenBuffer();
			virtual void DeleteBuffers();

		public:
			inline virtual void BindBuffer() noexcept = 0;
			inline virtual void UnBindBuffer() noexcept = 0;
		};
	}
}