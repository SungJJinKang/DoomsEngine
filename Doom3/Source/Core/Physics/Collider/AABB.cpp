#include "AABB.h"
#include "../Graphics/DebugGraphics.h"

//#include <Trigonometric.h>

using namespace doom::physics;

AABB2D::AABB2D(const AABB3D& aabb3D)
{
	this->mLowerBound = aabb3D.mLowerBound;
	this->mUpperBound = aabb3D.mUpperBound;
}

doom::physics::AABB2D& AABB2D::operator=(const AABB3D& aabb3D)
{
	this->mLowerBound = aabb3D.mLowerBound;
	this->mUpperBound = aabb3D.mUpperBound;
	return *this;
}

bool doom::physics::AABB2D::IsValid() const
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y;
}

void doom::physics::AABB2D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		float temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}
}

math::Vector2 doom::physics::AABB2D::GetHalfExtent() const
{
	return (this->mUpperBound + this->mLowerBound) * 0.5f;
}

void doom::physics::AABB2D::Render(eColor color)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 x{ this->mUpperBound.x - this->mLowerBound.x, 0, 0 };
	math::Vector3 y{ 0, this->mUpperBound.y - this->mLowerBound.y, 0 };

	debugGraphics->DebugDraw2DLine(this->mLowerBound, this->mLowerBound + x, color);
	debugGraphics->DebugDraw2DLine(this->mLowerBound, this->mLowerBound + y, color);
	debugGraphics->DebugDraw2DLine(this->mLowerBound + x, this->mLowerBound + x + y, color);
	debugGraphics->DebugDraw2DLine(this->mLowerBound + y, this->mLowerBound + y + x, color);

}



doom::physics::ColliderType doom::physics::AABB2D::GetColliderType() const
{
	return doom::physics::ColliderType::AABB2D;
}

bool doom::physics::AABB3D::IsValid() const
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y && mUpperBound.z > mLowerBound.z;
}

void doom::physics::AABB3D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		float temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG("AABB bound is wrong");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is wrong");
	}

	if (mUpperBound.z < mLowerBound.z)
	{
		float temp = mLowerBound.z;
		mLowerBound.z = mUpperBound.z;
		mUpperBound.z = temp;
		D_DEBUG_LOG("AABB bound is wrong");
	}
}

math::Vector3 doom::physics::AABB3D::GetHalfExtent() const
{
	return (this->mUpperBound - this->mLowerBound) * 0.5f;
}


float AABB3D::GetDiagonarLineLength()
{
	auto halfExtent = this->GetHalfExtent();
	return math::sqrt(halfExtent.x * halfExtent.x + halfExtent.y * halfExtent.y + halfExtent.z * halfExtent.z);
}

void doom::physics::AABB3D::Render(eColor color)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 x{ this->mUpperBound.x - this->mLowerBound.x, 0, 0 };
	math::Vector3 y{ 0, this->mUpperBound.y - this->mLowerBound.y, 0 };
	math::Vector3 z{ 0, 0, this->mUpperBound.z - this->mLowerBound.z };

	debugGraphics->DebugDraw3DLine(this->mLowerBound, this->mLowerBound + x, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound, this->mLowerBound + y, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound, this->mLowerBound + z, color);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + x, this->mLowerBound + x + y, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + x, this->mLowerBound + x + z, color);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + y, this->mLowerBound + y + x, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + y, this->mLowerBound + y + z, color);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + z, this->mLowerBound + z + x, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + z, this->mLowerBound + z + y, color);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + x + y, this->mLowerBound + x + y + z, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + y + z, this->mLowerBound + y + z + x, color);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + x + z, this->mLowerBound + x + z + y, color);
}

doom::physics::ColliderType doom::physics::AABB3D::GetColliderType() const
{
	return doom::physics::ColliderType::AABB3D;
}

doom::physics::AABB2D doom::physics::Union(const AABB2D& A, const AABB2D& B)
{
	return AABB2D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
}

doom::physics::AABB3D doom::physics::Union(const AABB3D& A, const AABB3D& B)
{
	return AABB3D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
}

/// <summary>
/// ºÎÇÇ
/// </summary>
/// <param name="A"></param>
/// <returns></returns>
float doom::physics::GetArea(const AABB3D& A)
{
	math::Vector3 d = A.mUpperBound - A.mLowerBound;
	return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
}

float doom::physics::GetArea(const AABB2D& A)
{
	math::Vector2 d = A.mUpperBound - A.mLowerBound;
	return d.x * d.y;
}

bool doom::physics::IsOverlap(const AABB2D& aabb, const math::Vector2& Point)
{
	return (Point.x >= aabb.mLowerBound.x && Point.x <= aabb.mUpperBound.x) &&
		(Point.y >= aabb.mLowerBound.y && Point.y <= aabb.mUpperBound.y);
}

bool doom::physics::IsOverlap(const AABB2D& aabb, const AABB2D& B)
{
	return aabb.mUpperBound.x > B.mLowerBound.x && aabb.mLowerBound.x < B.mUpperBound.x&&
		aabb.mUpperBound.y  > B.mLowerBound.y && aabb.mLowerBound.y < B.mUpperBound.y;
}

bool doom::physics::IsOverlap(const AABB3D& aabb, const math::Vector3& Point)
{
	return (Point.x >= aabb.mLowerBound.x && Point.x <= aabb.mUpperBound.x) &&
		(Point.y >= aabb.mLowerBound.y && Point.y <= aabb.mUpperBound.y) &&
		(Point.z >= aabb.mLowerBound.z && Point.z <= aabb.mUpperBound.z);
}

bool doom::physics::IsOverlap(const AABB3D& aabb, const AABB3D& B)
{
	return (aabb.mLowerBound.x <= B.mUpperBound.x && aabb.mUpperBound.x >= B.mLowerBound.x) &&
		(aabb.mLowerBound.y <= B.mUpperBound.y && aabb.mUpperBound.y >= B.mLowerBound.y) &&
		(aabb.mLowerBound.z <= B.mUpperBound.z && aabb.mUpperBound.z >= B.mLowerBound.z);
}

math::Vector2 doom::physics::ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point)
{
	math::Vector2 result{};
	if (aabb.mLowerBound.x > point.x)
	{
		result.x = aabb.mLowerBound.x;
	}
	else if (aabb.mUpperBound.x < point.x)
	{
		result.x = aabb.mUpperBound.x;
	}
	else
	{
		result.x = point.x;
	}

	if (aabb.mLowerBound.y > point.y)
	{
		result.y = aabb.mLowerBound.y;
	}
	else if (aabb.mUpperBound.y < point.y)
	{
		result.y = aabb.mUpperBound.y;
	}
	else
	{
		result.y = point.y;
	}

	return result;
}

math::Vector3 doom::physics::ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point)
{
	math::Vector3 result{};
	if (aabb.mLowerBound.x > point.x)
	{
		result.x = aabb.mLowerBound.x;
	}
	else if (aabb.mUpperBound.x < point.x)
	{
		result.x = aabb.mUpperBound.x;
	}
	else
	{
		result.x = point.x;
	}

	if (aabb.mLowerBound.y > point.y)
	{
		result.y = aabb.mLowerBound.y;
	}
	else if (aabb.mUpperBound.y < point.y)
	{
		result.y = aabb.mUpperBound.y;
	}
	else
	{
		result.y = point.y;
	}


	if (aabb.mLowerBound.z > point.z)
	{
		result.z = aabb.mLowerBound.z;
	}
	else if (aabb.mUpperBound.z < point.z)
	{
		result.z = aabb.mUpperBound.z;
	}
	else
	{
		result.z = point.z;
	}

	return result;
}

