
#include "AABB.h"

#include "../Physics_Server.h"
#include <Rendering/RenderingDebugger/RenderingDebuggerModules/DebugDrawer.h>

#include "Ray.h"
#include <Matrix4x4.h>
#include "../Phycis_Core.h"

using namespace dooms::physics;


dooms::physics::AABB2D& AABB2D::operator=(const AABB3D& aabb3D)
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
		FLOAT32 temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG(eLogType::D_ERROR, "AABB bound is worng");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		FLOAT32 temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG(eLogType::D_ERROR, "AABB bound is worng");
	}
}

dooms::physics::AABB2D::component_type dooms::physics::AABB2D::GetHalfExtent() const
{
	return (mUpperBound + mLowerBound) * 0.5f;
}

void dooms::physics::AABB2D::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	const math::Vector3 x{ mUpperBound.x - mLowerBound.x, 0, 0 };
	const math::Vector3 y{ 0, mUpperBound.y - mLowerBound.y, 0 };

	debugGraphics->DebugDraw2DLine(math::Vector3{ mLowerBound }, static_cast<math::Vector3>(mLowerBound) + x, color);
	debugGraphics->DebugDraw2DLine(math::Vector3{ mLowerBound }, static_cast<math::Vector3>(mLowerBound) + y, color);
	debugGraphics->DebugDraw2DLine(static_cast<math::Vector3>(mLowerBound) + x, static_cast<math::Vector3>(mLowerBound) + x + y, color);
	debugGraphics->DebugDraw2DLine(static_cast<math::Vector3>(mLowerBound) + y, static_cast<math::Vector3>(mLowerBound) + y + x, color);
#endif
}



dooms::physics::ColliderType dooms::physics::AABB2D::GetColliderType() const
{
	return dooms::physics::ColliderType::AABB2D;
}

void dooms::physics::AABB2D::SignedExpand(const component_type& movedVector)
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
}



AABB2D AABB2D::EnlargeAABB(const AABB2D& aabb)
{
	const FLOAT32 offset = dooms::physics::Physics_Setting::ENLARGED_AABB2D_OFFSET;
	return AABB2D(aabb.mLowerBound - offset, aabb.mUpperBound + offset);
}

// this function is not tested

void dooms::physics::AABB2D::ApplyModelMatrix(const AABB2D& localAABB, const math::Matrix4x4& modelMatrix, AABB2D& resultAABB)
{
	for (INT32 i = 0; i < 2; i++)
	{
		resultAABB.mLowerBound[i] = resultAABB.mUpperBound[i] = modelMatrix[3][i];

		for (INT32 j = 0; j < 2; j++)
		{
			FLOAT32 e = modelMatrix[i][j] * localAABB.mLowerBound[j];
			FLOAT32 f = modelMatrix[i][j] * localAABB.mUpperBound[j];
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

/// <summary>
/// This is different with IsOverlap
/// This function check if innerAABB is completly enclosed by outerAABB
/// </summary>
/// <param name="innerAABB"></param>
/// <param name="outerAABB"></param>
/// <returns></returns>

bool dooms::physics::AABB2D::CheckIsCompletlyEnclosed(const AABB2D& innerAABB, const AABB2D& outerAABB)
{
	return innerAABB.mLowerBound.x >= outerAABB.mLowerBound.x &&
		innerAABB.mLowerBound.y >= outerAABB.mLowerBound.y &&
		innerAABB.mUpperBound.x <= outerAABB.mUpperBound.x &&
		innerAABB.mUpperBound.y <= outerAABB.mUpperBound.y;
}

bool AABB3D::IsValid() const
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y && mUpperBound.z > mLowerBound.z;
}

void AABB3D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		FLOAT32 temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG(eLogType::D_ERROR, "AABB bound is wrong");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		FLOAT32 temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG(eLogType::D_ERROR, "AABB bound is wrong");
	}

	if (mUpperBound.z < mLowerBound.z)
	{
		FLOAT32 temp = mLowerBound.z;
		mLowerBound.z = mUpperBound.z;
		mUpperBound.z = temp;
		D_DEBUG_LOG(eLogType::D_ERROR, "AABB bound is wrong");
	}
}



