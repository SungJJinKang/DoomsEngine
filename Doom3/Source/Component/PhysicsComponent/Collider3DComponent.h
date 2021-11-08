#pragma once
#include "ColliderComponent.h"
#include "Vector3.h"
namespace dooms
{
	class DOOM_API D_CLASS Collider3DComponent : public ColliderComponent
	{
		DOBJECT_ABSTRACT_CLASS_BODY(Collider3DComponent)
		DOBJECT_CLASS_BASE_CHAIN(ColliderComponent)

	protected:
		math::Vector3 mOffset;

		virtual math::Vector3 GetOffsetVector3() const final;

	public:

		virtual ~Collider3DComponent();

		void SetOffset(const math::Vector3& offset);
		math::Vector3 GetOffset();
	};
}
