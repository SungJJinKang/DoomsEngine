#include "MeshHelper.h"

#include <cmath>

#include "Asset/ThreeDModelAsset.h"
#include <Asset/AssetManager/AssetManager.h>
#include "eVertexArrayFlag.h"

namespace dooms::graphics::meshHelper
{
	static asset::ThreeDModelAsset* DefaultQuadThreeDModelAsset{ nullptr };
	static asset::ThreeDModelAsset* DefaultTriangleThreeDModelAsset{ nullptr };

	static MeshData GetTriangleMeshVertexData(const TriangleType triangleType, const math::Vector2& pointA, const FLOAT32 width, const FLOAT32 height, const bool flipUV_Y)
	{
		FLOAT32 QuadMeshData[15];


		if(triangleType == TriangleType::BottomFlat)
		{
			QuadMeshData[0] = pointA.x;
			QuadMeshData[1] = pointA.y + height;
			QuadMeshData[2] = 0.0f;
			QuadMeshData[3] = 0.0f; 
			QuadMeshData[4] = (flipUV_Y == true) ? 1.0f : 0.0f; // UV Y
			QuadMeshData[5] = pointA.x;
			QuadMeshData[6] = pointA.y;
			QuadMeshData[7] = 0.0f;
			QuadMeshData[8] = 0.0f;
			QuadMeshData[9] = (flipUV_Y == true) ? 0.0f : 1.0f; // UV Y
			QuadMeshData[10] = pointA.x + width;
			QuadMeshData[11] = pointA.y;
			QuadMeshData[12] = 0.0f;
			QuadMeshData[13] = 1.0f;
			QuadMeshData[14] = (flipUV_Y == true) ? 0.0f : 1.0f; // UV Y
		}
		else if (triangleType == TriangleType::TopFlat)
		{
			QuadMeshData[0] = pointA.x;
			QuadMeshData[1] = pointA.y - height;
			QuadMeshData[2] = 0.0f;
			QuadMeshData[3] = 1.0f;
			QuadMeshData[4] = (flipUV_Y == true) ? 0.0f :1.0f; // UV Y
			QuadMeshData[5] = pointA.x;
			QuadMeshData[6] = pointA.y;
			QuadMeshData[7] = 0.0f;
			QuadMeshData[8] = 1.0f;
			QuadMeshData[9] = (flipUV_Y == true) ? 1.0f : 0.0f; // UV Y
			QuadMeshData[10] = pointA.x - width;
			QuadMeshData[11] = pointA.y;
			QuadMeshData[12] = 0.0f;
			QuadMeshData[13] = 0.0f;
			QuadMeshData[14] = (flipUV_Y == true) ? 1.0f : 0.0f; // UV Y
		}
		else
		{
			D_ASSERT(false);
		}

		MeshData MeshVertexDataList{ 3 };
		for (size_t i = 0; i < 3; i++)
		{
			MeshVertexDataList.mVertex[i] = math::Vector3(QuadMeshData[5 * i + 0], QuadMeshData[5 * i + 1], QuadMeshData[5 * i + 2]);
			MeshVertexDataList.mTexCoord[i] = math::Vector3(QuadMeshData[5 * i + 3], QuadMeshData[5 * i + 4], 0.0f);
		}

		return MeshVertexDataList;
	}

