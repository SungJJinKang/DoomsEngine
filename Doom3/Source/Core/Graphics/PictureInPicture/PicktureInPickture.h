#pragma once

#include <string>

#include "../Buffer/Mesh.h"
#include "../Material/Material.h"

#include <Vector2.h>


namespace doom
{
	namespace graphics
	{
		class SingleTexture;

		class PicktureInPickture
		{

		private:

			static inline Material mDefualtPIPMaterial{ nullptr };
			Material* mPIPMaterial;

			Mesh mPlaneMesh;
			SingleTexture* mDrawedTexture;

			void InitializeDefaultPIPMaterial();

		public:

			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial);

			

			~PicktureInPickture();

			void SetTexture(SingleTexture* const texture);
			void SetMaterial(Material* const _pipMaterial);

			void DrawPictureInPicture();


		};

	}
}
