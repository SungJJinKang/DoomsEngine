#pragma once

#include <chrono>
#include "../Core.h"
#include "../Game/IGameFlow.h"



namespace doom
{
	class GameCore;

	namespace time
	{
		class DOOM_API Time_Server : public IGameFlow, public ISingleton<Time_Server>
		{
			friend class ::doom::GameCore;

		private:

			
		
			void Init() noexcept override;
			void Update() noexcept override;
			void OnEndOfFrame() noexcept override;

			

		
		};
	}
	
}


