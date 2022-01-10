#include "DebugPrimitivePointContainer.h"

UINT32 dooms::graphics::DebugPrimitivePointContainer::GetVertexCountPerPrimitive() const
{
	return 1;
}

UINT32 dooms::graphics::DebugPrimitivePointContainer::GetComponentCountPerPrimitive() const
{
	return 3;
}

dooms::graphics::GraphicsAPI::ePrimitiveType dooms::graphics::DebugPrimitivePointContainer::GetPrimitiveType() const
{
	return dooms::graphics::GraphicsAPI::ePrimitiveType::POINTS;
}

void dooms::graphics::DebugPrimitivePointContainer::AddColoredPointData
(
	const math::Vector3 point, 
	const eColor color
)
{
	std::vector<float>& container = GetColoredVertexVector(color);

	container.push_back(point.x);
	container.push_back(point.y);
	container.push_back(point.z);
}

void dooms::graphics::DebugPrimitivePointContainer::AddColoredPointData
(
	const math::Vector3 point,
	const math::Vector4 color
)
{
	mSpecialColoredVertexData.push_back(point.x);
	mSpecialColoredVertexData.push_back(point.y);

	mSpecialColorData.push_back(color);
}
