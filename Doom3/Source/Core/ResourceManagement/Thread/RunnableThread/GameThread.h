#pragma once


#include "../Core.h"

#include "RunnableThread.h"
#include <../Helper/Simple_SingleTon/Singleton.h>

#include "RenderThread.reflection.h"
namespace dooms
{
	namespace thread
	{
		class DOOM_API D_CLASS GameThread : public RunnableThread, public ISingleton<GameThread>
		{

		public:

			const char* GetThreadName() const override;
			eThreadType GetThreadType() const override;

			virtual void Init_OnCallerThread() override;
			bool IsAllowMultipleThreadOfThisThreadType() const override;

		protected:

			bool IsCreateNewThread() override;
			
		};
	}
}

