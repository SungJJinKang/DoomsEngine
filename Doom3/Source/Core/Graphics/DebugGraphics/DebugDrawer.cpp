#include "Core.h"
#include "../Graphics_Core.h"

#ifdef DEBUG_DRAWER

#include "DebugDrawer.h"

#define MAX_DEBUG_VERTEX_COUNT 500000
#define RESERVE_PRIMITIVE_COUNT 30000

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

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		container->ReserveVector(RESERVE_PRIMITIVE_COUNT);
	}
}

void dooms::graphics::DebugDrawer::Update()
{
}

void dooms::graphics::DebugDrawer::Reset()
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	mDebugMeshCount = 0;

	for(DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		container->ClearDatas();
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
	m2DMaterial{}, m3DMaterial{}
{
}



void dooms::graphics::DebugDrawer::Draw()
{
	std::scoped_lock<std::mutex> lock{ mMextex };
	
	UINT32 alreadyDrawedVertexCount{ 0 };

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		for(size_t colorIndex = 0 ; colorIndex < DebugPrimitiveContainer::COLOR_COUNT ; colorIndex++)
		{
			if (container->IsColoredVertexDataEmpty(static_cast<eColor>(colorIndex)) == false)
			{
				if(container->Is3DPrimitive() == false)
				{
					m2DMaterial->UseProgram();
					m2DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(colorIndex)));
				}
				else
				{
					m3DMaterial->UseProgram();
					m3DMaterial->SetVector4(0, Color::GetColor(static_cast<eColor>(colorIndex)));
				}

				const size_t primitiveCount = container->GetColoredPrimitiveCount(static_cast<eColor>(colorIndex));
				mDebugMesh.DrawArray(container->GetPrimitiveType(), alreadyDrawedVertexCount, primitiveCount * container->GetVertexCountPerPrimitive());

				alreadyDrawedVertexCount += primitiveCount * container->GetVertexCountPerPrimitive();
			}
		}
		if (container->IsSpecialColoredVertexDataEmpty() == false)
		{
			for (size_t index = 0; index < container->GetSpecialColoredPrimitiveCount(); index++)
			{
				if (container->Is3DPrimitive() == false)
				{
					m2DMaterial->UseProgram();
					m2DMaterial->SetVector4(0, container->GetSpecialColorData()[index]);
				}
				else
				{
					m3DMaterial->UseProgram();
					m3DMaterial->SetVector4(0, container->GetSpecialColorData()[index]);
				}

				mDebugMesh.DrawArray(container->GetPrimitiveType(), alreadyDrawedVertexCount, container->GetVertexCountPerPrimitive());

				alreadyDrawedVertexCount += container->GetVertexCountPerPrimitive();
			}

		}
		
	}
	

}

void dooms::graphics::DebugDrawer::DebugDraw2DPoint(const math::Vector3& point, eColor color)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive2DPointContainer.AddColoredPointData(point, color);;
}

void dooms::graphics::DebugDrawer::DebugDraw2DPoint(const math::Vector3& point, const math::Vector4 color)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive2DPointContainer.AddColoredPointData(point, color);;
}

void dooms::graphics::DebugDrawer::DebugDraw3DPoint(const math::Vector3& point, eColor color)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive3DPointContainer.AddColoredPointData(point, color);;
}

void dooms::graphics::DebugDrawer::DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color /*= false*/)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive3DLineContainer.AddColoredLineData(startWorldPos, endWorldPos, color);
}



/// <summary>
/// Why Use Vector3 not Vector2??
/// Debug mesh's Vertex Array Object have already define that Vector atribute have 3 component.
/// So For reducing complexity, Just use vector3
/// </summary>
/// <param name="startNDCPos"></param>
/// <param name="endNDCPos"></param>
/// <param name="color"></param>
void dooms::graphics::DebugDrawer::DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color /*= false*/)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive2DLineContainer.AddColoredLineData(startNDCPos, endNDCPos, color);
}


void dooms::graphics::DebugDrawer::DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color /*= false*/)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive2DTriangleContainer.AddColoredTriangleData(pointA, pointB, pointC, color);
}

void dooms::graphics::DebugDrawer::DebugDraw2DTriangle
(
	const math::Vector3& pointA, 
	const math::Vector3& pointB,
	const math::Vector3& pointC, 
	const math::Vector4 color
)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");
	mDebugPrimitiveContainers._DebugPrimitive2DTriangleContainer.AddColoredTriangleData(pointA, pointB, pointC, color);
}

