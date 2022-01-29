#pragma once

#include "../Buffer/Mesh.h"
#include "../Material/Material.h"

#include <Vector2.h>

#include "PicktureInPickture.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS PicktureInPickture : public DObject
		{
			GENERATE_BODY()
			
			

		private:

			static inline Material mDefualtPIPMaterial{ };
			D_PROPERTY()
			Material* mPIPMaterial = nullptr;

			D_PROPERTY()
			Mesh* mPlaneMesh = nullptr;
			D_PROPERTY()
			TextureView* mDrawedTexture = nullptr;

			void InitializeDefaultPIPMaterial();

		public:

			bool bmIsDrawOnScreen;

			PicktureInPickture();
			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, TextureView* const _drawedTexture);
			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, TextureView* const _drawedTexture, Material* const _pipMaterial);
			//PicktureInPickture& operator=(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			//PicktureInPickture& operator=(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial);

			void SetDefaultPIPMaterial();

			~PicktureInPickture();

			void SetTexture(TextureView* const texture);
			void SetMaterial(Material* const _pipMaterial);

			void DrawPictureInPicture();


		};

	}
}
