#pragma once

//#include "../Core.h" don't do this ( recursive dependency )

#include <Core.h>

#include <Vector4.h>

#include "Color.reflection.h"
namespace dooms
{
	namespace graphics 
	{
		enum class D_ENUM eColor
		{
			White = 0,
			Black = 1,
			Red = 2,
			Green = 3,
			Blue = 4
			
		};
		
		enum
		{
			ENUM_COLOR_COUNT = 5
		};
		
		namespace Color
		{
			extern const math::Vector4 WHITE;
			extern const math::Vector4 BLACK;
			extern const math::Vector4 RED;
			extern const math::Vector4 GREEN;
			extern const math::Vector4 BLUE;
		
			extern const math::Vector4& GetColor(eColor color);
		};
		
	}
}

using dooms::graphics::eColor;