#include "MeshCollider.h"

void doom::MeshCollider::UpdateLocalCollider()
{

}

void doom::MeshCollider::UpdateWorldCollider()
{

}

void doom::MeshCollider::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{

}

doom::physics::Collider* doom::MeshCollider::GetWorldCollider()
{
	return nullptr;
}

doom::physics::AABB3D doom::MeshCollider::ExtractLocalAABB3D()
{
	return this->GetLocalBVhAABB3DCache();
}
