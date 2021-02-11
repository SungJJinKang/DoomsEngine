#pragma once
#include "../Game/IGameFlow.h"
#include "../Singleton.h"

namespace doom
{
	namespace physics
	{
		class Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{

			friend class GameCore;

		private:

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

		};

	}
}

