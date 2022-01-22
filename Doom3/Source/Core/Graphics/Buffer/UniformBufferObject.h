#pragma once

#include "Buffer.h"

#include <unordered_map>
#include <string>

#include "../OverlapBindChecker.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "UniformBufferObject.reflection.h"
namespace dooms
{
	namespace graphics
	{
		/// <summary>
		/// reference : https://www.khronos.org/opengl/wiki/Program_Introspection, https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
		/// </summary>
		class DOOM_API D_CLASS UniformBufferObject : public Buffer
		{
			GENERATE_BODY()
			

		private:

			static inline const char GL_UNIFORM_BUFFER_TAG[]{ "GL_UNIFORM_BUFFER" };

			/// <summary>
			/// for buffer data only when data is dirty
			/// </summary>
			D_PROPERTY()
			bool bmIsDirty = true;

			D_PROPERTY()
			std::string mUniformBlockName;

			D_PROPERTY()
			UINT32 mDefaultBindingPoint;
			D_PROPERTY()
			GraphicsAPI::eGraphicsPipeLineStage mDefaultTargetPipeLineStage;
			D_PROPERTY()
			UINT64 mUniformBufferSize;
			/// <summary>
			/// Buffer::data is same with mUniformBufferID
			/// </summary>
			//UINT32& mUniformBufferID = data; USE data


			// TODO: Check Which is faster : 
			// Store at temporary data in cpu and send it to gpu once glbufferdata VS send data instantly to gpu glbuffersubdata ( don't store at memory )

			/// <summary>
			/// each element is pointer of consecutive dats
			/// Use life mUniformBuffers[0][offset in byte]
			///
			/// </summary>
			D_PROPERTY()
			char* mUniformBufferTempData;
			

			/// <summary>
			/// Cache element of uniform block's aligned offset
			/// </summary>
			std::unordered_map<std::string, UINT32> mUniformBlockAlignedOffset{};
		
			void GenerateUniformBufferObject(const UINT64 uniformBufferSize, const void* const initialData = 0);
			void DeleteBuffers() final;

			FORCE_INLINE void BindBuffer() const noexcept final
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(GL_UNIFORM_BUFFER_TAG, mBufferID))
				{
					GraphicsAPI::BindConstantBuffer(mBufferID, mDefaultBindingPoint, mDefaultTargetPipeLineStage);
				}
			}
			FORCE_INLINE void BindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(GL_UNIFORM_BUFFER_TAG, mBufferID))
				{
					GraphicsAPI::BindConstantBuffer(mBufferID, bindingPoint, targetPipeLineStage);
				}
			}

			void OnSetPendingKill() override;
			

		public:

			UniformBufferObject() = delete;
			UniformBufferObject
			(
				const std::string& uniformBlockName,
				const UINT64 uniformBufferSize,
				const UINT32 defaultBindingPoint, 
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage,
				const void* const initialData
			);
			~UniformBufferObject();

			UniformBufferObject(const UniformBufferObject&) = delete;
			UniformBufferObject(UniformBufferObject&&) noexcept = default;
			UniformBufferObject& operator=(const UniformBufferObject&) = delete;
			UniformBufferObject& operator=(UniformBufferObject&&) noexcept = default;
			
			/// <summary>
			/// Send data in mUniformBufferData to gpu 
			/// </summary>
			/// <returns></returns>
			virtual void BufferData() noexcept;
			virtual void BufferSubData(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock) noexcept;

			/// <summary>
			/// Store data in temporary buffer
			/// data isn't send to gpu instantly, it is stored in temp buffer
			/// if you want buffer data ( send data to gpu ), call BufferData function
			/// </summary>
			/// <param name="sourceData">souce data address</param>
			/// <param name="sizeInByte">data size in byte</param>
			/// <param name="offsetInUniformBlock"></param>
			void StoreDataAtTempBuffer(const void* sourceData, const UINT32 sizeOfSourceData, const UINT32 offsetInUniformBlock);
			//void StoreDataAtTempBuffer(const void* sourceData, const std::string& elementName);

			UINT32 GetAlignedOffset(const std::string elementName);
		};
	}
}

