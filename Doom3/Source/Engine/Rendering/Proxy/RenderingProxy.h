#pragma once

#include <Core.h>

#include <ResourceManagement/Thread/RunnableThread/RenderThread.h>

namespace dooms
{
	namespace graphics
	{
		class RenderingProxy
		{

		public:

			virtual ~RenderingProxy() = default;

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

