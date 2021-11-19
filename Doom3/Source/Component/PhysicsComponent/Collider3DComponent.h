#pragma once
#include "ColliderComponent.h"
#include "Vector3.h"

#include "Collider3DComponent.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS Collider3DComponent : public ColliderComponent
	{
		GENERATE_BODY()
		

	protected:
		math::Vector3 mOffset {0.0f};

		virtual math::Vector3 GetOffsetVector3() const final;

	public:

		virtual ~Collider3DComponent();

		void SetOffset(const math::Vector3& offset);
		math::Vector3 GetOffset();
	};
}
