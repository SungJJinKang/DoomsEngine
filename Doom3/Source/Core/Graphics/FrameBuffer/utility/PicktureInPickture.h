#pragma once

#include "../FrameBuffer.h"
#include "../../Buffer/Mesh.h"
#include "../../Material.h"

#include <Vector2.h>

namespace doom
{
	namespace graphics
	{
		class PicktureInPickture
		{
		private:

			static inline Material mPIPMaterial{};

			Mesh mPlaneMesh;
			SingleTexture* mDrawedTexture;

		public:

			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);

			void SetTexture(SingleTexture* const texture);

			void DrawPictureInPicture();


		};

	}
}
