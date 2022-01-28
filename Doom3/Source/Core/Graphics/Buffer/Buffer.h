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
			
			void OnSetPendingKill() override;

		public:


			Buffer();
			virtual ~Buffer();

			Buffer(const Buffer&) = delete;
			Buffer& operator=(const Buffer&) noexcept = delete;

			Buffer(Buffer&& buffer) noexcept;
			Buffer& operator=(Buffer && buffer) noexcept;
			
			D_FUNCTION()
			virtual void BindBuffer() const noexcept = 0;

			D_FUNCTION()
			virtual void DeleteBuffers() = 0;

			D_FUNCTION()
			virtual bool IsBufferGenerated() const = 0;
		};
	}
}