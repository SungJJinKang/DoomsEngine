#pragma once

//#include "../Core.h" don't do this ( recursive dependency )

#include <Core.h>

#include <Vector4.h>

namespace doom
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

		D_PROPERTY()
		inline constexpr extern UINT32 ENUM_COLOR_COUNT = 5;

		class D_CLASS Color
		{
		public:

			D_PROPERTY()
			inline static const math::Vector4 WHITE{ 1.0f, 1.0f, 1.0f, 1.0f };

			D_PROPERTY()
			inline static const math::Vector4 BLACK{ 0.0f, 0.0f, 0.0f, 1.0f };

			D_PROPERTY()
			inline static const math::Vector4 RED{ 1.0f, 0.0f, 0.0f, 1.0f };

			D_PROPERTY()
			inline static const math::Vector4 GREEN{ 0.0f, 1.0f, 0.0f, 1.0f };

			D_PROPERTY()
			inline static const math::Vector4 BLUE{ 0.0f, 0.0f, 1.0f, 1.0f };
		
			static const math::Vector4& GetColor(eColor color)
			{
				switch (color)
				{
					case eColor::White:
						return Color::WHITE;
					break;

					case eColor::Black:
						return Color::BLACK;
						break;

					case eColor::Red:
						return Color::RED;
						break;

					case eColor::Green:
						return Color::GREEN;
						break;

					case eColor::Blue:
						return Color::BLUE;
						break;

					default:
						__assume(0);
						break;
				}
			}

		};
		
	}
}

using doom::graphics::eColor;