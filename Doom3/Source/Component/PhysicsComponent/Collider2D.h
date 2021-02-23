#pragma once
#include "Collider.h"
#include "Vector2.h"
namespace doom
{
	class Collider2D : public Collider
	{
	protected:
		math::Vector2 mOffset;

	public:
		void SetOffset(const math::Vector2& offset);
		math::Vector2 GetOffset();
	};
}
