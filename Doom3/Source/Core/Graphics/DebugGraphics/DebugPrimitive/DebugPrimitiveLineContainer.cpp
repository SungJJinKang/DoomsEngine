#include "DebugPrimitiveLineContainer.h"

UINT32 dooms::graphics::DebugPrimitiveLineContainer::GetVertexCountPerPrimitive() const
{
	return 2;
}

UINT32 dooms::graphics::DebugPrimitiveLineContainer::GetComponentCountPerPrimitive() const
{
	return 6;
}

dooms::ePrimitiveType dooms::graphics::DebugPrimitiveLineContainer::GetPrimitiveType() const
{
	return ePrimitiveType::LINES;
}

void dooms::graphics::DebugPrimitiveLineContainer::AddColoredLineData
(
	const math::Vector3 point1,
	const math::Vector3 point2,
	const eColor color
)
{
	std::vector<float>& container = GetColoredVertexVector(color);

	container.push_back(point1.x);
	container.push_back(point1.y);
	container.push_back(point1.z);
	container.push_back(point2.x);
	container.push_back(point2.y);
	container.push_back(point2.z);
}

void dooms::graphics::DebugPrimitiveLineContainer::AddColoredLineData
(
	const math::Vector3 point1,
	const math::Vector3 point2, 
	const math::Vector4 color
)
{
	mSpecialColoredVertexData.push_back(point1.x);
	mSpecialColoredVertexData.push_back(point1.y);
	mSpecialColoredVertexData.push_back(point1.z);
	mSpecialColoredVertexData.push_back(point2.x);
	mSpecialColoredVertexData.push_back(point2.y);
	mSpecialColoredVertexData.push_back(point2.z);

	mSpecialColorData.push_back(color);
}
