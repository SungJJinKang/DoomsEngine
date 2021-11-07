#include "MeshCollider.h"

void dooms::MeshCollider::UpdateLocalCollider()
{

}

void dooms::MeshCollider::UpdateWorldCollider()
{

}

void dooms::MeshCollider::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{

}

dooms::physics::Collider* dooms::MeshCollider::GetWorldCollider()
{
	return nullptr;
}

dooms::physics::AABB3D dooms::MeshCollider::ExtractLocalAABB3D()
{
	return GetLocalColliderCache();
}
