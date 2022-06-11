#pragma once

#include <Core.h>

#include <vector>

#include <Simple_SingleTon/Singleton.h>

#include "RenderingProxyManager.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class RenderingPrimitiveProxy;
		class RenderingLighProxy;

		class DOOM_API D_CLASS RenderingProxyManager : public DObject, public ISingleton<RenderingProxyManager>
		{
			GENERATE_BODY()
			
		public:

		private:

			std::vector<RenderingPrimitiveProxy*> RenderingPrimitiveProxyList{};
			std::vector<RenderingLighProxy*> RenderingLighProxyList{};
		};
	}
}


