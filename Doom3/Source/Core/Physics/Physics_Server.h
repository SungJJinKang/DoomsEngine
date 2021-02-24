#pragma once
#include "../Core.h"
#include "../Game/IGameFlow.h"
#include "../Singleton.h"
#include "Picking.h"

namespace doom
{
	namespace physics
	{
		class Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{

			friend class GameCore;

		private:
			Picking mPicking{};

			virtual void Init() final;
			virtual void Update() final;

			void UpdateColliders();

			virtual void OnEndOfFrame() final;

		public:
			static inline bool IsShowDebug{ true };

		};

	}
}

