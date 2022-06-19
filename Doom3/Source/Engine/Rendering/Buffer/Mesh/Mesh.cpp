#include "Mesh.h"

#include "../Asset/ThreeDModelAsset.h"
#include "Matrix3x3.h"
#include <Rendering/Proxy/RenderingMeshProxy.h>
#include <ResourceManagement/Thread/RunnableThread/RenderThread.h>
#include <Rendering/Proxy/RenderingProxyManager.h>

void dooms::graphics::Mesh::CreateRenderingMeshProxy()
{
	D_ASSERT(IsRenderingMeshProxyCreated() == false);

	RenderingMeshProxy::FRenderingMeshProxyInitializer Initializer;
	Initializer.DataComponentCount = DataComponentCount;
	Initializer.VertexCount = VertexCount;
	Initializer.MeshRawData = std::move(MeshRawData);
	Initializer.PrimitiveType = PrimitiveType;
	Initializer.VertexArrayFlag = VertexArrayFlag;
	Initializer.IndiceList = IndiceList;
	Initializer.bDynamicWrite = DynamicWrite;

	MeshProxy = new RenderingMeshProxy();
	MeshProxy->InitRenderingMeshProxyInitializer(Initializer);

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MeshProxy]()
		{
			RenderingProxyManager::GetSingleton()->AddedRenderingMeshProxyList.push_back(Proxy);
		}
	);
}

void dooms::graphics::Mesh::DestroyRenderingMeshProxy()
{
	D_ASSERT(IsRenderingMeshProxyCreated());

	RenderingMeshProxy* const Proxy = GetRenderingMeshProxy();
	MeshProxy = nullptr;

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy]()
		{
			RenderingProxyManager::GetSingleton()->DestroyedRenderingMeshProxyList.push_back(Proxy);
		}
	);
}

dooms::graphics::RenderingMeshProxy* dooms::graphics::Mesh::GetRenderingMeshProxy() const
{
	return MeshProxy;
}

bool dooms::graphics::Mesh::IsRenderingMeshProxyCreated() const
{
	return (MeshProxy != nullptr);
}

dooms::graphics::Mesh::Mesh()
	:
	DataComponentCount(),
	VertexCount(),
	MeshRawData(),
	PrimitiveType(),
	VertexArrayFlag(),
	IndiceList(),
	DynamicWrite()
{

}

dooms::graphics::Mesh::Mesh
(
	const UINT64 DataComponentCount,
	const UINT64 VertexCount,
	const std::vector<UINT8> MeshRawData,
	const GraphicsAPI::ePrimitiveType PrimitiveType,
	const UINT32 VertexArrayFlag,
	const std::vector<UINT32> IndiceList,
	const bool DynamicWrite
)
	:
	DataComponentCount{ DataComponentCount },
	VertexCount{ VertexCount },
	MeshRawData(MeshRawData),
	PrimitiveType(PrimitiveType),
	VertexArrayFlag(VertexArrayFlag),
	IndiceList(IndiceList),
	DynamicWrite(DynamicWrite)
{
	
}

dooms::graphics::Mesh::Mesh(const ThreeDModelMesh& ThreeDModelMesh)
	:
	mNumOfVertices{ 0 },
	mNumOfIndices{ 0 },
	mPrimitiveType{ GraphicsAPI::ePrimitiveType::NONE },
	mVertexBufferLayoutCount()
{
	CreateBufferObjectFromModelMesh(ThreeDModelMesh);

	ThreeDModelMesh.
}

dooms::graphics::Mesh::~Mesh()
{
	DestroyRenderingMeshProxy();
	
}

void dooms::graphics::Mesh::OnSetPendingKill()
{
	//Base::OnSetPendingKill();

	DestroyRenderingMeshProxy();
}


dooms::graphics::Mesh& dooms::graphics::Mesh::operator=(const ThreeDModelMesh& threeDModelMesh)
{
	DestroyUniformBufferProxy();
	
	CreateBufferObjectFromModelMesh(threeDModelMesh);
	return *this;
}

const dooms::physics::AABB3D& dooms::graphics::Mesh::GetBoundingBox() const
{
	return mAABB3D;
}

const dooms::physics::Sphere& dooms::graphics::Mesh::GetBoundingSphere() const
{
	return mSphere;
}

void* dooms::graphics::Mesh::MapVertexDataBuffer
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (mVertexDataBuffer.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(mVertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, mapBufferAccessOption);
	}
	D_ASSERT(bufferAddress != nullptr);

	return bufferAddress;
}

void dooms::graphics::Mesh::UnmapVertexDataBuffer()
{
	if(mVertexDataBuffer.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mVertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER);
	}
}

void* dooms::graphics::Mesh::MapElementBuffer
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (mVertexArrayObjectID.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, mapBufferAccessOption);
	}
	D_ASSERT(bufferAddress != nullptr);

	return bufferAddress;
}

void dooms::graphics::Mesh::UnmapElementBuffer()
{
	if (mElementBufferObjectID.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER);
	}
}

UINT64 dooms::graphics::Mesh::GetNumOfIndices() const
{
	return NumOfIndices;
}

UINT64 dooms::graphics::Mesh::GetNumOfVertices() const
{
	return mNumOfVertices;
}





