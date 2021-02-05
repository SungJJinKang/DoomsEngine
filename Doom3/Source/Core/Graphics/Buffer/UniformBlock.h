#pragma once

#include "Buffer.h"
#include "../../OverlapBindChecker/OverlapBindChecker.h"

namespace doom
{
	namespace graphics
	{
		/// <summary>
		/// reference : https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
		/// </summary>
		class UniformBlock : public Buffer
		{
		private:
			unsigned int& mUniformBufferID = this->mBufferID;
		public:

			UniformBlock();

			inline void BindBuffer() noexcept final
			{
				D_CHECK_OVERLAP_BIND("UniformBlock", this->mUniformBufferID);
				glBindBuffer(GL_UNIFORM_BUFFER, this->mUniformBufferID);
			}
			inline void UnBindBuffer() noexcept final
			{
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
			inline void BufferData(GLsizeiptr size, const void* data) noexcept final
			{
				glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
			}
		};
	}
}

