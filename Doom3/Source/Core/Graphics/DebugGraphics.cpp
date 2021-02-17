#include "DebugGraphics.h"

#include "../Game/AssetManager.h"
#include "Material.h"

void doom::graphics::DebugGraphics::Init()
{
	this->mDebugMesh.GenMeshBuffer(false);
	this->mDebugMesh.BufferData(MAX_DEBUG_LINE_COUNT * 6, NULL, ePrimitiveType::LINES, Mesh::eVertexArrayFlag::Vertex);

	auto debug2DShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>(DebugGraphics::DEBUG_2D_SHADER);
	this->m2DMaterial = std::make_unique<Material>(*debug2DShader);

	auto debug3DShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>(DebugGraphics::DEBUG_3D_SHADER);
	this->m3DMaterial = std::make_unique<Material>(*debug3DShader);
}

void doom::graphics::DebugGraphics::Reset()
{
	this->mDebugMeshCount = 0;
	this->bmIs2dLineDataAdded = false;
	this->bmIs3dLineDataAdded = false;
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

	khronos_intptr_t offsetInByte{ 0 };
	unsigned int twoDVertexCount{ 0 };
	unsigned int threeDVertexCount{ 0 };
	unsigned int vertexCount{ 0 };

	if (this->bmIs2dLineDataAdded == true || this->bmIs3dLineDataAdded == true)
	{
		this->mDebugMesh.BindVertexBufferObject();
		

		if (this->bmIs2dLineDataAdded)
		{
			this->m2DMaterial->UseProgram();
			for (size_t i = 0; i < this->m2dLine.size(); i++)
			{
				unsigned int lineCount = static_cast<unsigned int>(this->m2dLine[i].size());
				if (lineCount > 0)
				{
					this->m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));

					khronos_intptr_t dataCount = lineCount * 6;
					this->mDebugMesh.BufferSubData(dataCount, this->m2dLine[i].data(), offsetInByte);

					offsetInByte += dataCount * sizeof(float);
					vertexCount += lineCount * 2;

					D_ASSERT(MAX_DEBUG_LINE_COUNT * 2 >= vertexCount);
				}
			}

			twoDVertexCount = vertexCount;
		}

		if (this->bmIs3dLineDataAdded)
		{
			this->m3DMaterial->UseProgram();
			for (size_t i = 0; i < this->m3dLine.size(); i++)
			{
				unsigned int lineCount = static_cast<unsigned int>(this->m3dLine[i].size());
				if (lineCount > 0)
				{
					this->m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));

					GLsizeiptr dataCount = lineCount * 6;
					this->mDebugMesh.BufferSubData(dataCount, this->m3dLine[i].data(), offsetInByte);
					offsetInByte += dataCount * sizeof(float);
					vertexCount += lineCount * 2;

					D_ASSERT(MAX_DEBUG_LINE_COUNT * 2 >= vertexCount);
				}
			}
			threeDVertexCount = vertexCount - twoDVertexCount;
		}

		this->mDebugMesh.BindVertexArrayObject();
		if (twoDVertexCount > 0)
		{
			this->mDebugMesh.DrawArray(0, twoDVertexCount);
		}

		if (threeDVertexCount > 0)
		{
			this->mDebugMesh.DrawArray(twoDVertexCount * 12, threeDVertexCount);
		}
	}
}

void doom::graphics::DebugGraphics::DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color)
{
	this->m3dLine[static_cast<unsigned int>(color)].emplace_back(startWorldPos, endWorldPos);
	this->bmIs3dLineDataAdded = true;
}


void doom::graphics::DebugGraphics::DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color)
{
	this->m2dLine[static_cast<unsigned int>(color)].emplace_back(startNDCPos, startNDCPos);
	this->bmIs2dLineDataAdded = true;
}

void doom::graphics::DebugGraphics::DebugDrawSphere(const math::Vector3& centerWorldPos, float radius, eColor color)
{
}


