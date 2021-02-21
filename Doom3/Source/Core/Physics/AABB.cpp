#include "AABB.h"

using namespace doom::physics;

bool doom::physics::AABB2D::IsValid()
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

void doom::physics::AABB2D::Render()
{

}

bool doom::physics::AABB3D::IsValid()
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
		D_DEBUG_LOG("AABB bound is worng");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}

	if (mUpperBound.z < mLowerBound.z)
	{
		float temp = mLowerBound.z;
		mLowerBound.z = mUpperBound.z;
		mUpperBound.z = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}
}


doom::physics::AABB2D doom::physics::AABB2D::Union(const AABB2D& A, const AABB2D& B)
{
	return AABB2D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
}

doom::physics::AABB3D doom::physics::AABB3D::Union(const AABB3D& A, const AABB3D& B)
{
	return AABB3D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
}

/// <summary>
/// ºÎÇÇ
/// </summary>
/// <param name="A"></param>
/// <returns></returns>
float doom::physics::AABB3D::GetArea(const AABB3D& A)
{
	math::Vector3 d = A.mUpperBound - A.mLowerBound;
	return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
}

float doom::physics::AABB2D::GetArea(const AABB2D& A)
{
	math::Vector2 d = A.mUpperBound - A.mLowerBound;
	return d.x * d.y;
}

bool doom::physics::AABB2D::IsOverlap(const math::Vector2& Point)
{
	return (Point.x >= this->mLowerBound.x && Point.x <= this->mUpperBound.x) &&
		(Point.y >= this->mLowerBound.y && Point.y <= this->mUpperBound.y);
}

bool doom::physics::AABB2D::IsOverlap(const AABB2D& B)
{
	return this->mUpperBound.x > B.mLowerBound.x && this->mLowerBound.x < B.mUpperBound.x&&
		this->mUpperBound.y  > B.mLowerBound.y && this->mLowerBound.y < B.mUpperBound.y;
}

bool doom::physics::AABB3D::IsOverlap(const math::Vector3& Point)
{
	return (Point.x >= this->mLowerBound.x && Point.x <= this->mUpperBound.x) &&
		(Point.y >= this->mLowerBound.y && Point.y <= this->mUpperBound.y) &&
		(Point.z >= this->mLowerBound.z && Point.z <= this->mUpperBound.z);
}

bool doom::physics::AABB3D::IsOverlap(const AABB3D& B)
{
	return (this->mLowerBound.x <= B.mUpperBound.x && this->mUpperBound.x >= B.mLowerBound.x) &&
		(this->mLowerBound.y <= B.mUpperBound.y && this->mUpperBound.y >= B.mLowerBound.y) &&
		(this->mLowerBound.z <= B.mUpperBound.z && this->mUpperBound.z >= B.mLowerBound.z);
}

math::Vector2 doom::physics::AABB2D::ClosestPointToPoint(const math::Vector2& point)
{
	math::Vector2 result{};
	if (this->mLowerBound.x > point.x)
	{
		result.x = this->mLowerBound.x;
	}
	else if (this->mUpperBound.x < point.x)
	{
		result.x = this->mUpperBound.x;
	}
	else
	{
		result.x = point.x;
	}

	if (this->mLowerBound.y > point.y)
	{
		result.y = this->mLowerBound.y;
	}
	else if (this->mUpperBound.y < point.y)
	{
		result.y = this->mUpperBound.y;
	}
	else
	{
		result.y = point.y;
	}

	return result;
}

math::Vector3 doom::physics::AABB3D::ClosestPointToPoint(const math::Vector3& point)
{
	math::Vector3 result{};
	if (this->mLowerBound.x > point.x)
	{
		result.x = this->mLowerBound.x;
	}
	else if (this->mUpperBound.x < point.x)
	{
		result.x = this->mUpperBound.x;
	}
	else
	{
		result.x = point.x;
	}

	if (this->mLowerBound.y > point.y)
	{
		result.y = this->mLowerBound.y;
	}
	else if (this->mUpperBound.y < point.y)
	{
		result.y = this->mUpperBound.y;
	}
	else
	{
		result.y = point.y;
	}


	if (this->mLowerBound.z > point.z)
	{
		result.z = this->mLowerBound.z;
	}
	else if (this->mUpperBound.z < point.z)
	{
		result.z = this->mUpperBound.z;
	}
	else
	{
		result.z = point.z;
	}

	return result;
}

float doom::physics::AABB3D::Raycast(Ray ray, AABB3D aabb) {
	auto normal = ray.GetNormal();

	float t1 = (aabb.mLowerBound.x - ray.mPosition.x) / normal.x;
	float t2 = (aabb.mUpperBound.x - ray.mPosition.x) / normal.x;
	float t3 = (aabb.mLowerBound.y - ray.mPosition.y) / normal.y;
	float t4 = (aabb.mUpperBound.y - ray.mPosition.y) / normal.y;
	float t5 = (aabb.mLowerBound.z - ray.mPosition.z) / normal.z;
	float t6 = (aabb.mUpperBound.z - ray.mPosition.z) / normal.z;

	float tmin = math::max(math::max(math::min(t1, t2), math::min(t3, t4)), math::min(t5, t6));
	float tmax = math::min(math::min(math::max(t1, t2), math::max(t3, t4)), math::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0) {
		return -1;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return -1;
	}

	if (tmin < 0.0f) {
		return tmax;
	}
	return tmin;
}

