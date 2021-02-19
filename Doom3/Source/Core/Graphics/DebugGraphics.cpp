#include "DebugGraphics.h"

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
}



doom::graphics::DebugGraphics::DebugGraphics() : m2DMaterial{}, m3DMaterial{}, m2dLine{}, m3dLine{}
{
	for (size_t i = 0; i < this->m2dLine.size(); i++)
	{
		this->m2dLine[i].reserve(100);
	}

	for (size_t i = 0; i < this->m3dLine.size(); i++)
	{
		this->m3dLine[i].reserve(100);
	}
}

void doom::graphics::DebugGraphics::DrawDebug()
{
	//DRAW 2D FIRST

	/// <summary>
	/// vector3 -> 3, vector4 -> 4
	/// </summary>
	khronos_intptr_t exOffsetComponentCount{ 0 };
	khronos_intptr_t offsetComponentCount{ 0 };
	unsigned int alreadyDrawedVertexCount{ 0 };


	this->mDebugMesh.BindVertexArrayObject();
	this->mDebugMesh.BindVertexBufferObject();
	
	if (this->m2dLine.size())
	{
		this->m2DMaterial->UseProgram();
		for (size_t i = 0; i < this->m2dLine.size(); i++)
		{
			unsigned int lineCount = static_cast<unsigned int>(this->m2dLine[i].size());
			if (lineCount > 0)
			{
				this->m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));

				this->mDebugMesh.BufferSubData(lineCount * 6, this->m2dLine[i].data(), offsetComponentCount * sizeof(float));

				offsetComponentCount += lineCount * 6;
				alreadyDrawedVertexCount += lineCount * 2;

				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount);
			}
		}
		this->mDebugMesh.DrawArray(ePrimitiveType::LINES, exOffsetComponentCount, alreadyDrawedVertexCount);
		exOffsetComponentCount = offsetComponentCount;
	}

	if (this->m3dLine.size())
	{
		
		this->m3DMaterial->UseProgram();
		for (size_t i = 0; i < this->m3dLine.size(); i++)
		{
			unsigned int lineCount = static_cast<unsigned int>(this->m3dLine[i].size());
			if (lineCount > 0)
			{
				this->m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));

				this->mDebugMesh.BufferSubData(lineCount * 6, this->m3dLine[i].data(), offsetComponentCount * sizeof(float));
				
				offsetComponentCount += lineCount * 6;
				alreadyDrawedVertexCount += lineCount * 2;

				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount);
			}
		}
		this->mDebugMesh.DrawArray(ePrimitiveType::LINES, exOffsetComponentCount, alreadyDrawedVertexCount);
		exOffsetComponentCount = offsetComponentCount;
	}
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
void doom::graphics::DebugGraphics::DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color)
{
	this->m2dLine[static_cast<unsigned int>(color)].emplace_back(startNDCPos, startNDCPos);
}

void doom::graphics::DebugGraphics::DebugDrawSphere(const math::Vector3& centerWorldPos, float radius, eColor color)
{
}


