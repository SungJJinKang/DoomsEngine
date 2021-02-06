#pragma once
#include <array>
#include "UniformBufferObject.h"

namespace doom
{
	namespace graphics
	{
		class UniformBufferObjectManager
		{
			friend class Graphics;
		private:

#define MAX_UNIFORM_BLOCK_BINDING_POINT 10
			/// <summary>
			/// index is same with binding point
			/// </summary>
			static inline std::array<UniformBufferObject, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects;

			// TODO : Use glGetActiveUniformBlockiv https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetActiveUniformBlock.xhtml

			static void Init();
			static void BufferData();
		public:
			
		};
	}
}

