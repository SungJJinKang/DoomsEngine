#include "DebugDrawer.h"

#include <Graphics/Graphics_Core.h>
#include <Rendering/Graphics_Server.h>
#include <Asset/AssetManager/AssetManager.h>
#include <Rendering/Material/Material.h>
#include <Asset/ShaderAsset.h>
#include <Rendering/Buffer/eVertexArrayFlag.h>


#define MAX_DEBUG_VERTEX_COUNT 500000
#define RESERVE_PRIMITIVE_COUNT 30000

#define COLOR_UNIFORM_BUFFER_NAME "ColorData"

const std::string dooms::graphics::DebugDrawer::DEBUG_2D_SHADER{ "Debug2DShader.glsl" };
const std::string dooms::graphics::DebugDrawer::DEBUG_3D_SHADER{ "Debug3DShader.glsl" };

void dooms::graphics::DebugDrawer::SetIsVertexDataSendToGPUAtCurrentFrame(const bool isSet)
{
	bmIsVertexDataSendToGPUAtCurrentFrame = isSet;
}

bool dooms::graphics::DebugDrawer::GetIsVertexDataSendToGPUAtCurrentFrame() const
{
	return bmIsVertexDataSendToGPUAtCurrentFrame;
}

dooms::graphics::DebugDrawer::DebugDrawer()
	:
	m2DMaterial{},
	m3DMaterial{},
	mDebugPrimitiveContainers{},
	mDrawInstantlyMaterial(nullptr),
	bmIsVertexDataSendToGPUAtCurrentFrame(false),
	mDebugMeshCount(),
	mDebugMesh(),
	mMextex()
{
}



void dooms::graphics::DebugDrawer::Draw()
{
	std::scoped_lock<std::mutex> lock{ mMextex };
	
	UINT32 alreadyDrawedVertexCount{ 0 };

	dooms::graphics::UniformBufferObjectView* const _2DUBOView = m2DMaterial->GetUniformBufferObjectViewFromUBOName(COLOR_UNIFORM_BUFFER_NAME);
	dooms::graphics::UniformBufferObjectView* const _3DUBOView = m3DMaterial->GetUniformBufferObjectViewFromUBOName(COLOR_UNIFORM_BUFFER_NAME);

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		for(size_t colorIndex = 0 ; colorIndex < DebugPrimitiveContainer::COLOR_COUNT ; colorIndex++)
		{
			if (container->IsColoredVertexDataEmpty(static_cast<eColor>(colorIndex)) == false)
			{
				if(container->Is3DPrimitive() == false)
				{
					m2DMaterial->BindMaterial();
					_2DUBOView->SetVector4((UINT64)0, Color::GetColor(static_cast<eColor>(colorIndex)));
				}
				else
				{
					m3DMaterial->BindMaterial();
					_3DUBOView->SetVector4((UINT64)0, Color::GetColor(static_cast<eColor>(colorIndex)));
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
					m2DMaterial->BindMaterial();
					_2DUBOView->SetVector4((UINT64)0, container->GetSpecialColorData()[index]);
				}
				else
				{
					m3DMaterial->BindMaterial();
					_3DUBOView->SetVector4((UINT64)0, container->GetSpecialColorData()[index]);
				}

				mDebugMesh.DrawArray(container->GetPrimitiveType(), alreadyDrawedVertexCount, container->GetVertexCountPerPrimitive());

				alreadyDrawedVertexCount += container->GetVertexCountPerPrimitive();
			}

		}
		
	}
	

}

void dooms::graphics::DebugDrawer::Initialize()
{
	mDebugMesh.CreateBufferObject(MAX_DEBUG_VERTEX_COUNT * 3, MAX_DEBUG_VERTEX_COUNT, NULL, GraphicsAPI::ePrimitiveType::LINES, eVertexArrayFlag::VertexVector3, nullptr, 0, true);

	auto debug2DShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>(DebugDrawer::DEBUG_2D_SHADER);
	D_ASSERT(IsValid(debug2DShader));
	m2DMaterial = std::make_unique<Material>(debug2DShader);

	auto debug3DShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>(DebugDrawer::DEBUG_3D_SHADER);
	D_ASSERT(IsValid(debug3DShader));
	m3DMaterial = std::make_unique<Material>(debug3DShader);

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		container->ReserveVector(RESERVE_PRIMITIVE_COUNT);
	}
}

