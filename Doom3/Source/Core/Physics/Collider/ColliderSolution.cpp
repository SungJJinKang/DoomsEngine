#include "ColliderSolution.h"

#include "AABB.h"
#include "CapsuleCollider.h"
#include "Circle2D.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "PhysicsGeneric.h"

#include <magic_enum.hpp>

// enum class ColliderType
// {
// 	AABB2D,
// 	AABB3D,
// 	Circle2D,
// 	CapsuleCollider,
// 	Line,
// 	Plane,
// 	Ray,
// 	Sphere
// };

//TODO : 더 좋은 방법 찾아보자
doom::physics::ColliderSolution::is_overlap_algorithm_func doom::physics::ColliderSolution::CollisionAlgorithms[COLLIDER_TYPE_COUNT][COLLIDER_TYPE_COUNT]
{

	//AABB2D
	{
		&(physics::IsOverlapAABB2DAndAABB2D), //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		&(physics::RaycastLineAndAABB2D), //Line
		nullptr, //Plane
		&(physics::RaycastRayAndAABB2D), //Ray
		nullptr, //Sphere
		nullptr //TwoDTriangle
	},


	//AABB3D
	{
		nullptr, //AABB2D
		&(physics::IsOverlapAABB3DAndAABB3D), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		&(physics::RaycastLineAndAABB3D), //Line
		&(physics::IsOverlapAABB3DAndPlane), //Plane
		&(physics::RaycastRayAndAABB3D), //Ray
		&(physics::IsOverlapSphereAndAABB3D), //Sphere
		nullptr //TwoDTriangle
	},


	//Circle2D
	{
		nullptr, //AABB2D
		nullptr, //AABB3D
		&(physics::IsOverlapCircle2DAndCircle2D), //Circle2D
		nullptr, //CapsuleCollider
		&(physics::RaycastLineAndCirecle2D), //Line
		nullptr, //Plane
		&(physics::RaycastRayAndCirecle2D), //Ray
		nullptr, //Sphere
		nullptr //TwoDTriangle
	},


	//CapsuleCollider
	{
		nullptr, //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		nullptr, //Plane
		nullptr, //Ray
		nullptr, //Sphere
		nullptr //TwoDTriangle
	},


	//Line
	{
		&(physics::RaycastLineAndAABB2D), //AABB2D
		&(physics::RaycastLineAndAABB3D), //AABB3D
		&(physics::RaycastLineAndCirecle2D), //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		&(physics::RaycastLineAndPlane), //Plane
		nullptr, //Ray
		&(physics::RaycastLineAndSphere), //Sphere
		nullptr //TwoDTriangle
	},


	//Plane
	{
		nullptr, //AABB2D
		&(physics::IsOverlapAABB3DAndPlane), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		&(physics::RaycastLineAndPlane), //Line
		&(physics::IsOverlapPlaneAndPlane),  //Plane
		&(physics::RaycastRayAndPlane),  //Ray
		&(physics::IsOverlapSphereAndPlane), //Sphere
		nullptr //TwoDTriangle
	},


	//Ray
	{
		&(physics::RaycastRayAndAABB2D), //AABB2D
		&(physics::RaycastRayAndAABB3D), //AABB3D
		&(physics::RaycastRayAndCirecle2D), //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		&(physics::RaycastRayAndPlane), //Plane
		nullptr, //Ray
		&(physics::RaycastRayAndSphere), //Sphere
		nullptr //TwoDTriangle
	},


	//Sphere
	{
		nullptr, //AABB2D
		&(physics::IsOverlapSphereAndAABB3D), //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		&(physics::RaycastLineAndSphere), //Line
		&(physics::IsOverlapSphereAndPlane), //Plane
		&(physics::RaycastRayAndSphere), //Ray
		&(physics::IsOverlapSphereAndSphere), //Sphere
		nullptr //TwoDTriangle
	},

	//TwoDTriangle
	{
		nullptr, //AABB2D
		nullptr, //AABB3D
		nullptr, //Circle2D
		nullptr, //CapsuleCollider
		nullptr, //Line
		nullptr, //Plane
		nullptr, //Ray
		nullptr, //Sphere
		nullptr //TwoDTriangle
	}
};

doom::physics::ColliderSolution::is_overlap_algorithm_func doom::physics::ColliderSolution::GetCollisionAlgorithm(Collider* colliderA, Collider* colliderB)
{
	return doom::physics::ColliderSolution::CollisionAlgorithms[static_cast<unsigned int>(colliderA->GetColliderType())][static_cast<unsigned int>(colliderB->GetColliderType())];
}

bool doom::physics::ColliderSolution::CheckIsOverlap(Collider* colliderA, Collider* colliderB)
{
	auto solution = ColliderSolution::GetCollisionAlgorithm(colliderA, colliderB);
	if (solution != nullptr)
	{
		return solution(colliderA, colliderB);
	}
	else
	{
#ifdef DEBUG_MODE
		std::string name1{ magic_enum::enum_name(colliderA->GetColliderType()) };
		std::string name2{ magic_enum::enum_name(colliderB->GetColliderType()) };

		D_DEBUG_LOG({ "Cant FInd Collider Solution : " + name1 + ' ' + name2 }, eLogType::D_WARNING);
#endif
		return false;
	}
}