void dooms::physics::AABB3D::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	const math::Vector3 mLowerBoundVec3 = math::Vector3{ mLowerBound };
	const math::Vector3 mUpperBoundVec3 = math::Vector3{ mUpperBound };

	const math::Vector3 x{ mUpperBoundVec3.x - mLowerBoundVec3.x, 0, 0 };
	const math::Vector3 y{ 0, mUpperBoundVec3.y - mLowerBoundVec3.y, 0 };
	const math::Vector3 z{ 0, 0, mUpperBoundVec3.z - mLowerBoundVec3.z };

	debugGraphics->DebugDraw3DLine(mLowerBoundVec3, mLowerBoundVec3 + x, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3, mLowerBoundVec3 + y, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3, mLowerBoundVec3 + z, color);

	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + x, mLowerBoundVec3 + x + y, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + x, mLowerBoundVec3 + x + z, color);

	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + y, mLowerBoundVec3 + y + x, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + y, mLowerBoundVec3 + y + z, color);

	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + z, mLowerBoundVec3 + z + x, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + z, mLowerBoundVec3 + z + y, color);

	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + x + y, mLowerBoundVec3 + x + y + z, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + y + z, mLowerBoundVec3 + y + z + x, color);
	debugGraphics->DebugDraw3DLine(mLowerBoundVec3 + x + z, mLowerBoundVec3 + x + z + y, color);

#endif
}

void dooms::physics::AABB3D::Render2DTopView(eColor color, bool drawInstantly /*= false*/)
{
#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	math::Vector3 lower{ mLowerBound.x, mLowerBound.z, 0.0f };
	math::Vector3 width{ mUpperBound.x - mLowerBound.x, 0.0f, 0.0f };
	math::Vector3 height{ 0.0f, mUpperBound.z - mLowerBound.z, 0.0f };

	debugGraphics->DebugDraw2DLine(lower, lower + width, color);
	debugGraphics->DebugDraw2DLine(lower + width, lower + width + height, color);
	debugGraphics->DebugDraw2DLine(lower , lower + height, color);
	debugGraphics->DebugDraw2DLine(lower + height, lower + width + height, color);
#endif
}

dooms::physics::ColliderType dooms::physics::AABB3D::GetColliderType() const
{
	return dooms::physics::ColliderType::AABB3D;
}


AABB3D AABB3D::EnlargeAABB(const AABB3D& aabb)
{
	FLOAT32 offset = dooms::physics::Physics_Setting::ENLARGED_AABB3D_OFFSET;
	return AABB3D(aabb.mLowerBound - offset, aabb.mUpperBound + offset);
}

/// <summary>
/// /// See Christer Ericson's Real-time Collision Detection, p. 87, or
/// James Arvo's "Transforming Axis-aligned Bounding Boxes" in Graphics Gems 1, pp. 548-550.
/// http://www.graphicsgems.org/
/// </summary>
/// <param name="localAABB"></param>
/// <param name="modelMatrix"></param>
/// <param name="resultAABB"></param>

