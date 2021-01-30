#pragma once
#include "Buffer.h"

#include <functional>
#include "../../Asset/ThreeDModelAsset.h"

namespace doom
{
	namespace graphics
	{
		class Mesh : public Buffer
		{
		private:
			unsigned int mVertexArrayObject;
			unsigned int& mVertexBufferObject = this->mBufferID;
			unsigned int mElementBufferObject;

			const std::reference_wrapper<const ThreeDModelMesh> mThreeDModelMesh;
		public:
			inline Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
				: Buffer(), mThreeDModelMesh{ threeDModelMesh }, mVertexArrayObject{}, mElementBufferObject{}
			{
				glGenVertexArrays(1, &(this->mVertexArrayObject));


				if (mThreeDModelMesh.get().bHasIndices)
				{
					glGenBuffers(1, &(this->mElementBufferObject));
				}
			}

			inline void BindBuffer() noexcept final
			{
				glBindVertexArray(this->mVertexArrayObject);
			}
			inline void UnBindBuffer() noexcept final
			{
				glBindVertexArray(0);
			}

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
			void BufferData(GLsizeiptr size, const void* data) noexcept final;
		};
	}
}