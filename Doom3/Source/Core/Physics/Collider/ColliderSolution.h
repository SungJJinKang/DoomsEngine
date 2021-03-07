#pragma once

#include "../Core.h"
#include "ColliderType.h"
namespace doom
{
	namespace physics
	{


		class Collider;
		class ColliderSolution
		{
		private:

			using is_overlap_algorithm_func = bool (*)(Collider* colA, Collider* colB);
			using raycast_algorithm_func = float (*)(Collider* colA, Collider* colB);

			/// <summary>
			/// How to use : Get Algorithm with CollisionAlgorithms[A ColliderType][B ColliderType]
			/// </summary>
			static is_overlap_algorithm_func CollisionAlgorithms[COLLIDER_TYPE_COUNT][COLLIDER_TYPE_COUNT];

		public:
			static is_overlap_algorithm_func GetCollisionAlgorithm(Collider* colliderA, Collider* colliderB);
		};
	}
}

