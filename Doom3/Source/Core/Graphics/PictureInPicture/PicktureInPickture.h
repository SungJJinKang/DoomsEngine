#pragma once

#include "../Buffer/Mesh.h"
#include "../Material/Material.h"

#include <Vector2.h>


namespace dooms
{
	namespace graphics
	{
		class SingleTexture;

		class DOOM_API D_CLASS PicktureInPickture : public DObject
		{

			DOBJECT_CLASS_BODY(PicktureInPickture, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

		private:

			static inline Material mDefualtPIPMaterial{ nullptr };
			Material* mPIPMaterial = nullptr;

			Mesh mPlaneMesh;
			SingleTexture* mDrawedTexture;

			void InitializeDefaultPIPMaterial();

		public:

			bool bmIsDrawOnScreen;

			PicktureInPickture();
			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial);
			//PicktureInPickture& operator=(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			//PicktureInPickture& operator=(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial);

			void SetDefaultPIPMaterial();

			~PicktureInPickture();

			void SetTexture(SingleTexture* const texture);
			void SetMaterial(Material* const _pipMaterial);

			void DrawPictureInPicture();


		};

	}
}