void dooms::physics::AABB3D::ApplyModelMatrix(const AABB3D& localAABB, const math::Matrix4x4& modelMatrix, AABB3D& resultAABB)
{
	// check 87p http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Christer_Ericson-Real-Time_Collision_Detection-EN.pdf

#ifdef __AVX__
	const M128F& localAABBLowerBound = *reinterpret_cast<const M128F*>(&localAABB.mLowerBound);
	const M128F& localAABBUpperBound = *reinterpret_cast<const M128F*>(&localAABB.mUpperBound);

	M128F centerPoint = M128F_MUL(M128F_ADD(localAABBLowerBound, localAABBUpperBound), _mm_set1_ps(0.5f));
	centerPoint.m128_f32[3] = 1.0f;
	const math::Vector4 newCenter = modelMatrix * (*reinterpret_cast<const math::Vector4*>(&centerPoint));

	const M128F halfSize = M128F_SUB(centerPoint, localAABBLowerBound);

	const M128F newXAxis = M128F_MUL(*reinterpret_cast<const M128F*>(modelMatrix.columns + 0), _mm_set1_ps(halfSize.m128_f32[0]));
	const M128F newYAxis = M128F_MUL(*reinterpret_cast<const M128F*>(modelMatrix.columns + 1), _mm_set1_ps(halfSize.m128_f32[1]));
	const M128F newZAxis = M128F_MUL(*reinterpret_cast<const M128F*>(modelMatrix.columns + 2), _mm_set1_ps(halfSize.m128_f32[2]));

	const math::Vector4 newDir
	(
		std::abs(newXAxis.m128_f32[0]) + std::abs(newYAxis.m128_f32[0]) + std::abs(newZAxis.m128_f32[0]),
		std::abs(newXAxis.m128_f32[1]) + std::abs(newYAxis.m128_f32[1]) + std::abs(newZAxis.m128_f32[1]),
		std::abs(newXAxis.m128_f32[2]) + std::abs(newYAxis.m128_f32[2]) + std::abs(newZAxis.m128_f32[2]),
		0
	);

	resultAABB.mLowerBound = newCenter - newDir;
	resultAABB.mUpperBound = newCenter + newDir;

#else

	const math::Vector4 centerPoint = (localAABB.mLowerBound + localAABB.mUpperBound) * 0.5f;
	const math::Vector4 halfSize = centerPoint - localAABB.mLowerBound;
	const math::Vector4 newCenter = modelMatrix * centerPoint;

	// The following is equal to taking the math::absolute value of the whole matrix m.
	const math::Vector4 newDir(
		std::abs(modelMatrix[0][0] * halfSize.x) + std::abs(modelMatrix[1][0] * halfSize.y) + std::abs(modelMatrix[2][0] * halfSize.z),
		std::abs(modelMatrix[0][1] * halfSize.x) + std::abs(modelMatrix[1][1] * halfSize.y) + std::abs(modelMatrix[2][1] * halfSize.z),
		std::abs(modelMatrix[0][2] * halfSize.x) + std::abs(modelMatrix[1][2] * halfSize.y) + std::abs(modelMatrix[2][2] * halfSize.z),
		0.0f
	);
	resultAABB.mLowerBound = newCenter - newDir;
	resultAABB.mUpperBound = newCenter + newDir;
#endif

}

/// <summary>
/// This is different with IsOverlap
/// This function check if innerAABB is completly enclosed by outerAABB
/// </summary>
/// <param name="A"></param>
/// <param name="B"></param>
/// <returns></returns>

bool dooms::physics::AABB3D::CheckIsCompletlyEnclosed(const AABB3D& innerAABB, const AABB3D& outerAABB)
{
	return innerAABB.mLowerBound.x >= outerAABB.mLowerBound.x &&
		innerAABB.mLowerBound.y >= outerAABB.mLowerBound.y &&
		innerAABB.mLowerBound.z >= outerAABB.mLowerBound.z &&
		innerAABB.mUpperBound.x <= outerAABB.mUpperBound.x &&
		innerAABB.mUpperBound.y <= outerAABB.mUpperBound.y &&
		innerAABB.mUpperBound.z <= outerAABB.mUpperBound.z;
}

void AABB3D::SignedExpand(const component_type& movedVector)
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

void AABB3D::Expand(const component_type& movedVector)
{
	const math::Vector4 expandVec{ std::abs(movedVector.x) ,  std::abs(movedVector.y) ,  std::abs(movedVector.z), 0.0f };
	mUpperBound += expandVec;
	mLowerBound -= expandVec;
}


////////////////////////////////////////





math::Vector2 dooms::physics::ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point)
{
	math::Vector2 result{ nullptr };
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

bool dooms::physics::IsOverlapAABB3DAndPoint(const AABB3D& A, const math::Vector3& Point)
{
	return (Point.x >= A.mLowerBound.x && Point.x <= A.mUpperBound.x) &&
		(Point.y >= A.mLowerBound.y && Point.y <= A.mUpperBound.y) &&
		(Point.z >= A.mLowerBound.z && Point.z <= A.mUpperBound.z);
}

bool dooms::physics::IsOverlapAABB3DAndAABB3D(const AABB3D& A, const AABB3D& B)
{
	return  A.mLowerBound.x <= B.mUpperBound.x && A.mUpperBound.x >= B.mLowerBound.x &&
			A.mLowerBound.y <= B.mUpperBound.y && A.mUpperBound.y >= B.mLowerBound.y &&
			A.mLowerBound.z <= B.mUpperBound.z && A.mUpperBound.z >= B.mLowerBound.z;
}

bool dooms::physics::IsOverlapAABB3DAndAABB3D(const Collider* const A, const Collider* const B)
{
	return IsOverlapAABB3DAndAABB3D(*static_cast<const AABB3D*>(A), *static_cast<const AABB3D*>(B));
}

math::Vector3 dooms::physics::ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point)
{
	math::Vector3 result{ nullptr };
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

