#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		class RenderingProxy
		{

		public:


			void MarkAsDirty();

			FORCE_INLINE bool GetIsDirty() const
			{
				return bIsDirty;
			}

		private:

			bool bIsDirty = true;

		};
	}
}