void dooms::graphics::DebugDrawer::PreRender()
{
}

void dooms::graphics::DebugDrawer::Render(dooms::Camera* const targetCamera)
{
	BufferVertexDataToGPU();
	Draw();
}

void dooms::graphics::DebugDrawer::PostRender()
{
	SetIsVertexDataSendToGPUAtCurrentFrame(false);

	std::scoped_lock<std::mutex> lock{ mMextex };

	mDebugMeshCount = 0;

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		container->ClearDatas();
	}
}

const char* dooms::graphics::DebugDrawer::GetRenderingDebuggerModuleName()
{
	return "DebugDrawer";
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

	math::Vector3 ndcPointA = math::Vector3(pointA.x / GraphicsSetting::GetScreenWidth(), pointA.y / GraphicsSetting::GetScreenHeight(), pointA.z);
	ndcPointA.x *= 2.0f;
	ndcPointA.y *= 2.0f;
	ndcPointA.x -= 1.0f;
	ndcPointA.y -= 1.0f;


	math::Vector3 ndcPointB = math::Vector3(pointB.x / GraphicsSetting::GetScreenWidth(), pointB.y / GraphicsSetting::GetScreenHeight(), pointB.z);
	ndcPointB.x *= 2.0f;
	ndcPointB.y *= 2.0f;
	ndcPointB.x -= 1.0f;
	ndcPointB.y -= 1.0f;


	math::Vector3 ndcPointC = math::Vector3(pointC.x / GraphicsSetting::GetScreenWidth(), pointC.y / GraphicsSetting::GetScreenHeight(), pointC.z);
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

	UINT64 offsetComponentCount{ 0 };
	UINT64 alreadyDrawedVertexCount{ 0 };

	dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapOption;
	if(graphics::GraphicsAPI::_GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		mapOption = dooms::graphics::GraphicsAPI::eMapBufferAccessOption::WRITE_ONLY;
	}
	else if (graphics::GraphicsAPI::_GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::D3D11)
	{
		mapOption = dooms::graphics::GraphicsAPI::eMapBufferAccessOption::WRITE_DISCARD;
	}
	else
	{
		ASSUME_ZERO;
	}

	char* const mapppedAddress = reinterpret_cast<char*>(mDebugMesh.MapVertexDataBuffer(mapOption));
	D_ASSERT(mapppedAddress != nullptr);

	for (DebugPrimitiveContainer* container : mDebugPrimitiveContainers.DebugPrimitiveContainers)
	{
		for (size_t colorIndex = 0; colorIndex < DebugPrimitiveContainer::COLOR_COUNT; colorIndex++)
		{
			if (container->IsColoredVertexDataEmpty(static_cast<eColor>(colorIndex)) == false)
			{
				const size_t primitiveCount = container->GetColoredPrimitiveCount(static_cast<eColor>(colorIndex));

				D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + primitiveCount * container->GetVertexCountPerPrimitive());
				const UINT64 dataSize = primitiveCount * container->GetComponentCountPerPrimitive() * container->GetComponentSize();
				const UINT64 offset = offsetComponentCount * sizeof(FLOAT32);

				std::memcpy(mapppedAddress + offset, container->GetColoredVertexData(static_cast<eColor>(colorIndex)), dataSize);

				offsetComponentCount += primitiveCount * container->GetComponentCountPerPrimitive();
				alreadyDrawedVertexCount += primitiveCount * container->GetVertexCountPerPrimitive();
			}
		}

		if (container->IsSpecialColoredVertexDataEmpty() == false)
		{
			const size_t primitiveCount = container->GetSpecialColoredPrimitiveCount();

			D_ASSERT(MAX_DEBUG_VERTEX_COUNT >= alreadyDrawedVertexCount + primitiveCount * container->GetVertexCountPerPrimitive());
			const UINT64 dataSize = primitiveCount * container->GetComponentCountPerPrimitive() * container->GetComponentSize();
			const UINT64 offset = offsetComponentCount * sizeof(FLOAT32);

			std::memcpy(mapppedAddress + offset, container->GetSpecialColoredVertexData(), dataSize);

			offsetComponentCount += primitiveCount * container->GetComponentCountPerPrimitive();
			alreadyDrawedVertexCount += primitiveCount * container->GetVertexCountPerPrimitive();
		}
	}

	mDebugMesh.UnmapVertexDataBuffer();
	
	bmIsVertexDataSendToGPUAtCurrentFrame = true;
}

