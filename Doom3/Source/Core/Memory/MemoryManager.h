#pragma once

#include <Core.h>

#include <Game/IGameFlow.h>
#include <Simple_SingleTon/Singleton.h>

namespace dooms
{
	namespace memory
	{

		class D_CLASS MemoryManager : public IGameFlow, public ISingleton<MemoryManager>
		{

			void CheckIsIntelTBBLoaded() const;

		public:

			void Init() override;
			void Update() override;
			void OnEndOfFrame() override;
		};

	}
}
