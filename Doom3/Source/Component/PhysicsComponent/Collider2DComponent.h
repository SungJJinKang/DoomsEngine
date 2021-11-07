#pragma once
#include "ColliderComponent.h"

#include "Vector2.h"
namespace dooms
{
	class DOOM_API Collider2DComponent : public ColliderComponent
	{
		DOBJECT_ABSTRACT_CLASS_BODY(Collider2DComponent)
		DOBJECT_CLASS_BASE_CHAIN(ColliderComponent)

	protected:
		math::Vector2 mOffset;

		virtual math::Vector3 GetOffsetVector3() const final;

	public:
		void SetOffset(const math::Vector2& offset);
		math::Vector2 GetOffset();
	};
}
