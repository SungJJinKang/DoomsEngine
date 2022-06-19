#include "FMeshRawData.h"

dooms::graphics::FMeshRawData::FMeshRawData()
	:
	Data(nullptr),
	VerticeCount(0),
	Vertex(nullptr),
	TexCoord(nullptr),
	Normal(nullptr),
	Tangent(nullptr),
	mBitangent(nullptr)
{
}

dooms::graphics::FMeshRawData::FMeshRawData(const size_t VerticeCount)
	: FMeshRawData()
{
	Allocate(VerticeCount);
}

dooms::graphics::FMeshRawData::FMeshRawData(const FMeshRawData& MeshData)
	:
	Data(nullptr),
	VerticeCount(0),
	Vertex(nullptr),
	TexCoord(nullptr),
	Normal(nullptr),
	Tangent(nullptr),
	mBitangent(nullptr)
{
	Allocate(MeshData.VerticeCount);

	std::memcpy(Data, MeshData.Data, (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * VerticeCount);
}

dooms::graphics::FMeshRawData::FMeshRawData(FMeshRawData&& meshData) noexcept
	:
	Data(meshData.Data),
	VerticeCount(meshData.VerticeCount),
	Vertex(meshData.Vertex),
	TexCoord(meshData.TexCoord),
	Normal(meshData.Normal),
	Tangent(meshData.Tangent),
	mBitangent(meshData.mBitangent)
{
	meshData.Data = nullptr;
	meshData.VerticeCount = 0;
	meshData.Vertex = nullptr;
	meshData.TexCoord = nullptr;
	meshData.Normal = nullptr;
	meshData.Tangent = nullptr;
	meshData.mBitangent = nullptr;
}

dooms::graphics::FMeshRawData& dooms::graphics::FMeshRawData::operator=(const FMeshRawData& meshData)
{
	if (VerticeCount == meshData.VerticeCount)
	{
		std::memcpy(Data, meshData.Data, (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * VerticeCount);
	}
	else
	{
		Free();

		Allocate(meshData.VerticeCount);

		std::memcpy(Data, meshData.Data, (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * VerticeCount);
	}

	return *this;
}

dooms::graphics::FMeshRawData& dooms::graphics::FMeshRawData::operator=(FMeshRawData&& meshData) noexcept
{
	Free();

	Data = meshData.Data;
	VerticeCount = meshData.VerticeCount;
	Vertex = meshData.Vertex;
	TexCoord = meshData.TexCoord;
	Normal = meshData.Normal;
	Tangent = meshData.Tangent;
	mBitangent = meshData.mBitangent;

	meshData.Data = nullptr;
	meshData.VerticeCount = 0;
	meshData.Vertex = nullptr;
	meshData.TexCoord = nullptr;
	meshData.Normal = nullptr;
	meshData.Tangent = nullptr;
	meshData.mBitangent = nullptr;

	return *this;
}

dooms::graphics::FMeshRawData::~FMeshRawData()
{
	Free();
}

void dooms::graphics::FMeshRawData::Allocate(const size_t verticeCount)
{
	D_ASSERT(Data == nullptr);
	if (verticeCount != 0)
	{
		Data = reinterpret_cast<char*>(std::malloc((sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * verticeCount));
		VerticeCount = verticeCount;

		Vertex = reinterpret_cast<math::Vector3*>(Data);
		TexCoord = reinterpret_cast<math::Vector3*>((char*)Vertex + sizeof(math::Vector3) * verticeCount);
		Normal = reinterpret_cast<math::Vector3*>((char*)TexCoord + sizeof(math::Vector3) * verticeCount);
		Tangent = reinterpret_cast<math::Vector3*>((char*)Normal + sizeof(math::Vector3) * verticeCount);
		mBitangent = reinterpret_cast<math::Vector3*>((char*)Tangent + sizeof(math::Vector3) * verticeCount);
	}

}

unsigned long long dooms::graphics::FMeshRawData::GetAllocatedDataSize() const
{
	return (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * (unsigned long long)VerticeCount;
}

void dooms::graphics::FMeshRawData::Free()
{
	if (Data != nullptr)
	{
		free(Data);
	}

	VerticeCount = 0;
	Vertex = nullptr;
	TexCoord = nullptr;
	Normal = nullptr;
	Tangent = nullptr;
	mBitangent = nullptr;
}
