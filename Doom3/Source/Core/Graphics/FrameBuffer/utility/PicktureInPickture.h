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

			Mesh mMesh;
			FrameBuffer mFrameBuffer;
			SingleTexture* mScreenTexture;

		public:
			/// <summary>
			/// ratio between TxtureWidth and Height should equal to ratio between two NDCPoint
			/// </summary>
			/// <param name="TextureWidth"></param>
			/// <param name="TextureHeight"></param>
			/// <param name="leftBottonNDCPoint">-1 ~ 1</param>
			/// <param name="rightTopNDCPoint">-1 ~ 1</param>
			PicktureInPickture(int textureWidth, int textureHeight, const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint);

			void BindFrameBuffer();
			void UnBindFrameBuffer();
			void RevertFrameBuffer();

			void DrawPictureInPicture();

			void ClearFrameBuffer();

		};

	}
}
