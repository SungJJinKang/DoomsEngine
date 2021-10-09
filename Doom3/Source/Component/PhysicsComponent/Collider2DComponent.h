#pragma once
#include "ColliderComponent.h"

#include "Vector2.h"
namespace doom
{
	class DOOM_API Collider2DComponent : public ColliderComponent
	{
	protected:
		math::Vector2 mOffset;

		virtual math::Vector3 GetOffsetVector3() const final;

	public:
		void SetOffset(const math::Vector2& offset);
		math::Vector2 GetOffset();
	};
}
