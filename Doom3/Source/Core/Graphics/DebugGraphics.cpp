#include "DebugGraphics.h"

#include "Graphics_Server.h"
#include "../Game/AssetManager.h"
#include "Material.h"

void doom::graphics::DebugGraphics::Init()
{
	this->mDebugMesh.GenMeshBuffer(false);
	this->mDebugMesh.BufferData(MAX_DEBUG_VERTEX_COUNT * 3, NULL, ePrimitiveType::LINES, Mesh::eVertexArrayFlag::Vertex);


	auto debug2DShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>(DebugGraphics::DEBUG_2D_SHADER);
	this->m2DMaterial = std::make_unique<Material>(*debug2DShader);

	auto debug3DShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>(DebugGraphics::DEBUG_3D_SHADER);
	this->m3DMaterial = std::make_unique<Material>(*debug3DShader);
}

void doom::graphics::DebugGraphics::Reset()
{
	this->mDebugMeshCount = 0;
	for (size_t i = 0; i < this->m2dLine.size(); i++)
	{
		this->m2dLine[i].clear();
	}

	for (size_t i = 0; i < this->m3dLine.size(); i++)
	{
		this->m3dLine[i].clear();
	}

	for (size_t i = 0; i < this->m2dTriangle.size(); i++)
	{
		this->m2dTriangle[i].clear();
	}

	for (size_t i = 0; i < this->m3dTriangle.size(); i++)
	{
		this->m3dTriangle[i].clear();
	}
}



doom::graphics::DebugGraphics::DebugGraphics() : m2DMaterial{}, m3DMaterial{}, m2dLine{}, m3dLine{}, m2dTriangle{}, m3dTriangle{}
{
	for (size_t i = 0; i < this->m2dLine.size(); i++)
	{
		this->m2dLine[i].reserve(100);
	}

	for (size_t i = 0; i < this->m3dLine.size(); i++)
	{
		this->m3dLine[i].reserve(100);
	}

	for (size_t i = 0; i < this->m2dTriangle.size(); i++)
	{
		this->m2dTriangle[i].reserve(100);
	}

	for (size_t i = 0; i < this->m3dTriangle.size(); i++)
	{
		this->m3dTriangle[i].reserve(100);
	}
}

void doom::graphics::DebugGraphics::DrawDebug()
{
	if (DebugGraphics::mbDrawDebug == false)
		return;

	//DRAW 2D FIRST

	/// <summary>
	/// vector3 -> 3, vector4 -> 4
	/// </summary>
	int exOffsetComponentCount{ 0 };
	int offsetComponentCount{ 0 };
	unsigned int alreadyDrawedVertexCount{ 0 };


	this->mDebugMesh.BindVertexArrayObject();
	this->mDebugMesh.BindVertexBufferObject();
	
	this->m2DMaterial->UseProgram();
	for (size_t i = 0; i < this->m2dLine.size(); i++)
	{
		unsigned int lineCount = static_cast<unsigned int>(this->m2dLine[i].size());
		if (lineCount > 0)
		{
			this->mDebugMesh.BufferSubData(lineCount * 6, this->m2dLine[i].data(), offsetComponentCount * sizeof(float));

			offsetComponentCount += lineCount * 6;
			alreadyDrawedVertexCount += lineCount * 2;

			D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount);

			this->m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
			this->mDebugMesh.DrawArray(ePrimitiveType::LINES, exOffsetComponentCount, lineCount * 2);
			exOffsetComponentCount = offsetComponentCount;
		}
	}

	for (size_t i = 0; i < this->m2dTriangle.size(); i++)
	{
		unsigned int triangleCount = static_cast<unsigned int>(this->m2dTriangle[i].size());
		if (triangleCount > 0)
		{
			this->mDebugMesh.BufferSubData(triangleCount * 9, this->m2dTriangle[i].data(), offsetComponentCount * sizeof(float));

			offsetComponentCount += triangleCount * 9;
			alreadyDrawedVertexCount += triangleCount * 3;

			D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount);

			this->m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
			this->mDebugMesh.DrawArray(ePrimitiveType::TRIANGLES, exOffsetComponentCount, triangleCount * 3);
			exOffsetComponentCount = offsetComponentCount;
		}
	}


	this->m3DMaterial->UseProgram();
	for (size_t i = 0; i < this->m3dLine.size(); i++)
	{
		unsigned int lineCount = static_cast<unsigned int>(this->m3dLine[i].size());
		if (lineCount > 0)
		{
			this->mDebugMesh.BufferSubData(lineCount * 6, this->m3dLine[i].data(), offsetComponentCount * sizeof(float));

			offsetComponentCount += lineCount * 6;
			alreadyDrawedVertexCount += lineCount * 2;

			D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount);

			this->m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
			this->mDebugMesh.DrawArray(ePrimitiveType::LINES, exOffsetComponentCount, lineCount * 2);
			exOffsetComponentCount = offsetComponentCount;
		}
	}

	for (size_t i = 0; i < this->m3dTriangle.size(); i++)
	{
		unsigned int triangleCount = static_cast<unsigned int>(this->m3dTriangle[i].size());
		if (triangleCount > 0)
		{
			this->mDebugMesh.BufferSubData(triangleCount * 9, this->m3dTriangle[i].data(), offsetComponentCount * sizeof(float));

			offsetComponentCount += triangleCount * 9;
			alreadyDrawedVertexCount += triangleCount * 3;

			D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount);

			this->m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
			this->mDebugMesh.DrawArray(ePrimitiveType::TRIANGLES, exOffsetComponentCount, triangleCount * 3);
			exOffsetComponentCount = offsetComponentCount;
		}
	}

	this->Reset();
}