void dooms::graphics::DebugDrawer::DebugDraw3DSphere(const math::Vector3& center, const float radius, const eColor color)
{
	const FLOAT32 intervalRadian = static_cast<FLOAT32>(math::PI * 2.0 / 72.0);


	const FLOAT32 deltaTheta = static_cast<FLOAT32>(math::PI / 12.0);
	const FLOAT32 deltaPhi = static_cast<FLOAT32>(2.0 * math::PI / 10.0);



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

void dooms::graphics::DebugDrawer::DebugDraw3DBox(const math::Vector3& minWorldPos, const math::Vector3& maxWorldPos, eColor color)
{
	// ChatGPT wrote this codes!

	const math::Vector3 Point1 = math::Vector3(minWorldPos.x, minWorldPos.y, minWorldPos.z);
	const math::Vector3 Point2 = math::Vector3(maxWorldPos.x, minWorldPos.y, minWorldPos.z);
	const math::Vector3 Point3 = math::Vector3(maxWorldPos.x, maxWorldPos.y, minWorldPos.z);
	const math::Vector3 Point4 = math::Vector3(minWorldPos.x, maxWorldPos.y, minWorldPos.z);
	const math::Vector3 Point5 = math::Vector3(minWorldPos.x, minWorldPos.y, maxWorldPos.z);
	const math::Vector3 Point6 = math::Vector3(maxWorldPos.x, minWorldPos.y, maxWorldPos.z);
	const math::Vector3 Point7 = math::Vector3(maxWorldPos.x, maxWorldPos.y, maxWorldPos.z);
	const math::Vector3 Point8 = math::Vector3(minWorldPos.x, maxWorldPos.y, maxWorldPos.z);
	
	DebugDraw3DLine(Point1, Point2, color);  // Edge 1-2
	DebugDraw3DLine(Point2, Point3, color);  // Edge 2-3
	DebugDraw3DLine(Point3, Point4, color);  // Edge 3-4
	DebugDraw3DLine(Point4, Point1, color);  // Edge 4-1
	DebugDraw3DLine(Point1, Point5, color);  // Edge 1-5
	DebugDraw3DLine(Point2, Point6, color);  // Edge 2-6
	DebugDraw3DLine(Point3, Point7, color);  // Edge 3-7
	DebugDraw3DLine(Point4, Point8, color);  // Edge 4-8
	DebugDraw3DLine(Point5, Point6, color);  // Edge 5-6
	DebugDraw3DLine(Point6, Point7, color);  // Edge 6-7
	DebugDraw3DLine(Point7, Point8, color);  // Edge 7-8
	DebugDraw3DLine(Point8, Point5, color);  // Edge 8-5
}


void dooms::graphics::DebugDrawer::DebugDraw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color /*= false*/)
{
	std::scoped_lock<std::mutex> lock{ mMextex };

	D_ASSERT_LOG(bmIsVertexDataSendToGPUAtCurrentFrame == false, "Debugging Vertex Data is already send to GPU");

	mDebugPrimitiveContainers._DebugPrimitive3DTriangleContainer.AddColoredTriangleData(pointA, pointB, pointC, color);
	mDebugPrimitiveContainers._DebugPrimitive3DTriangleContainer.AddColoredTriangleData(pointC, pointB, pointA, color);
}
