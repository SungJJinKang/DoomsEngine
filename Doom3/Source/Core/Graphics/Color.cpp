#include "Color.h"


const math::Vector4 dooms::graphics::Color::WHITE{ 1.0f, 1.0f, 1.0f, 1.0f };
const math::Vector4 dooms::graphics::Color::BLACK{ 0.0f, 0.0f, 0.0f, 1.0f };
const math::Vector4 dooms::graphics::Color::RED{ 1.0f, 0.0f, 0.0f, 1.0f };
const math::Vector4 dooms::graphics::Color::GREEN{ 0.0f, 1.0f, 0.0f, 1.0f };
const math::Vector4 dooms::graphics::Color::BLUE{ 0.0f, 0.0f, 1.0f, 1.0f };

const math::Vector4& dooms::graphics::Color::GetColor(eColor color)
{
	switch (color)
	{
		case eColor::White:
		{
			return Color::WHITE;
		}
		case eColor::Black:
		{
			return Color::BLACK;
		}
		case eColor::Red:
		{
			return Color::RED;
		}
		case eColor::Green:
		{
			return Color::GREEN;
		}
		case eColor::Blue:
		{
			return Color::BLUE;
		}
		default:
		{
			ASSUME_ZERO;
			break;
		}
	}

	return math::Vector4{ nullptr };
}
			