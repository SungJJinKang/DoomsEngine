#include "CircleCollider2D.h"
#include <Transform.h>

void dooms::CircleCollider2D::UpdateLocalCollider()
{
	mLocalCircle2D.mCenter = mOffset;
	mLocalCircle2D.mRadius = mRadius;
}

void dooms::CircleCollider2D::UpdateWorldCollider()
{
	auto transform = GetTransform();
	auto translate = transform->GetPosition();
	translate.z = 0;
	auto scale = transform->GetScale();

	mWorldCircle2D.mCenter = mOffset + translate;
	mWorldCircle2D.mRadius = mRadius * math::Max(scale.x, scale.y);
}



void dooms::CircleCollider2D::SetRadius(FLOAT32 radius)
{
	mRadius = radius;
	bmIsLocalColliderDirty = true;
}

FLOAT32 dooms::CircleCollider2D::GetRadius()
{
	return mRadius;
}

dooms::physics::AABB3D dooms::CircleCollider2D::ExtractLocalAABB3D()
{
	math::Vector3 lowerBound
	{
		mLocalCircle2D.mCenter.x - mLocalCircle2D.mRadius,
		mLocalCircle2D.mCenter.y - mLocalCircle2D.mRadius,
		0
	};

	math::Vector3 upperBound
	{
		mLocalCircle2D.mCenter.x + mLocalCircle2D.mRadius,
		mLocalCircle2D.mCenter.y + mLocalCircle2D.mRadius,
		0
	};

	return dooms::physics::AABB3D(lowerBound, upperBound);
}

dooms::physics::Collider* dooms::CircleCollider2D::GetWorldCollider()
{
	return &(mWorldCircle2D);
}

void dooms::CircleCollider2D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	mRadius = aabb3dFromMesh.GetDiagonarLineLength();
}
