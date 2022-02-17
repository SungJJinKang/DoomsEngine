#include "meshBatchCreater.h"

#include <vector>

#include <Vector3.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>

#include <Rendering/Buffer/Mesh.h>
#include <Rendering/Renderer/MeshRenderer.h>
#include <Asset/ThreeDModelAsset.h>

#include "Rendering/Buffer/eVertexArrayFlag.h"

namespace dooms::graphics::meshBatchCreater
{
	math::Matrix3x3 CalculateTBN
	(
		const math::Matrix4x4& modelMatrix, 
		const math::Vector3 normal,
		const math::Vector3 tangent,
		const math::Vector3 biTangent
	)
	{
		const math::Vector3 N = math::Vector3{ (modelMatrix * normal).normalized() };
		math::Vector3 T = math::Vector3{ (modelMatrix * tangent).normalized() };
		T = normalize(T - math::dot(N, T) * N);
		// vec3 B = cross(N, T);
		const math::Vector3 B = math::Vector3{ (modelMatrix * biTangent).normalized() };

		// TBN must form a right handed coord system.
		// Some models have symetric UVs. Check and fix.
		if (math::dot(cross(N, T), B) < 0.0)
		{
			T = T * -1.0;
		}

		return math::Matrix3x3(T, B, N);
	}

	struct DOOM_API D_STRUCT BatchedMeshData
	{
		D_PROPERTY()
		UINT64 mVerticeCount;

		D_PROPERTY()
		UINT64 mIndiceCount;

		D_PROPERTY()
		char* mData;

		D_PROPERTY()
		math::Vector3* mWorldSpaceVertex;

		D_PROPERTY()
		math::Vector3* mTexCoord; //support only one channel

		D_PROPERTY()
		math::Matrix3x3* mTBN;

		UINT32* mIndices;

		unsigned long long GetAllocatedMeshComponentCount() const
		{
			return ( (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Matrix3x3)) / sizeof(FLOAT32) ) * (UINT64)mVerticeCount;
		}
		unsigned long long GetAllocatedDataSize() const
		{
			return (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Matrix3x3)) * (UINT64)mVerticeCount + sizeof(UINT32) * (UINT64)mIndiceCount;
		}
		unsigned long long GetAllocatedDataSize(const size_t verticeCount, const size_t indiceCount) const
		{
			return ((sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Matrix3x3)) * (UINT64)verticeCount) + (sizeof(UINT32) * (UINT64)indiceCount);
		}
		BatchedMeshData()
			:
			mData(nullptr),
			mVerticeCount(0),
			mIndiceCount(0),
			mWorldSpaceVertex(nullptr),
			mTexCoord(nullptr),
			mTBN(nullptr),
			mIndices(nullptr)
		{
		}
		BatchedMeshData(const size_t verticeCount, const size_t indiceCount)
			: BatchedMeshData()
		{
			Allocate(verticeCount, indiceCount);
		}
		BatchedMeshData(const BatchedMeshData& meshData)
			:
			mData(nullptr),
			mVerticeCount(0),
			mIndiceCount(0),
			mWorldSpaceVertex(nullptr),
			mTexCoord(nullptr),
			mTBN(nullptr),
			mIndices(nullptr)
		{
			Allocate(meshData.mVerticeCount, meshData.mIndiceCount);

			std::memcpy(mData, meshData.mData, GetAllocatedDataSize());
		}
		BatchedMeshData(BatchedMeshData&& meshData) noexcept
			:
			mData(meshData.mData),
			mVerticeCount(meshData.mVerticeCount),
			mIndiceCount(meshData.mIndiceCount),
			mWorldSpaceVertex(meshData.mWorldSpaceVertex),
			mTexCoord(meshData.mTexCoord),
			mTBN(meshData.mTBN),
			mIndices(meshData.mIndices)
		{
			meshData.mData = nullptr;
			meshData.mVerticeCount = 0;
			meshData.mIndiceCount = 0;
			meshData.mWorldSpaceVertex = nullptr;
			meshData.mTexCoord = nullptr;
			meshData.mTBN = nullptr;
			meshData.mIndices = nullptr;
		}

		BatchedMeshData& operator=(const BatchedMeshData& meshData)
		{
			if (mVerticeCount == meshData.mVerticeCount && mIndiceCount == meshData.mIndiceCount)
			{
				std::memcpy(mData, meshData.mData, GetAllocatedDataSize());
			}
			else
			{
				Free();

				Allocate(meshData.mVerticeCount, meshData.mIndiceCount);

				std::memcpy(mData, meshData.mData, GetAllocatedDataSize());
			}

			return *this;
		}

		BatchedMeshData& operator=(BatchedMeshData&& meshData) noexcept
		{
			Free();

			mData = meshData.mData;
			mVerticeCount = meshData.mVerticeCount;
			mIndiceCount = meshData.mIndiceCount;
			mWorldSpaceVertex = meshData.mWorldSpaceVertex;
			mTexCoord = meshData.mTexCoord;
			mTBN = meshData.mTBN;
			mIndices = meshData.mIndices;

			meshData.mData = nullptr;
			meshData.mVerticeCount = 0;
			meshData.mIndiceCount = 0;
			meshData.mWorldSpaceVertex = nullptr;
			meshData.mTexCoord = nullptr;
			meshData.mTBN = nullptr;
			meshData.mIndices = nullptr;

			return *this;
		}
		~BatchedMeshData()
		{
			Free();
		}

		void Allocate(const UINT64 verticeCount, const UINT64 indiceCount)
		{
			D_ASSERT(mData == nullptr);
			D_ASSERT(verticeCount != 0 && indiceCount != 0);
			if (verticeCount != 0 && indiceCount != 0)
			{
				mData = reinterpret_cast<char*>(std::malloc(GetAllocatedDataSize(verticeCount, indiceCount)));
				mVerticeCount = verticeCount;
				mIndiceCount = indiceCount;
				
				mWorldSpaceVertex = reinterpret_cast<math::Vector3*>(mData);
				mTexCoord = reinterpret_cast<math::Vector3*>((char*)mWorldSpaceVertex + sizeof(math::Vector3) * verticeCount);
				mTBN = reinterpret_cast<math::Matrix3x3*>((char*)mTexCoord + sizeof(math::Vector3) * verticeCount);
				mIndices = reinterpret_cast<UINT32*>((char*)mTBN + sizeof(math::Matrix3x3) * verticeCount);
			}

		}
		void Free()
		{
			if (mData != nullptr)
			{
				free(mData);
			}

			mVerticeCount = 0;
			mIndiceCount = 0;
			mWorldSpaceVertex = nullptr;
			mTexCoord = nullptr;
			mTBN = nullptr;
			mIndices = nullptr;
		}

	};
}


