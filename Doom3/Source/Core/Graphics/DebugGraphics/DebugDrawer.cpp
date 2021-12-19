#include "Core.h"
#include "../Graphics_Core.h"

#ifdef DEBUG_DRAWER

#include "DebugDrawer.h"

#include "../Graphics_Server.h"
#include <Game/AssetManager/AssetManager.h>
#include "../Material/Material.h"
#include <IO/UserInput_Server.h>

void dooms::graphics::DebugDrawer::Init()
{
	mDebugMesh.GenMeshBuffer(false);
	mDebugMesh.BufferData(MAX_DEBUG_VERTEX_COUNT * 3, NULL, ePrimitiveType::LINES, eVertexArrayFlag::VertexVector3);


	auto debug2DShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>(DebugDrawer::DEBUG_2D_SHADER);
	m2DMaterial = std::make_unique<Material>(debug2DShader);

	auto debug3DShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>(DebugDrawer::DEBUG_3D_SHADER);
	m3DMaterial = std::make_unique<Material>(debug3DShader);
}

void dooms::graphics::DebugDrawer::Update()
{
}

void dooms::graphics::DebugDrawer::Reset()
{
	mDebugMeshCount = 0;
	for (size_t i = 0; i < m2dLine.size(); i++)
	{
		m2dLine[i].clear();
	}

	for (size_t i = 0; i < m3dLine.size(); i++)
	{
		m3dLine[i].clear();
	}

	for (size_t i = 0; i < m2dTriangle.size(); i++)
	{
		m2dTriangle[i].clear();
	}

	for (size_t i = 0; i < m3dTriangle.size(); i++)
	{
		m3dTriangle[i].clear();
	}
}



void dooms::graphics::DebugDrawer::SetIsVertexDataSendToGPUAtCurrentFrame(const bool isSet)
{
	bmIsVertexDataSendToGPUAtCurrentFrame = isSet;
}

bool dooms::graphics::DebugDrawer::GetIsVertexDataSendToGPUAtCurrentFrame() const
{
	return bmIsVertexDataSendToGPUAtCurrentFrame;
}

dooms::graphics::DebugDrawer::DebugDrawer() :
	m2DMaterial{}, m3DMaterial{}, m2dLine{}, m3dLine{}, m2dTriangle{}, m3dTriangle{}
{
}

void dooms::graphics::DebugDrawer::Draw()
{
	/// <summary>
	/// vector3 -> 3, vector4 -> 4
	/// </summary>
	INT32 offsetComponentCount{ 0 };
	UINT32 alreadyDrawedVertexCount{ 0 };

	if (m2dLine.size() != 0 && m2dTriangle.size() != 0)
	{
		for (size_t i = 0; i < m2dLine.size(); i++)
		{
			UINT32 lineCount = static_cast<UINT32>(m2dLine[i].size());
			if (lineCount > 0)
			{
				m2DMaterial->UseProgram();
				m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
				mDebugMesh.DrawArray(ePrimitiveType::LINES, alreadyDrawedVertexCount, lineCount * 2);

				offsetComponentCount += lineCount * 6;
				alreadyDrawedVertexCount += lineCount * 2;
			}
		}

		for (size_t i = 0; i < m2dTriangle.size(); i++)
		{
			UINT32 triangleCount = static_cast<UINT32>(m2dTriangle[i].size());
			if (triangleCount > 0)
			{
				m2DMaterial->UseProgram();
				m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
				mDebugMesh.DrawArray(ePrimitiveType::TRIANGLES, alreadyDrawedVertexCount, triangleCount * 3);

				offsetComponentCount += triangleCount * 9;
				alreadyDrawedVertexCount += triangleCount * 3;
			}
		}
	}

	if (m3dLine.size() != 0 && m3dTriangle.size() != 0)
	{
		for (size_t i = 0; i < m3dLine.size(); i++)
		{
			UINT32 lineCount = static_cast<UINT32>(m3dLine[i].size());
			if (lineCount > 0)
			{
				m3DMaterial->UseProgram();
				m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
				mDebugMesh.DrawArray(ePrimitiveType::LINES, alreadyDrawedVertexCount, lineCount * 2);

				offsetComponentCount += lineCount * 6;
				alreadyDrawedVertexCount += lineCount * 2;
			}
		}

		for (size_t i = 0; i < m3dTriangle.size(); i++)
		{
			UINT32 triangleCount = static_cast<UINT32>(m3dTriangle[i].size());
			if (triangleCount > 0)
			{
				m3DMaterial->UseProgram();
				m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
				mDebugMesh.DrawArray(ePrimitiveType::TRIANGLES, alreadyDrawedVertexCount, triangleCount * 3);

				offsetComponentCount += triangleCount * 9;
				alreadyDrawedVertexCount += triangleCount * 3;
			}
		}
	}

}

