#pragma once
#include "ColliderComponent.h"
#include "Vector3.h"
namespace doom
{
	class DOOM_API Collider3DComponent : public ColliderComponent
	{
	protected:
		math::Vector3 mOffset;

		virtual math::Vector3 GetOffsetVector3() const final;

	public:
		void SetOffset(const math::Vector3& offset);
		math::Vector3 GetOffset();
	};
}
