#pragma once

#include "../Core.h"
#include <functional>
namespace doom
{
	namespace physics
	{
		class Collider;
		using collision_algorithm_func = bool (*)(Collider* colA, Collider* colB);
		struct CollisionAlgorithm
		{
			//std::function<bool(Collider* colA, Collider* colB)> algorithmFunction;
			collision_algorithm_func algorithmFunction;
		};

	}
}