#pragma once
#include "../Game/GameFlow.h"
#include "../Singleton.h"

namespace doom
{
	namespace physics
	{
		class Physics_Server : public GameFlow, public ISingleton<Physics_Server>
		{

			friend class GameCore;

		private:

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

		};

	}
}

