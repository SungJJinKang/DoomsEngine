#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		class GraphicsAPIManager : public DObject
		{

		private:

		public:

			virtual void Initialize() = 0;
			virtual void DeInitialize() = 0;

		};
	}
}


