#include "DebugPrimitiveTriangleContainer.h"

UINT32 dooms::graphics::DebugPrimitiveTriangleContainer::GetVertexCountPerPrimitive() const
{
	return 3;
}

UINT32 dooms::graphics::DebugPrimitiveTriangleContainer::GetComponentCountPerPrimitive() const
{
	return 9;
}

dooms::graphics::GraphicsAPI::ePrimitiveType dooms::graphics::DebugPrimitiveTriangleContainer::GetPrimitiveType() const
{
	return dooms::graphics::GraphicsAPI::ePrimitiveType::TRIANGLES;
}

void dooms::graphics::DebugPrimitiveTriangleContainer::AddColoredTriangleData
(
	const math::Vector3 point1,
	const math::Vector3 point2, 
	const math::Vector3 point3, 
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
	container.push_back(point3.x);
	container.push_back(point3.y);
	container.push_back(point3.z);
}

void dooms::graphics::DebugPrimitiveTriangleContainer::AddColoredTriangleData
(
	const math::Vector3 point1,
	const math::Vector3 point2, 
	const math::Vector3 point3, 
	const math::Vector4 color
)
{
	mSpecialColoredVertexData.push_back(point1.x);
	mSpecialColoredVertexData.push_back(point1.y);
	mSpecialColoredVertexData.push_back(point1.z);
	mSpecialColoredVertexData.push_back(point2.x);
	mSpecialColoredVertexData.push_back(point2.y);
	mSpecialColoredVertexData.push_back(point2.z);
	mSpecialColoredVertexData.push_back(point3.x);
	mSpecialColoredVertexData.push_back(point3.y);
	mSpecialColoredVertexData.push_back(point3.z);

	mSpecialColorData.push_back(color);
}
