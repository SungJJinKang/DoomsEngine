#pragma once

#include <Core.h>

#include <Simple_SingleTon/Singleton.h>

namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS ShaderCodeLibrary : public DObject, public ISingleton<ShaderCodeLibrary>
		{
		};
	}
}


