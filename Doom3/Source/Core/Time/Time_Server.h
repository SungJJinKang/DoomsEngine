#pragma once

#include "../Core.h"
#include "../Game/IGameFlow.h"

#include "MainTimer.h"

namespace dooms
{
	class GameCore;

	namespace time
	{
		class DOOM_API D_CLASS Time_Server : public IGameFlow, public ISingleton<Time_Server>
		{
			DOBJECT_CLASS_BODY(Time_Server, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(IGameFlow)
				
		public:

			MainTimer mMainTimer;
			
			void Init() noexcept override;
			void Update() noexcept override;
			void OnEndOfFrame() noexcept override;

			

		
		};
	}
	
}


