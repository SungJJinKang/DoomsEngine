#include "DebugPrimitiveContainer.h"

std::vector<float>& dooms::graphics::DebugPrimitiveContainer::GetColoredVertexVector(const eColor color)
{
	D_ASSERT(static_cast<UINT32>(color) < ENUM_COLOR_COUNT);

	return mColoredVertexData[static_cast<UINT32>(color)];
}

const float* dooms::graphics::DebugPrimitiveContainer::GetColoredVertexData(const eColor color) const
{
	D_ASSERT(static_cast<UINT32>(color) < ENUM_COLOR_COUNT);

	return mColoredVertexData[static_cast<UINT32>(color)].data();
}

/*
size_t dooms::graphics::DebugPrimitiveContainer::GetColoredVertexCount(const eColor color) const
{
	D_ASSERT(static_cast<UINT32>(color) < ENUM_COLOR_COUNT);

	return mColoredVertexData[static_cast<UINT32>(color)].size() / GetVertexCountPerPrimitive();
}
*/

size_t dooms::graphics::DebugPrimitiveContainer::GetColoredPrimitiveCount(const eColor color) const
{
	D_ASSERT(static_cast<UINT32>(color) < ENUM_COLOR_COUNT);

	return mColoredVertexData[static_cast<UINT32>(color)].size() / GetComponentCountPerPrimitive();
}

const float* dooms::graphics::DebugPrimitiveContainer::GetSpecialColoredVertexData() const
{
	return mSpecialColoredVertexData.data();
}

size_t dooms::graphics::DebugPrimitiveContainer::GetSpecialColoredVertexDataCount() const
{
	return mSpecialColoredVertexData.size() / GetComponentCountPerPrimitive();
}

const math::Vector4* dooms::graphics::DebugPrimitiveContainer::GetSpecialColorData() const
{
	return mSpecialColorData.data();
}

size_t dooms::graphics::DebugPrimitiveContainer::GetSpecialColorDataCount() const
{
	return mSpecialColorData.size();
}

size_t dooms::graphics::DebugPrimitiveContainer::GetSpecialColoredPrimitiveCount() const
{
	return mSpecialColoredVertexData.size() / GetComponentCountPerPrimitive();
}

void dooms::graphics::DebugPrimitiveContainer::ReserveVector(const size_t primitiveCount)
{
	for(auto& coloredVertexVector : mColoredVertexData)
	{
		coloredVertexVector.reserve(primitiveCount * GetComponentCountPerPrimitive());
	}

	mSpecialColoredVertexData.reserve(primitiveCount * GetComponentCountPerPrimitive());
	mSpecialColorData.reserve(primitiveCount * GetComponentCountPerPrimitive());
}

void dooms::graphics::DebugPrimitiveContainer::ClearDatas()
{
	for (auto& coloredVertexVector : mColoredVertexData)
	{
		coloredVertexVector.clear();
	}

	mSpecialColoredVertexData.clear();
	mSpecialColorData.clear();
}

bool dooms::graphics::DebugPrimitiveContainer::IsColoredVertexDataEmpty(const eColor color) const
{
	D_ASSERT(static_cast<UINT32>(color) < ENUM_COLOR_COUNT);
	return mColoredVertexData[static_cast<UINT32>(color)].empty();
}

bool dooms::graphics::DebugPrimitiveContainer::IsSpecialColoredVertexDataEmpty() const
{
	return mSpecialColoredVertexData.empty();
}
