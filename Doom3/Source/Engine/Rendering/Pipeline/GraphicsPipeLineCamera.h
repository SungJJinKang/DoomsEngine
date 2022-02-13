#pragma once

#include <Core.h>

#include "GraphicsPipeLineCamera.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class FrameBuffer;
		class D_CLASS GraphicsPipeLineCamera : public DObject
		{
			GENERATE_BODY()

		private:

		public:

			GraphicsPipeLineCamera();

			virtual FrameBuffer* GetCameraFrameBuffer() = 0;
		};
	}
}