void dooms::graphics::DebugDrawer::DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color, bool drawInstantly /*= false*/)
{
	if (drawInstantly == false)
	{
		D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
		m3dLine[static_cast<UINT32>(color)].emplace_back(startWorldPos, endWorldPos);
	}
	else
	{
		m3DMaterial->UseProgram();
		m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
		FLOAT32 data[6]{ startWorldPos.x, startWorldPos.y, startWorldPos.z, endWorldPos.x, endWorldPos.y, endWorldPos.z };
		mDebugMesh.BufferSubData(6, data, 0);
		mDebugMesh.DrawArray(ePrimitiveType::LINES, 0, 2);
	}
}



/// <summary>
/// Why Use Vector3 not Vector2??
/// Debug mesh's Vertex Array Object have already define that Vector atribute have 3 component.
/// So For reducing complexity, Just use vector3
/// </summary>
/// <param name="startNDCPos"></param>
/// <param name="endNDCPos"></param>
/// <param name="color"></param>
void dooms::graphics::DebugDrawer::DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color, bool drawInstantly /*= false*/)
{
	if (drawInstantly == false)
	{
		D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
		m2dLine[static_cast<UINT32>(color)].emplace_back(startNDCPos, startNDCPos);
	}
	else
	{
		DebugDraw2DLineInstantly(startNDCPos, endNDCPos, color);
	}
}

void dooms::graphics::DebugDrawer::DebugDraw2DLineInstantly(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color)
{
	if (mDrawInstantlyMaterial != nullptr)
	{
		mDrawInstantlyMaterial->UseProgram();
		mDrawInstantlyMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
	}
	else
	{
		D_DEBUG_LOG(eLogType::D_WARNING, "Please set mDrawInstantlyMaterial");
		m2DMaterial->UseProgram();
		m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
	}
	
	FLOAT32 data[6]{ startNDCPos.x, startNDCPos.y, startNDCPos.z, endNDCPos.x, endNDCPos.y, endNDCPos.z };

	mDebugMesh.BufferSubData(6, data, 0);
	mDebugMesh.DrawArray(ePrimitiveType::LINES, 0, 2);
}



void dooms::graphics::DebugDrawer::DebugDraw2DTriangleInstantly(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color)
{
	if (mDrawInstantlyMaterial != nullptr)
	{
		D_DEBUG_LOG(eLogType::D_WARNING, "Please set mDrawInstantlyMaterial");
		mDrawInstantlyMaterial->UseProgram();
		mDrawInstantlyMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
	}
	else
	{
		m2DMaterial->UseProgram();
		m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
	}

	FLOAT32 data[9]{ pointA.x, pointA.y, pointA.z, pointB.x, pointB.y, pointB.z, pointC.x, pointC.y, pointC.z };
	mDebugMesh.BufferSubData(9, data, 0);
	mDebugMesh.DrawArray(ePrimitiveType::TRIANGLES, 0, 3);
}

void dooms::graphics::DebugDrawer::DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color, bool drawInstantly /*= false*/)
{
	if (drawInstantly == false)
	{
		D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
		m2dTriangle[static_cast<UINT32>(color)].emplace_back(pointA, pointB, pointC);
	}
	else
	{
		DebugDraw2DTriangleInstantly(pointA, pointB, pointC, color);
	}
}

void dooms::graphics::DebugDrawer::SetDrawInstantlyMaterial(Material* material)
{
	mDrawInstantlyMaterial = material;
}

