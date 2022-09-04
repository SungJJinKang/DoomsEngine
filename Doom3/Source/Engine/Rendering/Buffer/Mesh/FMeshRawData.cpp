#include "FMeshRawData.h"

#include "Rendering/Buffer/eVertexArrayFlag.h"
#include <Matrix3x3.h>

dooms::graphics::FMeshRawData::FMeshRawData()
	: bIsValidMesh(false)
{
}

dooms::graphics::FMeshRawData::FMeshRawData(const size_t InVerticeCount)
	: FMeshRawData()
{
	Allocate(InVerticeCount);
}

dooms::graphics::FMeshRawData::FMeshRawData(const FMeshRawData& InMeshRawData)
	:
	Data(nullptr),
	bIsValidMesh(false)
{
	Allocate(InMeshRawData.VerticeCount);

	std::memcpy(Data, InMeshRawData.Data, (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * VerticeCount);
}

dooms::graphics::FMeshRawData::FMeshRawData(FMeshRawData&& InMeshRawData) noexcept
	:
	Data(InMeshRawData.Data),
	VerticeCount(InMeshRawData.VerticeCount),
	Vertex(InMeshRawData.Vertex),
	TexCoord(InMeshRawData.TexCoord),
	Normal(InMeshRawData.Normal),
	Tangent(InMeshRawData.Tangent),
	Bitangent(InMeshRawData.Bitangent)
{
	InMeshRawData.Data = nullptr;
	InMeshRawData.VerticeCount = 0;
	InMeshRawData.Vertex = nullptr;
	InMeshRawData.TexCoord = nullptr;
	InMeshRawData.Normal = nullptr;
	InMeshRawData.Tangent = nullptr;
	InMeshRawData.Bitangent = nullptr;
}

dooms::graphics::FMeshRawData& dooms::graphics::FMeshRawData::operator=(const FMeshRawData& InMeshRawData)
{
	if (VerticeCount == InMeshRawData.VerticeCount)
	{
		std::memcpy(Data, InMeshRawData.Data, (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * VerticeCount);
	}
	else
	{
		Free();

		Allocate(InMeshRawData.VerticeCount);

		std::memcpy(Data, InMeshRawData.Data, (sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * VerticeCount);
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
	Bitangent = meshData.Bitangent;

	meshData.Data = nullptr;
	meshData.VerticeCount = 0;
	meshData.Vertex = nullptr;
	meshData.TexCoord = nullptr;
	meshData.Normal = nullptr;
	meshData.Tangent = nullptr;
	meshData.Bitangent = nullptr;

	return *this;
}

dooms::graphics::FMeshRawData::~FMeshRawData()
{
	Free();
}

void dooms::graphics::FMeshRawData::Allocate(const size_t InAllocatedVertexCount)
{
	D_ASSERT(Data == nullptr);
	if (InAllocatedVertexCount != 0)
	{
		Data = reinterpret_cast<char*>(std::malloc((sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3) + sizeof(math::Vector3)) * InAllocatedVertexCount));
		VerticeCount = InAllocatedVertexCount;

		Vertex = reinterpret_cast<math::Vector3*>(Data);
		TexCoord = reinterpret_cast<math::Vector3*>((char*)Vertex + sizeof(math::Vector3) * InAllocatedVertexCount);
		Normal = reinterpret_cast<math::Vector3*>((char*)TexCoord + sizeof(math::Vector3) * InAllocatedVertexCount);
		Tangent = reinterpret_cast<math::Vector3*>((char*)Normal + sizeof(math::Vector3) * InAllocatedVertexCount);
		Bitangent = reinterpret_cast<math::Vector3*>((char*)Tangent + sizeof(math::Vector3) * InAllocatedVertexCount);
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
	Bitangent = nullptr;
}

UINT32 dooms::graphics::FMeshRawData::GetStride() const
{
	UINT32 Stride = 0;

	if (VertexArrayFlag & eVertexArrayFlag::VERTEX_VECTOR2)
	{
		//mVertex
		Stride += sizeof(math::Vector2);
	}

	if (VertexArrayFlag & eVertexArrayFlag::VERTEX_VECTOR3)
	{
		//mVertex
		Stride += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::TEXCOORD)
	{
		//mTexCoord
		Stride += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::NORMAL)
	{
		//mNormal
		Stride += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::TANGENT)
	{
		//mTangent
		Stride += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::BI_TANGENT)
	{
		//mBitangent
		Stride += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::TBN)
	{
		//mBitangent
		Stride += sizeof(math::Matrix3x3);
	}

	return Stride;
}

UINT32 dooms::graphics::FMeshRawData::GetDataComponentCount() const
{
	UINT32 DataComponentCount = 0;

	if (VertexArrayFlag & eVertexArrayFlag::VERTEX_VECTOR2)
	{
		//mVertex
		DataComponentCount += 2;
	}

	if (VertexArrayFlag & eVertexArrayFlag::VERTEX_VECTOR3)
	{
		//mVertex
		DataComponentCount += 3;
	}

	if (VertexArrayFlag & eVertexArrayFlag::TEXCOORD)
	{
		//mTexCoord
		DataComponentCount += 3;
	}

	if (VertexArrayFlag & eVertexArrayFlag::NORMAL)
	{
		//mNormal
		DataComponentCount += 3;
	}

	if (VertexArrayFlag & eVertexArrayFlag::TANGENT)
	{
		//mTangent
		DataComponentCount += 3;
	}

	if (VertexArrayFlag & eVertexArrayFlag::BI_TANGENT)
	{
		//mBitangent
		DataComponentCount += 3;
	}

	if (VertexArrayFlag & eVertexArrayFlag::TBN)
	{
		//mBitangent
		DataComponentCount += 9;
	}

	return DataComponentCount;
}

UINT32 dooms::graphics::FMeshRawData::GetIndiceCount() const
{
	return bHasIndices ? MeshIndices.size() : 0;
}
