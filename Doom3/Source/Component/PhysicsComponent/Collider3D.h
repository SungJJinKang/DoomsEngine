#pragma once
#include "Collider.h"
#include "Vector3.h"
namespace doom
{
	class Collider3D : public Collider
	{
	protected:
		math::Vector3 mOffset;

	public:
		void SetOffset(const math::Vector3& offset);
		math::Vector3 GetOffset();
	};
}
