#pragma once

#include "../Core.h"

#include "../eThreadType.h"

#include "RunnableThread.reflection.h"
namespace dooms
{
	namespace thread
	{
		class DOOM_API D_CLASS RunnableThread : public DObject
		{
			GENERATE_BODY()

		private:

			bool bInitialized = false;
			std::string BeautifulThreadName;

		protected:

			RunnableThread(const char* const _BeautifulThreadName);

			virtual void Init();
			virtual void Tick();

		public:
			
			void Run();

			std::string GetBeautifulThreadName() const;
			virtual eThreadType GetThreadType() const = 0;

		};


		extern bool IsInGameThread();
		extern bool IsInRenderThread();
	}
}

