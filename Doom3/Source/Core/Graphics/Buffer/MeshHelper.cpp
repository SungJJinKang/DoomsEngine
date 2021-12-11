#include "MeshHelper.h"

namespace dooms::graphics::meshHelper
{
	static constexpr FLOAT32 QuadMeshData[]
	{
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};


	extern std::shared_ptr<Mesh> QuadMesh{};
}

std::shared_ptr<dooms::graphics::Mesh> dooms::graphics::meshHelper::GetQuadMesh()
{
	if (dooms::graphics::meshHelper::QuadMesh == nullptr)
	{
		dooms::graphics::meshHelper::QuadMesh = std::make_shared<Mesh>(sizeof(QuadMeshData) / sizeof(FLOAT32), (void*)QuadMeshData, ePrimitiveType::TRIANGLES, Mesh::eVertexArrayFlag::VertexVector3 | Mesh::eVertexArrayFlag::TexCoord);
	}

	return dooms::graphics::meshHelper::QuadMesh;
}

dooms::graphics::Mesh dooms::graphics::meshHelper::GetQuadMesh(const math::Vector2& leftbottom, const math::Vector2& rightup)
{
	FLOAT32 QuadMeshData[]
	{
		leftbottom.x, rightup.y, 0.0f, 0.0f, 1.0f,
		leftbottom.x, leftbottom.y, 0.0f, 0.0f, 0.0f,
		rightup.x, leftbottom.y, 0.0f, 1.0f, 0.0f,

		rightup.x, leftbottom.y, 0.0f, 1.0f, 0.0f,
		rightup.x, rightup.y, 0.0f, 1.0f, 1.0f,
		leftbottom.x, rightup.y, 0.0f, 0.0f, 1.0f,
	};

	return Mesh(sizeof(QuadMeshData) / sizeof(FLOAT32), reinterpret_cast<void*>(QuadMeshData), ePrimitiveType::TRIANGLES, Mesh::eVertexArrayFlag::VertexVector3 | Mesh::eVertexArrayFlag::TexCoord);
}
