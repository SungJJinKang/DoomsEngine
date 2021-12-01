#pragma once

#include <CompilerMacros.h>

namespace dooms
{
	namespace gc
	{
		class GarbageCollectee
		{

		private:

			bool mIsPendingKill;


		public:

			GarbageCollectee();
			GarbageCollectee(bool isPendingKill);
			GarbageCollectee(const GarbageCollectee& gcee);
			GarbageCollectee(GarbageCollectee&& gcee) noexcept;

			GarbageCollectee& operator=(const GarbageCollectee& gcee);
			GarbageCollectee& operator=(GarbageCollectee&& gcee) noexcept;

			FORCE_INLINE bool GetIsPendingKill() const
			{
				return mIsPendingKill;
			}
			void SetIsPendingKill(const bool isPendingKill);

		};
	}
}


