#pragma once

#include "../Core.h"
#include "CollisionAlgorithm.h"
#include "ColliderType.h"
namespace doom
{
	namespace physics
	{


		class Collider;
		class ColliderSolution
		{
		public:
			/// <summary>
			/// How to use : Get Algorithm with CollisionAlgorithms[A ColliderType][B ColliderType]
			/// </summary>
			static CollisionAlgorithm CollisionAlgorithms[COLLIDER_TYPE_COUNT][COLLIDER_TYPE_COUNT];
			static bool IsOverlap(Collider* a, Collider* b);
		};
	}
}

