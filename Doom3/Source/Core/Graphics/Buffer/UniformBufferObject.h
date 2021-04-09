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

			static inline const char GL_UNIFORM_BUFFER_TAG[]{ "GL_UNIFORM_BUFFER" };

			/// <summary>
			/// for buffer data only when data is dirty
			/// </summary>
			bool bmIsDirty = true;
			std::string mUniformBlockName;

			/// <summary>
			/// Buffer::data is same with mUniformBufferID
			/// </summary>
			//unsigned int& mUniformBufferID = this->data; USE data


			// TODO: Check Which is faster : 
			// Store at temporary data in cpu and send it to gpu once glbufferdata VS send data instantly to gpu glbuffersubdata ( don't store at memory )

			/// <summary>
			/// each element is pointer of consecutive dats
			/// Use life mUniformBuffers[0][offset in byte]
			///
			/// </summary>
			ZeroResetMoveContainer<char*> mUniformBufferTempData{ nullptr };
			unsigned int mSizeInByte;
			unsigned int mBindingPoint;

			/// <summary>
			/// Cache element of uniform block's aligned offset
			/// </summary>
			std::unordered_map<std::string, unsigned int> mUniformBlockAlignedOffset{};
		
			void GenerateUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSizeInByte);
			void DeleteBuffers() final;

			FORCE_INLINE void BindBuffer() noexcept final
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(GL_UNIFORM_BUFFER_TAG, this->mBufferID))
				{
					glBindBuffer(GL_UNIFORM_BUFFER, this->mBufferID);
				}
				
			}
			FORCE_INLINE virtual void UnBindBuffer() noexcept final
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(GL_UNIFORM_BUFFER_TAG, 0))
				{
					glBindBuffer(GL_UNIFORM_BUFFER, 0);
				}
			
			}

			/// <summary>
			/// Send data in mUniformBufferData to gpu 
			/// </summary>
			/// <returns></returns>
			virtual void BufferData() noexcept;
			

		public:

			UniformBufferObject();
			UniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize);
			~UniformBufferObject();

			UniformBufferObject(const UniformBufferObject&) = delete;
			UniformBufferObject(UniformBufferObject&&) noexcept = default;
			UniformBufferObject& operator=(const UniformBufferObject&) = delete;
			UniformBufferObject& operator=(UniformBufferObject&&) noexcept = default;
			
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

