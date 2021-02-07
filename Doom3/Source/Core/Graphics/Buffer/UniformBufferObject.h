#pragma once

#include "Buffer.h"

#include <vector>
#include <unordered_map>
#include <string>

#include "../OverlapBindChecker.h"
#include "UniformBlockOffsetInfo.h"
namespace doom
{
	namespace graphics
	{
		/// <summary>
		/// reference : https://www.khronos.org/opengl/wiki/Program_Introspection, https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
		/// </summary>
		class UniformBufferObject : public Buffer
		{
			friend class UniformBufferObjectManager;
		private:

			std::string mUniformBlockName;

			/// <summary>
			/// Buffer::mBufferID is same with mUniformBufferID
			/// </summary>
			unsigned int& mUniformBufferID = this->mBufferID;


			// TODO: Check Which is faster : 
			// Store at temporary data in cpu and send it to gpu once glbufferdata VS send data instantly to gpu glbuffersubdata ( don't store at memory )

			/// <summary>
			/// each element is pointer of consecutive dats
			/// Use life mUniformBuffers[0][offset in byte]
			///
			/// </summary>
			char* mUniformBufferTempData;
			unsigned int mSizeInByte;
			unsigned int mBindingPoint;

			/// <summary>
			/// Cache element of uniform block's aligned offset
			/// </summary>
			std::unordered_map<std::string, unsigned int> mUniformBlockAlignedOffset{};
		
			void GenUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize);
			void DeleteBuffers() final;

			inline void BindBuffer() noexcept final
			{
				D_CHECK_OVERLAP_BIND("UniformBlock", this->mUniformBufferID);
				glBindBuffer(GL_UNIFORM_BUFFER, this->mUniformBufferID);
			}
			inline virtual void UnBindBuffer() noexcept final
			{
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}

			/// <summary>
			/// Send data in mUniformBufferData to gpu 
			/// </summary>
			/// <returns></returns>
			inline virtual void BufferData() noexcept
			{
				if (this->IsBufferGenerated() == false)
					return;

				this->BindBuffer();
				glBufferData(GL_UNIFORM_BUFFER, mSizeInByte, mUniformBufferTempData, GL_STATIC_DRAW);
			}

		public:

			UniformBufferObject();
			UniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize);
			~UniformBufferObject();

			/// <summary>
			/// Store data in temporary buffer
			/// data isn't send to gpu instantly, it is stored in temp buffer
			/// if you want buffer data ( send data to gpu ), call BufferData function
			/// </summary>
			/// <param name="sourceData">souce data address</param>
			/// <param name="sizeInByte">data size in byte</param>
			/// <param name="offsetInUniformBlock"></param>
			void StoreDataAtTempBuffer(const void* sourceData, unsigned int sizeInByteOfSourceData, unsigned int offsetInUniformBlock);
			//void StoreDataAtTempBuffer(const void* sourceData, const std::string& elementName);

			unsigned int GetAlignedOffset(const std::string elementName);
		};
	}
}

