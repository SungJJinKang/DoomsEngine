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

			inline void BindBuffer() noexcept final;
			inline void UnBindBuffer() noexcept final;

			/// <summary>
			/// layout(location = 0) in vec3 aPos;
			/// layout(location = 1) in vec2 aUV0;
			/// layout(location = 2) in vec3 aNormal;
			/// layout(location = 3) in vec3 aTangent;
			/// layout(location = 4) in vec3 aBitangent;
			/// 
			/// above datas should be arranged sequentially
			/// 
			/// aPos(0)  aUV0  aNormal  aTangent  aBitangent
			/// 
			/// </summary>
			/// <param name="size"></param>
			/// <param name="data"></param>
			inline void BufferData(GLsizeiptr size, const void* data) noexcept final;
		};
	}
}