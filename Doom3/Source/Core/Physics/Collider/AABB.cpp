
#include "AABB.h"

#include "../Physics_Server.h"
#include "../Graphics/DebugGraphics.h"

#include "Ray.h"
#include <Matrix4x4.h>

//#include <Trigonometric.h>

using namespace doom::physics;


doom::physics::AABB2D& AABB2D::operator=(const AABB3D& aabb3D)
{
	mLowerBound = aabb3D.mLowerBound;
	mUpperBound = aabb3D.mUpperBound;
	return *this;
}

bool AABB2D::IsValid() const
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y;
}

void AABB2D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		float temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG("AABB bound is worng", eLogType::D_ERROR);
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is worng", eLogType::D_ERROR);
	}
}

math::Vector2 doom::physics::AABB2D::GetHalfExtent() const
{
	return (mUpperBound + mLowerBound) * 0.5f;
}

void doom::physics::AABB2D::Render(eColor color, bool drawInstantly /*= false*/)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 x{ mUpperBound.x - mLowerBound.x, 0, 0 };
	math::Vector3 y{ 0, mUpperBound.y - mLowerBound.y, 0 };

	debugGraphics->DebugDraw2DLine(mLowerBound, mLowerBound + x, color, drawInstantly);
	debugGraphics->DebugDraw2DLine(mLowerBound, mLowerBound + y, color, drawInstantly);
	debugGraphics->DebugDraw2DLine(mLowerBound + x, mLowerBound + x + y, color, drawInstantly);
	debugGraphics->DebugDraw2DLine(mLowerBound + y, mLowerBound + y + x, color, drawInstantly);
}



doom::physics::ColliderType doom::physics::AABB2D::GetColliderType() const
{
	return doom::physics::ColliderType::AABB2D;
}



AABB2D AABB2D::EnlargeAABB(const AABB2D& aabb)
{
	float offset = doom::physics::Physics_Server::GetSingleton()->ENLARGED_AABB2D_OFFSET;
	return AABB2D(aabb.mLowerBound - offset, aabb.mUpperBound + offset);
}

bool AABB3D::IsValid() const
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y && mUpperBound.z > mLowerBound.z;
}

void AABB3D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		float temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG("AABB bound is wrong", eLogType::D_ERROR);
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is wrong", eLogType::D_ERROR);
	}

	if (mUpperBound.z < mLowerBound.z)
	{
		float temp = mLowerBound.z;
		mLowerBound.z = mUpperBound.z;
		mUpperBound.z = temp;
		D_DEBUG_LOG("AABB bound is wrong", eLogType::D_ERROR);
	}
}

math::Vector3 doom::physics::AABB3D::GetHalfExtent() const
{
	return (mUpperBound - mLowerBound) * 0.5f;
}


float AABB3D::GetDiagonarLineLength() const
{
	auto halfExtent = GetHalfExtent();
	return math::sqrt(halfExtent.x * halfExtent.x + halfExtent.y * halfExtent.y + halfExtent.z * halfExtent.z);
}

void doom::physics::AABB3D::Render(eColor color, bool drawInstantly /*= false*/)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 x{ mUpperBound.x - mLowerBound.x, 0, 0 };
	math::Vector3 y{ 0, mUpperBound.y - mLowerBound.y, 0 };
	math::Vector3 z{ 0, 0, mUpperBound.z - mLowerBound.z };

	debugGraphics->DebugDraw3DLine(mLowerBound, mLowerBound + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound, mLowerBound + y, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound, mLowerBound + z, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(mLowerBound + x, mLowerBound + x + y, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound + x, mLowerBound + x + z, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(mLowerBound + y, mLowerBound + y + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound + y, mLowerBound + y + z, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(mLowerBound + z, mLowerBound + z + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound + z, mLowerBound + z + y, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(mLowerBound + x + y, mLowerBound + x + y + z, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound + y + z, mLowerBound + y + z + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(mLowerBound + x + z, mLowerBound + x + z + y, color, drawInstantly);

}

void doom::physics::AABB3D::Render2DTopView(eColor color, bool drawInstantly /*= false*/)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 lower{ mLowerBound.x, mLowerBound.z, 0.0f };
	math::Vector3 width{ mUpperBound.x - mLowerBound.x, 0.0f, 0.0f };
	math::Vector3 height{ 0.0f, mUpperBound.z - mLowerBound.z, 0.0f };

	debugGraphics->DebugDraw2DLine(lower, lower + width, color, drawInstantly);
	debugGraphics->DebugDraw2DLine(lower + width, lower + width + height, color, drawInstantly);
	debugGraphics->DebugDraw2DLine(lower , lower + height, color, drawInstantly);
	debugGraphics->DebugDraw2DLine(lower + height, lower + width + height, color, drawInstantly);
}

doom::physics::ColliderType doom::physics::AABB3D::GetColliderType() const
{
	return doom::physics::ColliderType::AABB3D;
}


AABB3D AABB3D::EnlargeAABB(const AABB3D& aabb)
{
	float offset = doom::physics::Physics_Server::GetSingleton()->ENLARGED_AABB3D_OFFSET;
	return AABB3D(aabb.mLowerBound - offset, aabb.mUpperBound + offset);
}

void AABB3D::SignedExpand(const math::Vector3& movedVector)
{
	if (movedVector.x > 0)
	{
		mUpperBound.x += movedVector.x;
	}
	else
	{
		mLowerBound.x += movedVector.x;
	}


	if (movedVector.y > 0)
	{
		mUpperBound.y += movedVector.y;
	}
	else
	{
		mLowerBound.y += movedVector.y;
	}


	if (movedVector.z > 0)
	{
		mUpperBound.z += movedVector.z;
	}
	else
	{
		mLowerBound.z += movedVector.z;
	}
}

void AABB3D::Expand(const math::Vector3& movedVector)
{
	math::Vector3 expandVec{ math::abs(movedVector.x) ,  math::abs(movedVector.y) ,  math::abs(movedVector.z) };
	mUpperBound += expandVec;
	mLowerBound -= expandVec;
}


////////////////////////////////////////





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

