#include "MeshHelper.h"

#include "Asset/ThreeDModelAsset.h"
#include <Game/AssetManager/AssetManager.h>

namespace dooms::graphics::meshHelper
{
	static asset::ThreeDModelAsset* DefaultQuadThreeDModelAsset{ nullptr };

	static std::vector<MeshVertexData> GetQuadMeshVertexData(const math::Vector2& leftbottom, const math::Vector2& rightup)
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

		std::vector<MeshVertexData> MeshVertexDataList{};
		MeshVertexDataList.resize(6, nullptr);
		for(size_t i = 0 ; i < 6 ; i++)
		{
			MeshVertexDataList[i].mVertex = math::Vector3(QuadMeshData[5 * i + 0], QuadMeshData[5 * i + 1], QuadMeshData[5 * i + 2]);
			MeshVertexDataList[i].mTexCoord = math::Vector2(QuadMeshData[5 * i + 3], QuadMeshData[5 * i + 4]);
		}

		return MeshVertexDataList;
	}

	static asset::ThreeDModelAsset* GetQuadThreeDModelAssset(const math::Vector2& leftbottom, const math::Vector2& rightup)
	{
		std::vector<ThreeDModelMesh> threeDModelMeshes{};
		threeDModelMeshes.emplace_back(nullptr);

		threeDModelMeshes[0].mPrimitiveType = ePrimitiveType::TRIANGLES;
		threeDModelMeshes[0].mVertexArrayFlag = eVertexArrayFlag::VertexVector3 | eVertexArrayFlag::TexCoord;

		threeDModelMeshes[0].bHasIndices = false;
		
		std::vector<MeshVertexData> meshVertexData = GetQuadMeshVertexData(math::Vector2(-1.0f, -1.0f), math::Vector2(1.0f, 1.0f));
		threeDModelMeshes[0].mMeshVertexDatas = std::move(meshVertexData);

		std::unique_ptr<ThreeDModelNode> threeDModelNode = std::make_unique<ThreeDModelNode>(nullptr);
		threeDModelNode->mThreeDModelNodeParent = nullptr;
		threeDModelNode->mModelMeshIndexs.push_back(0);

		asset::ThreeDModelAsset* const threeDModelAsset = dooms::CreateDObject<asset::ThreeDModelAsset>(std::move(threeDModelMeshes), std::move(threeDModelNode));
		assetImporter::AssetManager::GetSingleton()->AddAssetToAssetContainer(threeDModelAsset);

		return threeDModelAsset;
	}
}

dooms::graphics::Mesh* dooms::graphics::meshHelper::GetQuadMesh()
{
	if (dooms::graphics::meshHelper::DefaultQuadThreeDModelAsset == nullptr)
	{
		DefaultQuadThreeDModelAsset = GetQuadThreeDModelAssset(math::Vector2(-1.0f, -1.0f), math::Vector2(1.0f, 1.0f));
		
	}

	return DefaultQuadThreeDModelAsset->GetMesh(0);
}

dooms::graphics::Mesh* dooms::graphics::meshHelper::GetQuadMesh(const math::Vector2& leftbottom, const math::Vector2& rightup)
{
	asset::ThreeDModelAsset* const threeDModelAsset = GetQuadThreeDModelAssset(leftbottom, rightup);

	return threeDModelAsset->GetMesh(0);
}
