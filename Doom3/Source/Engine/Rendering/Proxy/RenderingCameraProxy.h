#pragma once

#include <Core.h>

#include "RenderingProxy.h"
#include <Rendering/Enum/eProjectionType.h>

#include "Vector4.h"

namespace dooms
{
	namespace graphics
	{
		class RenderingCameraProxy : public RenderingProxy
		{

		public:
			
				graphics::eProjectionType mProjectionMode{ graphics::eProjectionType::Perspective };
			
				FLOAT32 mFieldOfViewInDegree = 60;
			
				FLOAT32 mClippingPlaneNear = 0.001f;
			
				FLOAT32 mClippingPlaneFar = 3000.0f;

				/// <summary>
				/// opengl -1 ~ 1
				/// </summary>
				FLOAT32 mViewportRectX = 0.0f;

				/// <summary>
				/// opengl -1 ~ 1
				/// </summary>
				FLOAT32 mViewportRectY = 0.0f;

				/// <summary>
				/// opengl -1 ~ 1
				/// </summary>
				FLOAT32 mViewportRectWidth = 1920.0f;

				// <summary>
				/// opengl -1 ~ 1
				/// </summary>
				FLOAT32 mViewportRectHeight = 1080.0f;
				
				math::Vector4 mClearColor;
				
				UINT32 CameraIndexInCullingSystem;
				
				UINT32 mCameraFlag;

		private:


		};
	}
}