	static asset::ThreeDModelAsset* GetTriangleThreeDModelAssset(const TriangleType triangleType, const math::Vector2& pointA, const FLOAT32 width, const FLOAT32 height, const bool flipUV_Y)
	{
		std::vector<ThreeDModelMesh> threeDModelMeshes{};
		threeDModelMeshes.emplace_back(nullptr);

		threeDModelMeshes[0].mPrimitiveType = GraphicsAPI::ePrimitiveType::TRIANGLES;
		threeDModelMeshes[0].mVertexArrayFlag = eVertexArrayFlag::VertexVector3 | eVertexArrayFlag::TexCoord;

		threeDModelMeshes[0].mVerticeStride = 12;

		MeshData meshVertexData = GetTriangleMeshVertexData(triangleType, pointA, width, height, flipUV_Y);
		threeDModelMeshes[0].mMeshDatas = std::move(meshVertexData);
		threeDModelMeshes[0].mMeshIndices = { 0, 1, 2 };
		threeDModelMeshes[0].bHasIndices = true;

		math::Vector3 minX{nullptr};
		math::Vector3 maxX{nullptr};
		math::Vector3 boudingSphereCenter{nullptr};
		if(triangleType == TriangleType::BottomFlat)
		{
			minX = math::Vector3(pointA.x, pointA.y, 0.001f);
			maxX = math::Vector3(pointA.x + width, pointA.y + height, 0.001f);
			boudingSphereCenter = math::Vector3(width * 0.5f, height * 0.5f, 0.0f);
		}
		else if (triangleType == TriangleType::TopFlat)
		{
			minX = math::Vector3(pointA.x - width, pointA.y - height, 0.001f);
			maxX = math::Vector3(pointA.x, pointA.y, 0.001f);
			boudingSphereCenter = math::Vector3(-width * 0.5f, -height * 0.5f, 0.0f);
		}
		else
		{
			D_ASSERT(false);
		}
		
		threeDModelMeshes[0].mAABB3D = physics::AABB3D(minX, maxX);
		threeDModelMeshes[0].mSphere = physics::Sphere(boudingSphereCenter, math::Max(width, height) * 0.5f);

		threeDModelMeshes[0].mIsValidMesh = true;

		ThreeDModelNode* const threeDModelNode = dooms::CreateDObject<ThreeDModelNode>(nullptr);
		threeDModelNode->mThreeDModelNodeParent = nullptr;
		threeDModelNode->mModelMeshIndexs.push_back(0);

		asset::ThreeDModelAsset* const threeDModelAsset = dooms::CreateDObject<asset::ThreeDModelAsset>(std::move(threeDModelMeshes), threeDModelNode);
		assetImporter::AssetManager::GetSingleton()->AddAssetToAssetContainer(threeDModelAsset);


		return threeDModelAsset;
	}

	static MeshData GetQuadMeshVertexData(const math::Vector2& leftbottom, const math::Vector2& rightup, const bool flipUV_Y)
	{
		FLOAT32 QuadMeshData[]
		{
			leftbottom.x, rightup.y, 0.0f, 0.0f, (flipUV_Y == true) ? 1.0f : 0.0f /*UV Y*/,
			leftbottom.x, leftbottom.y, 0.0f, 0.0f,(flipUV_Y == true) ? 0.0f : 1.0f /*UV Y*/,
			rightup.x, leftbottom.y, 0.0f, 1.0f, (flipUV_Y == true) ? 0.0f : 1.0f /*UV Y*/,

			rightup.x, leftbottom.y, 0.0f, 1.0f, (flipUV_Y == true) ? 0.0f : 1.0f /*UV Y*/,
			rightup.x, rightup.y, 0.0f, 1.0f, (flipUV_Y == true) ? 1.0f : 0.0f /*UV Y*/,
			leftbottom.x, rightup.y, 0.0f, 0.0f, (flipUV_Y == true) ? 1.0f : 0.0f /*UV Y*/,
		};

		MeshData MeshVertexDataList{6};
		for(size_t i = 0 ; i < 6 ; i++)
		{
			MeshVertexDataList.mVertex[i] = math::Vector3(QuadMeshData[5 * i + 0], QuadMeshData[5 * i + 1], QuadMeshData[5 * i + 2]);
			MeshVertexDataList.mTexCoord[i] = math::Vector3(QuadMeshData[5 * i + 3], QuadMeshData[5 * i + 4], 0.0f);
		}

		return MeshVertexDataList;
	}

