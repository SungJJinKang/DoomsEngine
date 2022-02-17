#include "meshBatchCreater.h"

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
	// Store mesh vertex data in world space coordinate and TBN
	// Check GbufferWriter_BatchedMesh_PBR file
	return nullptr;
}
