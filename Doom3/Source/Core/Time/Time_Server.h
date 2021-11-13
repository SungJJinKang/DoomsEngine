#pragma once

#include "../Core.h"
#include "../Game/IGameFlow.h"

#include "MainTimer.h"

#include "Time_Server.reflection.h"
namespace dooms
{
	class GameCore;

	namespace time
	{
		class DOOM_API D_CLASS Time_Server : public IGameFlow, public ISingleton<Time_Server>
		{
			GENERATE_BODY()
			
				
		public:

			MainTimer mMainTimer;
			
			void Init() noexcept override;
			void Update() noexcept override;
			void OnEndOfFrame() noexcept override;

			

		
		};
	}
	
}


