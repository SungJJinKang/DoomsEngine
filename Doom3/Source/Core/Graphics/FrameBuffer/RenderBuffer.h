#pragma once

#include <Core.h>

#include "../GraphicsAPI.h"
#include "../OverlapBindChecker.h"
#include "../Buffer/BufferID.h"
#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/Stage/BinTrianglesStage.h"

namespace doom
{
	namespace graphics
	{
		class FrameBuffer;

		class RenderBuffer : public DObject
		{
			DOBJECT_CLASS_BODY(RenderBuffer, doom::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

		private:

			static inline const char RENDERBUFFER_TAG[]{ "RenderBuffer" };
			BufferID mRenderBufferID{};

			GraphicsAPI::eBufferBitType mFrameBufferType;
			UINT32 mWidth;
			UINT32 mHeight;
			
		public:

			

			RenderBuffer();
			RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height);
			virtual ~RenderBuffer();

			RenderBuffer(const RenderBuffer&) = delete;
			RenderBuffer& operator=(const RenderBuffer&) noexcept = delete;

			RenderBuffer(RenderBuffer&&) noexcept = default;
			RenderBuffer& operator=(RenderBuffer &&) noexcept = default;


			bool CreateRenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height);
			void DeleteRenderBuffers();
			
			FORCE_INLINE static void BindRenderBuffer(INT32 renderBufferID)
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(RENDERBUFFER_TAG, renderBufferID))
				{
					glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
				}
			}

			FORCE_INLINE void BindRenderBuffer() const noexcept
			{
				BindRenderBuffer(mRenderBufferID);
			}
			FORCE_INLINE static void UnBindRenderBuffer() noexcept
			{
				BindRenderBuffer(0);
			}

			FORCE_INLINE GraphicsAPI::eBufferBitType GetFrameBufferType() const
			{
				return mFrameBufferType;
			}
			FORCE_INLINE UINT32 GetWidth() const
			{
				return mWidth;
			}
			FORCE_INLINE UINT32 GetHeight() const
			{
				return mHeight;
			}
		};
	}
}

