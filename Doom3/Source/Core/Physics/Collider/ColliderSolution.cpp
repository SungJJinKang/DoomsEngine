#include "ColliderSolution.h"

#include "AABB.h"
#include "CapsuleCollider.h"
#include "Circle2D.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"

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
doom::physics::CollisionAlgorithm doom::physics::ColliderSolution::CollisionAlgorithms[COLLIDER_TYPE_COUNT][COLLIDER_TYPE_COUNT]
{
	{ 
		
		[](Collider* colA, Collider* colB)->bool
		{
			
		},

		[](Collider* colA, Collider* colB)->bool
		{

		},

		[](Collider* colA, Collider* colB)->bool
		{

		},

		[](Collider* colA, Collider* colB)->bool
		{

		},

		[](Collider* colA, Collider* colB)->bool
		{

		},

		[](Collider* colA, Collider* colB)->bool
		{

		},

	},
	{
	
	},
	{
	
	},
	{
	
	},
	{
	
	},
	{
	
	},
	{
	
	},
	{
	
	}
};

bool doom::physics::ColliderSolution::IsOverlap(Collider* a, Collider* b)
{

}