void dooms::graphics::DebugDrawer::BufferVertexDataToGPU()
{
	UINT32 offsetComponentCount{ 0 };
	UINT32 alreadyDrawedVertexCount{ 0 };

	if (m2dLine.size() != 0 && m2dTriangle.size() != 0)
	{
		for (size_t i = 0; i < m2dLine.size(); i++)
		{
			UINT32 lineCount = static_cast<UINT32>(m2dLine[i].size());
			if (lineCount > 0)
			{
				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + lineCount * 2);
				mDebugMesh.BufferSubData(lineCount * 6, m2dLine[i].data(), offsetComponentCount * sizeof(FLOAT32));

				offsetComponentCount += lineCount * 6;
				alreadyDrawedVertexCount += lineCount * 2;
			}
		}

		for (size_t i = 0; i < m2dTriangle.size(); i++)
		{
			UINT32 triangleCount = static_cast<UINT32>(m2dTriangle[i].size());
			if (triangleCount > 0)
			{
				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + triangleCount * 3);
				mDebugMesh.BufferSubData(triangleCount * 9, m2dTriangle[i].data(), offsetComponentCount * sizeof(FLOAT32));

				offsetComponentCount += triangleCount * 9;
				alreadyDrawedVertexCount += triangleCount * 3;
			}
		}
	}

	if (m3dLine.size() != 0 && m3dTriangle.size() != 0)
	{
		for (size_t i = 0; i < m3dLine.size(); i++)
		{
			UINT32 lineCount = static_cast<UINT32>(m3dLine[i].size());
			if (lineCount > 0)
			{
				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + lineCount * 2);
				mDebugMesh.BufferSubData(lineCount * 6, m3dLine[i].data(), offsetComponentCount * sizeof(FLOAT32));

				offsetComponentCount += lineCount * 6;
				alreadyDrawedVertexCount += lineCount * 2;
			}
		}

		for (size_t i = 0; i < m3dTriangle.size(); i++)
		{
			UINT32 triangleCount = static_cast<UINT32>(m3dTriangle[i].size());
			if (triangleCount > 0)
			{
				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + triangleCount * 3);
				mDebugMesh.BufferSubData(triangleCount * 9, m3dTriangle[i].data(), offsetComponentCount * sizeof(FLOAT32));

				offsetComponentCount += triangleCount * 9;
				alreadyDrawedVertexCount += triangleCount * 3;
			}
		}
	}

	bmIsVertexDataSendToGPUAtCurrentFrame = true;

}

void dooms::graphics::DebugDrawer::DebugDraw3DSphere(const math::Vector3& center, const float radius, const eColor color, bool drawInstantly)
{
	const FLOAT32 intervalRadian = math::PI * 2 / 72.0f;


	FLOAT32 deltaTheta = math::PI / 12;
	FLOAT32 deltaPhi = 2 * math::PI / 10;



	math::Vector3 exVertex{ nullptr };
	math::Vector3 currentVertex{ nullptr };

	FLOAT32 theta{ 0 };
	for (INT32 ring = 0; ring < 11; ring++) { //move to a new z - offset 
		FLOAT32 phi{ 0 };

		theta += deltaTheta;
		for (INT32 point = 0; point < 11; point++) { // draw a ring
			phi += deltaPhi;
			currentVertex.x = sin(theta) * cos(phi) * radius;
			currentVertex.y = sin(theta) * sin(phi) * radius;
			currentVertex.z = cos(theta) * radius;
			currentVertex += center;

			if (point != 0)
			{
				DebugDraw3DLine(exVertex, currentVertex, color, drawInstantly);
			}
			exVertex = currentVertex;
		}
	}

	theta = 0;
	for (INT32 ring = 0; ring < 11; ring++) { //move to a new z - offset 
		FLOAT32 phi{ 0 };

		theta += deltaTheta;
		for (INT32 point = 0; point < 11; point++) { // draw a ring
			phi += deltaPhi;
			currentVertex.z = sin(theta) * cos(phi) * radius;
			currentVertex.y = sin(theta) * sin(phi) * radius;
			currentVertex.x = cos(theta) * radius;
			currentVertex += center;

			if (point != 0)
			{
				DebugDraw3DLine(exVertex, currentVertex, color, drawInstantly);
			}
			exVertex = currentVertex;
		}
	}
}


void dooms::graphics::DebugDrawer::DebugDraw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color, bool drawInstantly /*= false*/)
{
	if (drawInstantly == false)
	{
		D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");

		m3dTriangle[static_cast<UINT32>(color)].emplace_back(pointA, pointB, pointC);

		//For Drawing both face
		m3dTriangle[static_cast<UINT32>(color)].emplace_back(pointC, pointB, pointA);
	}
	else
	{
		m3DMaterial->UseProgram();
		m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
		FLOAT32 data[9]{ pointA.x, pointA.y, pointA.z, pointB.x, pointB.y, pointB.z, pointC.x, pointC.y, pointC.z };
		mDebugMesh.BufferSubData(9, data, 0);
		mDebugMesh.DrawArray(ePrimitiveType::TRIANGLES, 0, 3);
	}
}

#endif