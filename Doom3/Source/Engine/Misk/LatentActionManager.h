#pragma once

#include <Core.h>

#include <functional>

#include "../Game/IGameFlow.h"
#include <Simple_SingleTon/Singleton.h>
#include <blockingconcurrentqueue.h>

#include "LatentActionManager.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS LatentActionManager : public IGameFlow, public ISingleton<LatentActionManager>
	{
		GENERATE_BODY()

	public:

		using LATENT_ACTION_TYPE = std::function<void()>;

		template <typename LAMBDA>
		void EnqueueLatentAction(LAMBDA&& LatentAction)
		{
			if(bLatentActionQueueToggle == false)
			{
				LatentActionQueue1.enqueue(std::forward<LAMBDA>(LatentAction));
			}
			else
			{
				LatentActionQueue2.enqueue(std::forward<LAMBDA>(LatentAction));
			}
		}
		
		void Init(const int argc, char* const* const argv) override;
		void Update() override;
		void OnEndOfFrame() override;

	private:

		bool bLatentActionQueueToggle = false;
		
		moodycamel::BlockingConcurrentQueue<LATENT_ACTION_TYPE> LatentActionQueue1;
		moodycamel::BlockingConcurrentQueue<LATENT_ACTION_TYPE> LatentActionQueue2;

	};
}