	static asset::ThreeDModelAsset* GetQuadThreeDModelAssset(const math::Vector2& leftbottom, const math::Vector2& rightup, const bool flipUV_Y)
	{
		std::vector<ThreeDModelMesh> threeDModelMeshes{};
		threeDModelMeshes.emplace_back(nullptr);

		threeDModelMeshes[0].mPrimitiveType = GraphicsAPI::ePrimitiveType::TRIANGLES;
		threeDModelMeshes[0].mVertexArrayFlag = eVertexArrayFlag::VertexVector3 | eVertexArrayFlag::TexCoord;

		threeDModelMeshes[0].mVerticeStride = 12;
		
		MeshData meshVertexData = GetQuadMeshVertexData(leftbottom, rightup, flipUV_Y);
		threeDModelMeshes[0].mMeshDatas = std::move(meshVertexData);
		threeDModelMeshes[0].mMeshIndices = { 0, 1, 2, 3, 4, 5 };
		threeDModelMeshes[0].bHasIndices = true;

		const math::Vector3 minX = math::Vector3(math::Min(leftbottom.x, rightup.x), math::Min(leftbottom.y, rightup.y), 0.001f);
		const math::Vector3 maxX = math::Vector3(math::Max(leftbottom.x, rightup.x), math::Max(leftbottom.y, rightup.y), 0.001f);
		threeDModelMeshes[0].mAABB3D = physics::AABB3D(minX, maxX);
		threeDModelMeshes[0].mSphere = physics::Sphere(math::Vector3(0.0f), 0.5f * math::Max(math::Abs(rightup.x - leftbottom.x), math::Abs(rightup.y - leftbottom.y)));

		threeDModelMeshes[0].mIsValidMesh = true;

		ThreeDModelNode* const threeDModelNode = dooms::CreateDObject<ThreeDModelNode>(nullptr);
		threeDModelNode->mThreeDModelNodeParent = nullptr;
		threeDModelNode->mModelMeshIndexs.push_back(0);

		asset::ThreeDModelAsset* const threeDModelAsset = dooms::CreateDObject<asset::ThreeDModelAsset>(std::move(threeDModelMeshes), threeDModelNode);
		assetImporter::AssetManager::GetSingleton()->AddAssetToAssetContainer(threeDModelAsset);


		return threeDModelAsset;
	}
}

dooms::graphics::Mesh* dooms::graphics::meshHelper::GetQuadMesh(const bool flipUV_Y)
{
	if (dooms::graphics::meshHelper::DefaultQuadThreeDModelAsset == nullptr)
	{
		DefaultQuadThreeDModelAsset = GetQuadThreeDModelAssset(math::Vector2(-1.0f, -1.0f), math::Vector2(1.0f, 1.0f), flipUV_Y);
		
	}

	return DefaultQuadThreeDModelAsset->GetMesh(0);
}

dooms::graphics::Mesh* dooms::graphics::meshHelper::GetQuadMesh(const math::Vector2& leftbottom, const math::Vector2& rightup, const bool flipUV_Y)
{
	asset::ThreeDModelAsset* const threeDModelAsset = GetQuadThreeDModelAssset(leftbottom, rightup, flipUV_Y);

	return threeDModelAsset->GetMesh(0);
}

dooms::graphics::Mesh* dooms::graphics::meshHelper::GetTriangleMesh(const TriangleType triangleType, const bool flipUV_Y)
{
	return GetTriangleThreeDModelAssset(triangleType, math::Vector2(-1.0f, -1.0f), 1.0f, 1.0f, flipUV_Y)->GetMesh(0);
}

dooms::graphics::Mesh* dooms::graphics::meshHelper::GetTriangleMesh
(
	const TriangleType triangleType,
	const math::Vector2& pointA,
	const FLOAT32 width,
	const FLOAT32 height, const bool flipUV_Y
)
{
	asset::ThreeDModelAsset* const threeDModelAsset = GetTriangleThreeDModelAssset(triangleType, pointA, width, height, flipUV_Y);

	return threeDModelAsset->GetMesh(0);
}

bool dooms::graphics::meshHelper::GetFlipOptionBasedOnCurrentGraphicsAPI()
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		return true;
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		return false;
	}
	else
	{
		ASSUME_ZERO;
	}
}
