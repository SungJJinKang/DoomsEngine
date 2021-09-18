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

			using is_overlap_algorithm_func = bool (*)(const Collider* colA, const Collider* const colB);
			using raycast_algorithm_func = float (*)(const Collider* colA, const Collider* const colB);

			/// <summary>
			/// How to use : Get Algorithm with CollisionAlgorithms[A ColliderType][B ColliderType]
			/// </summary>
			static is_overlap_algorithm_func CollisionAlgorithms[COLLIDER_TYPE_COUNT][COLLIDER_TYPE_COUNT];
			static is_overlap_algorithm_func GetCollisionAlgorithm(const Collider* const colliderA, const Collider* const colliderB);
		public:
			
			static bool CheckIsOverlap(const Collider* const colliderA, const Collider* const colliderB);
		};
	}
}

