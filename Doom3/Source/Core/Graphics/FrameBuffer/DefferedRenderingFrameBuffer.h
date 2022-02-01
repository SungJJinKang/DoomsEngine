#pragma once

#include <array>

#include "FrameBuffer.h"
#include <Vector4.h>

#include "DefferedRenderingFrameBuffer.reflection.h"
namespace dooms
{
	class Camera;
	namespace graphics
	{

		class DOOM_API D_CLASS DefferedRenderingFrameBuffer : public graphics::FrameBuffer
		{
			GENERATE_BODY()
			
			

		private:

			D_PROPERTY()
			std::array<TextureView*, 3> TextureViews;

		public:

			math::Vector4 mAlbedoClearColor{1.0f};

			DefferedRenderingFrameBuffer();

			void BlitDepthBufferToScreenBuffer();
			void BindGBufferTextures();
			void UnBindGBufferTextures();

			virtual void ClearFrameBuffer(const Camera* const camera) final;
		};

	}
}

