#pragma once
#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
namespace dooms
{
	namespace physics
	{
		class DOOM_API D_CLASS CapsuleCollider : public Collider
		{

		public:

			math::Vector3 mCenter;
			FLOAT32 mHeight;
			FLOAT32 mRadius;

			FORCE_INLINE virtual void* data() final
			{
				return &(mCenter);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mCenter);
			}

			CapsuleCollider() = default;
			CapsuleCollider(const math::Vector3& center, FLOAT32 height, FLOAT32 radius);

			ColliderType GetColliderType() const override;

			void DrawCollider(eColor color, bool drawInstantly = false) const override;

		};

	
	}
}