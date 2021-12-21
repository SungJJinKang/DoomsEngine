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
	std::scoped_lock<std::mutex> lock{ mMextex };

	mDebugMeshCount = 0;

	for (size_t i = 0; i < m2DPoint.size(); i++)
	{
		m2DPoint[i].clear();
	}

	for (size_t i = 0; i < m2DPoint.size(); i++)
	{
		m2DPoint[i].clear();
	}

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
	m2DMaterial{}, m3DMaterial{}, m2DPoint{}, m3DPoint{}, m2dLine{}, m3dLine{}, m2dTriangle{}, m3dTriangle{}
{
}



void dooms::graphics::DebugDrawer::Draw()
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	/// <summary>
	/// vector3 -> 3, vector4 -> 4
	/// </summary>
	INT32 offsetComponentCount{ 0 };
	UINT32 alreadyDrawedVertexCount{ 0 };

	if (m2DPoint.size() != 0)
	{
		for (size_t i = 0; i < m2DPoint.size(); i++)
		{
			UINT32 pointCount = static_cast<UINT32>(m2DPoint[i].size());
			if (pointCount > 0)
			{
				m2DMaterial->UseProgram();
				m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
				mDebugMesh.DrawArray(ePrimitiveType::POINTS, alreadyDrawedVertexCount, pointCount * 1);

				offsetComponentCount += pointCount * 3;
				alreadyDrawedVertexCount += pointCount * 1;
			}
		}
	}

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

	if (m3DPoint.size() != 0)
	{
		for (size_t i = 0; i < m3DPoint.size(); i++)
		{
			UINT32 pointCount = static_cast<UINT32>(m3DPoint[i].size());
			if (pointCount > 0)
			{
				m3DMaterial->UseProgram();
				m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(i)));
				mDebugMesh.DrawArray(ePrimitiveType::POINTS, alreadyDrawedVertexCount, pointCount * 1);

				offsetComponentCount += pointCount * 3;
				alreadyDrawedVertexCount += pointCount * 1;
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

void dooms::graphics::DebugDrawer::DebugDraw2DPoint(const math::Vector3& point, eColor color, bool drawInstantly)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	if (drawInstantly == false)
	{
		D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
		m2DPoint[static_cast<UINT32>(color)].emplace_back(point);
	}
	else
	{
		m2DMaterial->UseProgram();
		m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
		FLOAT32 data[3]{ point.x, point.y, point.z };
		mDebugMesh.BufferSubData(6, data, 0);
		mDebugMesh.DrawArray(ePrimitiveType::POINTS, 0, 1);
	}
}

void dooms::graphics::DebugDrawer::DebugDraw3DPoint(const math::Vector3& point, eColor color, bool drawInstantly)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	if (drawInstantly == false)
	{
		D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
		m3DPoint[static_cast<UINT32>(color)].emplace_back(point);
	}
	else
	{
		m3DMaterial->UseProgram();
		m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(color)));
		FLOAT32 data[3]{ point.x, point.y, point.z };
		mDebugMesh.BufferSubData(6, data, 0);
		mDebugMesh.DrawArray(ePrimitiveType::POINTS, 0, 1);
	}
}

void dooms::graphics::DebugDrawer::DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color, bool drawInstantly /*= false*/)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

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
	std::scoped_lock<std::mutex> lock{ mMextex };

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
	std::scoped_lock<std::mutex> lock{ mMextex };

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
	std::scoped_lock<std::mutex> lock{ mMextex };

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
	std::scoped_lock<std::mutex> lock{ mMextex };

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

void dooms::graphics::DebugDrawer::DebugDraw2DBox
(
	const math::Vector3& leftBottom, 
	const math::Vector3& rightTop,
	eColor color, bool drawInstantly
)
{
	{
		const math::Vector3 pointA{ leftBottom.x, rightTop.y , 0.0f };
		const math::Vector3 pointB{ leftBottom.x, leftBottom.y, 0.0f };
		const math::Vector3 pointC{ rightTop.x, leftBottom.y, 0.0f };

		DebugDraw2DTriangle(pointA, pointB, pointC, color, drawInstantly);
	}
	{
		const math::Vector3 pointA{ rightTop.x, leftBottom.y, 0.0f };
		const math::Vector3 pointB{ rightTop.x, rightTop.y, 0.0f };
		const math::Vector3 pointC{ leftBottom.x, rightTop.y, 0.0f };

		DebugDraw2DTriangle(pointA, pointB, pointC, color, drawInstantly);
	}
}

void dooms::graphics::DebugDrawer::DebugDraw2DTriangleScreenSpace
(
	const math::Vector3& pointA,
	const math::Vector3& pointB, 
	const math::Vector3& pointC, 
	eColor color, 
	bool drawInstantly
)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	math::Vector3 ndcPointA = math::Vector3(pointA.x / Graphics_Setting::GetScreenWidth(), pointA.y / Graphics_Setting::GetScreenHeight(), pointA.z);
	ndcPointA.x *= 2.0f;
	ndcPointA.y *= 2.0f;
	ndcPointA.x -= 1.0f;
	ndcPointA.y -= 1.0f;


	math::Vector3 ndcPointB = math::Vector3(pointB.x / Graphics_Setting::GetScreenWidth(), pointB.y / Graphics_Setting::GetScreenHeight(), pointB.z);
	ndcPointB.x *= 2.0f;
	ndcPointB.y *= 2.0f;
	ndcPointB.x -= 1.0f;
	ndcPointB.y -= 1.0f;


	math::Vector3 ndcPointC = math::Vector3(pointC.x / Graphics_Setting::GetScreenWidth(), pointC.y / Graphics_Setting::GetScreenHeight(), pointC.z);
	ndcPointC.x *= 2.0f;
	ndcPointC.y *= 2.0f;
	ndcPointC.x -= 1.0f;
	ndcPointC.y -= 1.0f;

	DebugDraw2DTriangle(ndcPointA, ndcPointB, ndcPointC, color);
}

void dooms::graphics::DebugDrawer::SetDrawInstantlyMaterial(Material* material)
{
	mDrawInstantlyMaterial = material;
}

void dooms::graphics::DebugDrawer::BufferVertexDataToGPU()
{
	std::scoped_lock<std::mutex> lock{ mMextex };

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
	std::scoped_lock<std::mutex> lock{ mMextex };

	const FLOAT32 intervalRadian = math::PI * 2 / 72.0f;


	const FLOAT32 deltaTheta = math::PI / 12;
	const FLOAT32 deltaPhi = 2 * math::PI / 10;



	math::Vector3 exVertex{ nullptr };
	math::Vector3 currentVertex{ nullptr };

	FLOAT32 theta{ 0 };
	for (UINT32 ring = 0; ring < 11; ring++) 
	{ //move to a new z - offset 

		FLOAT32 phi{ 0 };

		theta += deltaTheta;
		for (UINT32 point = 0; point < 11; point++) { // draw a ring
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
	for (UINT32 ring = 0; ring < 11; ring++) 
	{ //move to a new z - offset 

		FLOAT32 phi{ 0 };

		theta += deltaTheta;
		for (UINT32 point = 0; point < 11; point++) { // draw a ring
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
	std::scoped_lock<std::mutex> lock{ mMextex };

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