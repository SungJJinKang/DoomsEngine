#pragma once

#include <Core.h>

#include "EnginePlugin.reflection.h"
namespace dooms
{
	namespace plugin
	{
		class D_CLASS EnginePlugin : public DObject
		{
			GENERATE_BODY()

		private:

		public:

			virtual const char* GetEnginePluginName() const = 0;

		};
	}
}


