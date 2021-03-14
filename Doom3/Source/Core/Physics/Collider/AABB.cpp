
#include "AABB.h"

#include "../Physics_Server.h"
#include "../Graphics/DebugGraphics.h"

#include "Ray.h"
#include <Matrix4x4.h>

//#include <Trigonometric.h>

using namespace doom::physics;


doom::physics::AABB2D& AABB2D::operator=(const AABB3D& aabb3D)
{
	this->mLowerBound = aabb3D.mLowerBound;
	this->mUpperBound = aabb3D.mUpperBound;
	return *this;
}

math::Vector2 doom::physics::AABB2D::GetHalfExtent() const
{
	return (this->mUpperBound + this->mLowerBound) * 0.5f;
}

void doom::physics::AABB2D::Render(eColor color, bool drawInstantly /*= false*/)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 x{ this->mUpperBound.x - this->mLowerBound.x, 0, 0 };
	math::Vector3 y{ 0, this->mUpperBound.y - this->mLowerBound.y, 0 };

	debugGraphics->DebugDraw2DLine(this->mLowerBound, this->mLowerBound + x, color, false, drawInstantly);
	debugGraphics->DebugDraw2DLine(this->mLowerBound, this->mLowerBound + y, color, false, drawInstantly);
	debugGraphics->DebugDraw2DLine(this->mLowerBound + x, this->mLowerBound + x + y, color, false, drawInstantly);
	debugGraphics->DebugDraw2DLine(this->mLowerBound + y, this->mLowerBound + y + x, color, false, drawInstantly);

}



doom::physics::ColliderType doom::physics::AABB2D::GetColliderType() const
{
	return doom::physics::ColliderType::AABB2D;
}

math::Vector2 AABB2D::GetCenter() const
{
	return (this->mLowerBound + this->mUpperBound) / 2;
}

AABB2D doom::physics::AABB2D::EnlargeAABB(const AABB2D& aabb)
{
	float offset = doom::physics::Physics_Server::GetSingleton()->ENLARGED_AABB2D_OFFSET;
	return AABB2D(aabb.mLowerBound - offset, aabb.mUpperBound + offset);
}

math::Vector3 doom::physics::AABB3D::GetHalfExtent() const
{
	return (this->mUpperBound - this->mLowerBound) * 0.5f;
}


float AABB3D::GetDiagonarLineLength() const
{
	auto halfExtent = this->GetHalfExtent();
	return math::sqrt(halfExtent.x * halfExtent.x + halfExtent.y * halfExtent.y + halfExtent.z * halfExtent.z);
}

void doom::physics::AABB3D::Render(eColor color, bool drawInstantly /*= false*/)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 x{ this->mUpperBound.x - this->mLowerBound.x, 0, 0 };
	math::Vector3 y{ 0, this->mUpperBound.y - this->mLowerBound.y, 0 };
	math::Vector3 z{ 0, 0, this->mUpperBound.z - this->mLowerBound.z };

	debugGraphics->DebugDraw3DLine(this->mLowerBound, this->mLowerBound + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound, this->mLowerBound + y, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound, this->mLowerBound + z, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + x, this->mLowerBound + x + y, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + x, this->mLowerBound + x + z, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + y, this->mLowerBound + y + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + y, this->mLowerBound + y + z, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + z, this->mLowerBound + z + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + z, this->mLowerBound + z + y, color, drawInstantly);

	debugGraphics->DebugDraw3DLine(this->mLowerBound + x + y, this->mLowerBound + x + y + z, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + y + z, this->mLowerBound + y + z + x, color, drawInstantly);
	debugGraphics->DebugDraw3DLine(this->mLowerBound + x + z, this->mLowerBound + x + z + y, color, drawInstantly);
}

void doom::physics::AABB3D::Render2DTopView(eColor color, bool drawInstantly /*= false*/)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 lower{ this->mLowerBound.x, this->mLowerBound.z, 0.0f };
	math::Vector3 width{ this->mUpperBound.x - this->mLowerBound.x, 0.0f, 0.0f };
	math::Vector3 height{ 0.0f, this->mUpperBound.z - this->mLowerBound.z, 0.0f };

	debugGraphics->DebugDraw2DLine(lower, lower + width, color, false, drawInstantly);
	debugGraphics->DebugDraw2DLine(lower + width, lower + width + height, color, false, drawInstantly);
	debugGraphics->DebugDraw2DLine(lower , lower + height, color, false, drawInstantly);
	debugGraphics->DebugDraw2DLine(lower + height, lower + width + height, color, false, drawInstantly);
}

doom::physics::ColliderType doom::physics::AABB3D::GetColliderType() const
{
	return doom::physics::ColliderType::AABB3D;
}

math::Vector3 doom::physics::AABB3D::GetCenter() const
{
	return (this->mLowerBound + this->mUpperBound) / 2;
}

AABB3D doom::physics::AABB3D::EnlargeAABB(const AABB3D& aabb)
{
	float offset = doom::physics::Physics_Server::GetSingleton()->ENLARGED_AABB3D_OFFSET;
	return AABB3D(aabb.mLowerBound - offset, aabb.mUpperBound + offset);
}



