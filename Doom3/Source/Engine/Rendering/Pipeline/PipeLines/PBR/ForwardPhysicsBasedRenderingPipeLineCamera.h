#pragma once

#include <Core.h>

#include "../../GraphicsPipeLineCamera.h"

#include "ForwardPhysicsBasedRenderingPipeLineCamera.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS ForwardPhysicsBasedRenderingPipeLineCamera : public GraphicsPipeLineCamera
		{
			GENERATE_BODY()
		private:

		public:

			ForwardPhysicsBasedRenderingPipeLineCamera();

			FrameBuffer* GetCameraFrameBuffer() override;

		};
	}
}

