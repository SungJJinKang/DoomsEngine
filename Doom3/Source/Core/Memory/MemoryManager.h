#pragma once

#include <Core.h>

#include <Game/IGameFlow.h>
#include <SingleTon/Singleton.h>

#include "MemoryManager.reflection.h"
namespace dooms
{
	namespace memory
	{

		class D_CLASS MemoryManager : public IGameFlow, public ISingleton<MemoryManager>
		{
			GENERATE_BODY()

		private:

			void CheckIsIntelTBBLoaded() const;

		public:

			void Init() override;
			void Update() override;
			void OnEndOfFrame() override;
		};

	}
}