void dooms::graphics::DebugDrawer::DebugDraw2DBox
(
	const math::Vector3& leftBottom, 
	const math::Vector3& rightTop,
	eColor color
)
{
	{
		const math::Vector3 pointA{ leftBottom.x, rightTop.y , 0.0f };
		const math::Vector3 pointB{ leftBottom.x, leftBottom.y, 0.0f };
		const math::Vector3 pointC{ rightTop.x, leftBottom.y, 0.0f };

		DebugDraw2DTriangle(pointA, pointB, pointC, color);
	}
	{
		const math::Vector3 pointA{ rightTop.x, leftBottom.y, 0.0f };
		const math::Vector3 pointB{ rightTop.x, rightTop.y, 0.0f };
		const math::Vector3 pointC{ leftBottom.x, rightTop.y, 0.0f };

		DebugDraw2DTriangle(pointA, pointB, pointC, color);
	}
}

void dooms::graphics::DebugDrawer::DebugDraw2DBox
(
	const math::Vector3& leftBottom, 
	const math::Vector3& rightTop,
	math::Vector4 color
)
{
	{
		const math::Vector3 pointA{ leftBottom.x, rightTop.y , 0.0f };
		const math::Vector3 pointB{ leftBottom.x, leftBottom.y, 0.0f };
		const math::Vector3 pointC{ rightTop.x, leftBottom.y, 0.0f };

		DebugDraw2DTriangle(pointA, pointB, pointC, color);
	}
	{
		const math::Vector3 pointA{ rightTop.x, leftBottom.y, 0.0f };
		const math::Vector3 pointB{ rightTop.x, rightTop.y, 0.0f };
		const math::Vector3 pointC{ leftBottom.x, rightTop.y, 0.0f };

		DebugDraw2DTriangle(pointA, pointB, pointC, color);
	}
}

/* not tested
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
*/

void dooms::graphics::DebugDrawer::SetDrawInstantlyMaterial(Material* material)
{
	mDrawInstantlyMaterial = material;
}

void dooms::graphics::DebugDrawer::BufferVertexDataToGPU()
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	UINT32 offsetComponentCount{ 0 };
	UINT32 alreadyDrawedVertexCount{ 0 };

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		for (size_t colorIndex = 0; colorIndex < DebugPrimitiveContainer::COLOR_COUNT; colorIndex++)
		{
			if (container->IsColoredVertexDataEmpty(static_cast<eColor>(colorIndex)) == false)
			{
				const size_t primitiveCount = container->GetColoredPrimitiveCount(static_cast<eColor>(colorIndex));

				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + primitiveCount * container->GetVertexCountPerPrimitive());
				mDebugMesh.BufferSubData(primitiveCount * container->GetComponentCountPerPrimitive(), container->GetColoredVertexData(static_cast<eColor>(colorIndex)), offsetComponentCount * sizeof(FLOAT32));

				offsetComponentCount += primitiveCount * container->GetComponentCountPerPrimitive();
				alreadyDrawedVertexCount += primitiveCount * container->GetVertexCountPerPrimitive();
			}
		}

		if (container->IsSpecialColoredVertexDataEmpty() == false)
		{
			const size_t primitiveCount = container->GetSpecialColoredPrimitiveCount();

			D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + primitiveCount * container->GetVertexCountPerPrimitive());
			mDebugMesh.BufferSubData(primitiveCount * container->GetComponentCountPerPrimitive(), container->GetSpecialColoredVertexData(), offsetComponentCount * sizeof(FLOAT32));

			offsetComponentCount += primitiveCount * container->GetComponentCountPerPrimitive();
			alreadyDrawedVertexCount += primitiveCount * container->GetVertexCountPerPrimitive();
		}
	}
	
	bmIsVertexDataSendToGPUAtCurrentFrame = true;
}

void dooms::graphics::DebugDrawer::DebugDraw3DSphere(const math::Vector3& center, const float radius, const eColor color)
{
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
				DebugDraw3DLine(exVertex, currentVertex, color);
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
				DebugDraw3DLine(exVertex, currentVertex, color);
			}
			exVertex = currentVertex;
		}
	}
}


void dooms::graphics::DebugDrawer::DebugDraw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color /*= false*/)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");

	mDebugPrimitiveContainers._DebugPrimitive3DTriangleContainer.AddColoredTriangleData(pointA, pointB, pointC, color);
	mDebugPrimitiveContainers._DebugPrimitive3DTriangleContainer.AddColoredTriangleData(pointC, pointB, pointA, color);
}

#endif