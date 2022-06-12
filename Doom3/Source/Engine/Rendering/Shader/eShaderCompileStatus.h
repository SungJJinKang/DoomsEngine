#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum class eShaderCompileStatus : UINT32
		{
			READY,
			SHADER_OBJECT_CREATED,
			COMPILE_SUCCESS,
			COMPILE_FAIL
		};

	}
}
