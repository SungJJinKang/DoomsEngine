#pragma once
#include "ColliderComponent.h"

#include "Vector2.h"

#include "Collider2DComponent.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS Collider2DComponent : public ColliderComponent
	{
		GENERATE_BODY()
		

	protected:
		math::Vector2 mOffset{0.0f};

		virtual math::Vector3 GetOffsetVector3() const final;

	public:
		void SetOffset(const math::Vector2& offset);
		math::Vector2 GetOffset();
	};
}
