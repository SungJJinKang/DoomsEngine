#pragma once

#include "../Graphics_Core.h"
#include "../API/OpenglAPI.h"
#include "BufferID.h"

namespace doom
{
	namespace graphics
	{
		class Mesh;
		class UniformBufferObject;
		class Buffer : public DObject
		{
			DOBJECT_ABSTRACT_CLASS_BODY(Buffer);

		protected:

			BufferID mBufferID;

			Buffer();
			virtual ~Buffer();

			Buffer(const Buffer&) = delete;
			Buffer& operator=(const Buffer&) noexcept = delete;

			Buffer(Buffer&& buffer) noexcept = default;
			Buffer& operator=(Buffer&& buffer) noexcept = default;

			void GenBuffer();
			virtual void GenBufferIfNotGened();
			virtual void DeleteBuffers();

		protected:
			

		public:

			inline virtual void BindBuffer() const noexcept = 0;
			inline virtual void UnBindBuffer() const noexcept = 0;
			virtual bool IsBufferGenerated() const;


			enum class eBufferBindingTarget
			{
				ARRAY_BUFFER = GL_ARRAY_BUFFER,
				ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
				COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
				COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
				DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
				DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
				ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
				PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
				PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
				QUERY_BUFFER = GL_QUERY_BUFFER,
				SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
				TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
				TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
				UNIFORM_BUFFER = GL_UNIFORM_BUFFER
			};
			enum class eBufferParameter
			{
				BUFFER_ACCESS = GL_BUFFER_ACCESS,
				BUFFER_ACCESS_FLAGS = GL_BUFFER_ACCESS_FLAGS,
				BUFFER_IMMUTABLE_STORAGE = GL_BUFFER_IMMUTABLE_STORAGE,
				BUFFER_MAPPED = GL_BUFFER_MAPPED,
				BUFFER_MAP_LENGTH = GL_BUFFER_MAP_LENGTH,
				BUFFER_MAP_OFFSET = GL_BUFFER_MAP_OFFSET,
				BUFFER_SIZE = GL_BUFFER_SIZE,
				BUFFER_STORAGE_FLAGS = GL_BUFFER_STORAGE_FLAGS,
				BUFFER_USAGE = GL_BUFFER_USAGE,
			};
			int64_t GetNamedBufferParameteri64v(eBufferParameter bufferParameter);
			/// <summary>
			/// get parameter value aboud current bound bindingTarget
			/// </summary>
			/// <param name="bindingTarget"></param>
			/// <param name="bufferParameter"></param>
			/// <returns></returns>
			int64_t GetBufferParameteri64v(eBufferBindingTarget bindingTarget, eBufferParameter bufferParameter);
		};
	}
}