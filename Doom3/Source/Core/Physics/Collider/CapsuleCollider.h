#pragma once
#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class DOOM_API CapsuleCollider : public Collider
		{

		public:

			math::Vector3 mCenter;
			float mHeight;
			float mRadius;

			FORCE_INLINE virtual void* data() final
			{
				return &(mCenter);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mCenter);
			}

			CapsuleCollider(const math::Vector3& center, float height, float radius);

			ColliderType GetColliderType() const override;

			void DrawCollider(eColor color, bool drawInstantly = false) const override;

		};

	
	}
}