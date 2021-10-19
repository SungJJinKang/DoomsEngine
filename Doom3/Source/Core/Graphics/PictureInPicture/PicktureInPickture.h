#pragma once

#include "../Buffer/Mesh.h"
#include "../Material/Material.h"

#include <Vector2.h>


namespace doom
{
	namespace graphics
	{
		class SingleTexture;

		class PicktureInPickture : public DObject
		{

			DOBJECT_CLASS_BODY(PicktureInPickture, doom::eDOBJECT_ClassFlags::NonCopyable);

		private:

			static inline Material mDefualtPIPMaterial{ nullptr };
			Material* mPIPMaterial = nullptr;

			Mesh mPlaneMesh;
			SingleTexture* mDrawedTexture;

			void InitializeDefaultPIPMaterial();

		public:

			bool bmIsDrawOnScreen;

			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial);

			

			~PicktureInPickture();

			void SetTexture(SingleTexture* const texture);
			void SetMaterial(Material* const _pipMaterial);

			void DrawPictureInPicture();


		};

	}
}
