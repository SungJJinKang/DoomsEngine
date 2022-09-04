#include "Mesh.h"

#include "../Asset/ThreeDModelAsset.h"
#include "Matrix3x3.h"
#include <Rendering/Proxy/RenderingMeshProxy.h>
#include <ResourceManagement/Thread/RunnableThread/RenderThread.h>
#include <Rendering/Proxy/RenderingProxyManager.h>

void dooms::graphics::Mesh::CreateRenderingMeshProxy()
{
	D_ASSERT(MeshProxy == nullptr);

	RenderingMeshProxy::FRenderingMeshProxyInitializer Initializer;
	Initializer.MeshRawData = MeshRawData;
	Initializer.bDynamicWrite = DynamicWrite;

	MeshProxy = new RenderingMeshProxy();
	MeshProxy->InitRenderingMeshProxyInitializer(std::move(Initializer));

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
	if(MeshProxy != nullptr)
	{
		RenderingMeshProxy* const Proxy = MeshProxy;
		MeshProxy = nullptr;

		dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
		(
			[Proxy]()
			{
				RenderingProxyManager::GetSingleton()->DestroyedRenderingMeshProxyList.push_back(Proxy);
			}
		);
	}
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
	: MeshRawData(), DynamicWrite(false), MeshProxy(nullptr)
{
}

dooms::graphics::Mesh::Mesh(const graphics::FMeshRawData& InMeshRawData)
	:
	MeshRawData(InMeshRawData), DynamicWrite(false), MeshProxy(nullptr)
{
	CreateRenderingMeshProxy();
}

dooms::graphics::Mesh::Mesh(graphics::FMeshRawData&& InMeshRawData) noexcept
	:
	MeshRawData(std::move(InMeshRawData)), DynamicWrite(false), MeshProxy(nullptr)
{
	CreateRenderingMeshProxy();
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


dooms::graphics::Mesh& dooms::graphics::Mesh::operator=(const graphics::FMeshRawData& InMeshData)
{
	DestroyRenderingMeshProxy();

	MeshRawData = InMeshData;
	DynamicWrite = false;
	MeshProxy = nullptr;

	CreateRenderingMeshProxy();

	return *this;
}

dooms::graphics::Mesh& dooms::graphics::Mesh::operator=(graphics::FMeshRawData&& InMeshData) noexcept
{
	DestroyRenderingMeshProxy();

	MeshRawData = std::move(InMeshData);
	DynamicWrite = false;
	MeshProxy = nullptr;

	CreateRenderingMeshProxy();

	return *this;
}

const dooms::graphics::FMeshRawData& dooms::graphics::Mesh::GetMeshRawData() const
{
	return MeshRawData;
}

const dooms::physics::AABB3D& dooms::graphics::Mesh::GetBoundingBox() const
{
	return MeshRawData.BoundingBox;
}

const dooms::physics::Sphere& dooms::graphics::Mesh::GetBoundingSphere() const
{
	return MeshRawData.BoundingSphere;
}

/*void* dooms::graphics::Mesh::MapVertexDataBuffer
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
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MeshProxy]()
		{
			Proxy->UnmapElementBuffer();
		}
	);
}*/

UINT64 dooms::graphics::Mesh::GetNumOfIndices() const
{
	return MeshRawData.GetIndiceCount();
}

UINT64 dooms::graphics::Mesh::GetNumOfVertices() const
{
	return MeshRawData.VerticeCount;
}





