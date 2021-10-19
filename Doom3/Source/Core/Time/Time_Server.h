#pragma once

#include "../Core.h"
#include "../Game/IGameFlow.h"



namespace doom
{
	class GameCore;

	namespace time
	{
		class DOOM_API Time_Server : public IGameFlow, public ISingleton<Time_Server>
		{
			DOBJECT_CLASS_BODY(Time_Server, doom::eDOBJECT_ClassFlags::NonCopyable);

			//TODO : Remove friend class
			friend class ::doom::GameCore;

		private:

			
		
			void Init() noexcept override;
			void Update() noexcept override;
			void OnEndOfFrame() noexcept override;

			

		
		};
	}
	
}