dooms::graphics::Mesh* dooms::graphics::meshBatchCreater::CreateStaticBatchedMesh
(
	const std::vector<dooms::Renderer*>& staticRendererList
)
{
	// TODO : Implement this
	dooms::graphics::Mesh* batchMesh = nullptr;

	if(staticRendererList.empty() == false)
	{
		batchMesh = dooms::CreateDObject<dooms::graphics::Mesh>();

		BatchedMeshData batchedMeshData{};
		UINT64 indiceCount = 0;
		UINT64 verticeCount = 0;
		for(dooms::Renderer* renderer : staticRendererList)
		{
			dooms::MeshRenderer* meshRenderer = CastTo<MeshRenderer*>(renderer);
			if(IsValid(meshRenderer) && IsValid(meshRenderer->GetMesh()))
			{
				indiceCount += meshRenderer->GetMesh()->GetNumOfIndices();
				verticeCount += meshRenderer->GetMesh()->GetNumOfVertices();
			}
		}

		D_ASSERT(indiceCount != 0 && verticeCount != 0);
		if(indiceCount != 0 && verticeCount != 0)
		{
			batchedMeshData.Allocate(verticeCount, indiceCount);

			UINT64 currentVerticeIndex = 0;
			UINT64 currentIndiceIndex = 0;

			for (dooms::Renderer* renderer : staticRendererList)
			{
				dooms::MeshRenderer* meshRenderer = CastTo<MeshRenderer*>(renderer);
				if(IsValid(meshRenderer) && IsValid(meshRenderer->GetMesh()))
				{
					const dooms::ThreeDModelMesh* const targetThreeDModelMesh = meshRenderer->GetMesh()->GetTargetThreeDModelMesh();
					if(IsValid(targetThreeDModelMesh) && targetThreeDModelMesh->bHasIndices)
					{
						const math::Matrix4x4 modelMatrix = renderer->GetTransform()->GetModelMatrix();
						for(size_t verticeIndex = 0 ; verticeIndex < targetThreeDModelMesh->mMeshDatas.mVerticeCount ; verticeIndex++)
						{
							D_ASSERT(verticeIndex + currentVerticeIndex < batchedMeshData.mVerticeCount);
							batchedMeshData.mWorldSpaceVertex[verticeIndex + currentVerticeIndex] = modelMatrix * targetThreeDModelMesh->mMeshDatas.mVertex[verticeIndex];
							batchedMeshData.mTexCoord[verticeIndex + currentVerticeIndex] = targetThreeDModelMesh->mMeshDatas.mTexCoord[verticeIndex];
							batchedMeshData.mTBN[verticeIndex + currentVerticeIndex]
								=
								CalculateTBN(modelMatrix, targetThreeDModelMesh->mMeshDatas.mNormal[verticeIndex], targetThreeDModelMesh->mMeshDatas.mTangent[verticeIndex], targetThreeDModelMesh->mMeshDatas.mBitangent[verticeIndex]);
						}
						currentVerticeIndex += targetThreeDModelMesh->mMeshDatas.mVerticeCount;


						for (size_t indiceIndex = 0; indiceIndex < targetThreeDModelMesh->mMeshIndices.size(); indiceIndex++)
						{
							D_ASSERT(indiceIndex + currentIndiceIndex < batchedMeshData.mIndiceCount);
							batchedMeshData.mIndices[indiceIndex + currentIndiceIndex] = targetThreeDModelMesh->mMeshIndices[indiceIndex];
						}
						currentIndiceIndex += targetThreeDModelMesh->mMeshIndices.size();

					}
				}
			}
			
			
			batchMesh->CreateBufferObject
			(
				batchedMeshData.GetAllocatedMeshComponentCount(),
				batchedMeshData.mData,
				graphics::GraphicsAPI::ePrimitiveType::TRIANGLES,
				eVertexArrayFlag::VertexVector3 | eVertexArrayFlag::TexCoord | eVertexArrayFlag::mTBN,
				batchedMeshData.mIndices,
				batchedMeshData.mIndiceCount,
				false
			);
		}
	}

	return batchMesh;
}