void doom::graphics::DebugGraphics::DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color)
{
	this->m3dLine[static_cast<unsigned int>(color)].emplace_back(startWorldPos, endWorldPos);
}

/// <summary>
/// Why Use Vector3 not Vector2??
/// Debug mesh's Vertex Array Object have already define that Vector atribute have 3 component.
/// So For reducing complexity, Just use vector3
/// </summary>
/// <param name="startNDCPos"></param>
/// <param name="endNDCPos"></param>
/// <param name="color"></param>
void doom::graphics::DebugGraphics::DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color, bool resizeByScreenRatio)
{
	if (resizeByScreenRatio)
	{
		float screenRatio = Graphics_Server::GetScreenRatio();
		math::Vector3 newStartNDCPos{ startNDCPos.x * screenRatio , startNDCPos.y, startNDCPos.z };
		math::Vector3 newEndNDCPos{ endNDCPos.x * screenRatio , endNDCPos.y, endNDCPos.z };
	
		this->m2dLine[static_cast<unsigned int>(color)].emplace_back(newStartNDCPos, newEndNDCPos);
	}
	else
	{
		this->m2dLine[static_cast<unsigned int>(color)].emplace_back(startNDCPos, startNDCPos);
	}
	
}

void doom::graphics::DebugGraphics::DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color, bool resizeByScreenRatio)
{
	if (resizeByScreenRatio)
	{
		float screenRatio = Graphics_Server::GetScreenRatio();
		math::Vector3 newPointA{ pointA.x * screenRatio , pointA.y, pointA.z };
		math::Vector3 newPointB{ pointB.x * screenRatio , pointB.y, pointB.z };
		math::Vector3 newPointC{ pointC.x * screenRatio , pointC.y, pointC.z };

		this->m2dTriangle[static_cast<unsigned int>(color)].emplace_back(newPointA, newPointB, newPointC);
	}
	else
	{
		this->m2dTriangle[static_cast<unsigned int>(color)].emplace_back(pointA, pointB, pointC);
	}
}

void doom::graphics::DebugGraphics::DebugDraw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color)
{
	this->m3dTriangle[static_cast<unsigned int>(color)].emplace_back(pointA, pointB, pointC);

	//For Drawing both face
	this->m3dTriangle[static_cast<unsigned int>(color)].emplace_back(pointC, pointB, pointA);
}