////////////////////////////////////////


bool doom::physics::CheckIsAABBCompletlyEnclosed(const AABB2D& innerAABB, const AABB2D& outerAABB)
{
	return innerAABB.mLowerBound.x >= outerAABB.mLowerBound.x &&
		innerAABB.mLowerBound.y >= outerAABB.mLowerBound.y &&
		innerAABB.mUpperBound.x <= outerAABB.mUpperBound.x &&
		innerAABB.mUpperBound.y <= outerAABB.mUpperBound.y;
}

bool doom::physics::IsOverlapAABB2DAndPoint(const AABB2D& aabb, const math::Vector2& Point)
{
	return (Point.x >= aabb.mLowerBound.x && Point.x <= aabb.mUpperBound.x) &&
		(Point.y >= aabb.mLowerBound.y && Point.y <= aabb.mUpperBound.y);
}

bool doom::physics::IsOverlapAABB2DAndAABB2D(const AABB2D& aabb, const AABB2D& B)
{
	return aabb.mUpperBound.x > B.mLowerBound.x && aabb.mLowerBound.x < B.mUpperBound.x&&
		aabb.mUpperBound.y  > B.mLowerBound.y && aabb.mLowerBound.y < B.mUpperBound.y;
}

bool doom::physics::IsOverlapAABB2DAndAABB2D(Collider* aabb, Collider* B)
{
	return IsOverlapAABB2DAndAABB2D(*static_cast<AABB2D*>(aabb), *static_cast<AABB2D*>(B));
}

bool doom::physics::CheckIsAABBCompletlyEnclosed(const AABB3D& innerAABB, const AABB3D& outerAABB)
{
	return innerAABB.mLowerBound.x >= outerAABB.mLowerBound.x &&
		innerAABB.mLowerBound.y >= outerAABB.mLowerBound.y &&
		innerAABB.mLowerBound.z >= outerAABB.mLowerBound.z &&
		innerAABB.mUpperBound.x <= outerAABB.mUpperBound.x &&
		innerAABB.mUpperBound.y <= outerAABB.mUpperBound.y &&
		innerAABB.mUpperBound.z <= outerAABB.mUpperBound.z;
}

bool doom::physics::IsOverlapAABB3DAndPoint(const AABB3D& aabb, const math::Vector3& Point)
{
	return (Point.x >= aabb.mLowerBound.x && Point.x <= aabb.mUpperBound.x) &&
		(Point.y >= aabb.mLowerBound.y && Point.y <= aabb.mUpperBound.y) &&
		(Point.z >= aabb.mLowerBound.z && Point.z <= aabb.mUpperBound.z);
}

bool doom::physics::IsOverlapAABB3DAndAABB3D(const AABB3D& aabb, const AABB3D& B)
{
	return (aabb.mLowerBound.x <= B.mUpperBound.x && aabb.mUpperBound.x >= B.mLowerBound.x) &&
		(aabb.mLowerBound.y <= B.mUpperBound.y && aabb.mUpperBound.y >= B.mLowerBound.y) &&
		(aabb.mLowerBound.z <= B.mUpperBound.z && aabb.mUpperBound.z >= B.mLowerBound.z);
}

bool doom::physics::IsOverlapAABB3DAndAABB3D(Collider* aabb, Collider* B)
{
	return IsOverlapAABB3DAndAABB3D(*static_cast<AABB3D*>(aabb), *static_cast<AABB3D*>(B));
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

// this function is not tested
void doom::physics::ApplyModelMatrixToAABB(const AABB2D& localAABB, const math::Matrix4x4& modelMatrix, AABB2D& resultAABB)
{
	for (int i = 0; i < 2; i++)
	{
		resultAABB.mLowerBound[i] = resultAABB.mUpperBound[i] = modelMatrix[3][i];

		for (int j = 0; j < 2; j++)
		{
			float e = modelMatrix[i][j] * localAABB.mLowerBound[j];
			float f = modelMatrix[i][j] * localAABB.mUpperBound[j];
			if (e < f)
			{
				resultAABB.mLowerBound[i] += e;
				resultAABB.mUpperBound[i] += f;
			}
			else
			{
				resultAABB.mLowerBound[i] += f;
				resultAABB.mUpperBound[i] += e;
			}
		}
	}
}

void doom::physics::ApplyModelMatrixToAABB(const AABB3D& localAABB, const math::Matrix4x4& modelMatrix, AABB3D& resultAABB)
{
	for (int i = 0; i < 3; i++)
	{
		resultAABB.mLowerBound[i] = resultAABB.mUpperBound[i] = modelMatrix[3][i];

		for (int j = 0; j < 3; j++)
		{
			float e = modelMatrix[i][j] * localAABB.mLowerBound[j];
			float f = modelMatrix[i][j] * localAABB.mUpperBound[j];
			if (e < f)
			{
				resultAABB.mLowerBound[i] += e;
				resultAABB.mUpperBound[i] += f;
			}
			else
			{
				resultAABB.mLowerBound[i] += f;
				resultAABB.mUpperBound[i] += e;
			}
		}
	}
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

