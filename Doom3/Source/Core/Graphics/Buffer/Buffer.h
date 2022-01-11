#pragma once

#include "../Graphics_Core.h"
#include "BufferID.h"

#include "Buffer.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Mesh;
		class UniformBufferObject;
		class DOOM_API D_CLASS Buffer : public DObject
		{
			GENERATE_BODY()
			

		protected:

			D_PROPERTY()
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

			void OnSetPendingKill() override;

		public:

			D_FUNCTION()
			inline virtual void BindBuffer() const noexcept = 0;
			D_FUNCTION()
			inline virtual void UnBindBuffer() const noexcept = 0;
			D_FUNCTION()
			virtual bool IsBufferGenerated() const;


			/*
			enum class D_ENUM eBufferParameter
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
			*/
		};
	}
}