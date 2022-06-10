#pragma once

#include <Core.h>

#include <array>

#include "Rendering/MaxCameraCount.h"

namespace dooms
{
	namespace graphics
	{
		struct FDistanceToCameraData
		{
			std::array<FLOAT32, MAX_CAMERA_COUNT> DistancesToCamera;
		};

		class RenderingPrimitiveProxy
		{
		public:

		private:

			bool bIsRendered = true;

			bool bIsBatched = false;

			FDistanceToCameraData DistanceToCameraData;
		};
	}
}

