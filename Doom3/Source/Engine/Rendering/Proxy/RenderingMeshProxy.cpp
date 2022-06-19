#include "RenderingMeshProxy.h"

#include "Rendering/Buffer/eVertexArrayFlag.h"
#include <Math/JINMATH/Matrix3x3.h>
#include <Math/JINMATH/Matrix4x4.h>

UINT64 dooms::graphics::RenderingMeshProxy::BOUND_VERTEX_ARRAY_ID{ (UINT64)-1 };
const UINT32 dooms::graphics::RenderingMeshProxy::MAX_VERTEX_BUFFER_LAYOUT_COUNT{ 32 };
UINT64 dooms::graphics::RenderingMeshProxy::BOUND_VERTEX_BUFFER_ID[MAX_VERTEX_BUFFER_LAYOUT_COUNT]{ (UINT64)-1 };
UINT64 dooms::graphics::RenderingMeshProxy::BOUND_INDEX_BUFFER_ID{ (UINT64)-1 };

void dooms::graphics::RenderingMeshProxy::InitRenderingMeshProxyInitializer
(
	FRenderingMeshProxyInitializer& Initializer
)
{
	D_ASSERT(dooms::thread::IsInGameThread());

	DataComponentCount = Initializer.DataComponentCount;
	VertexCount = Initializer.VertexCount;
	MeshRawData = std::move(Initializer.MeshRawData);
	PrimitiveType = Initializer.PrimitiveType;
	VertexArrayFlag = Initializer.VertexArrayFlag;
	IndiceList = Initializer.IndiceList;
	bDynamicWrite = Initializer.bDynamicWrite;
	BoundingBox = Initializer.BoundingBox;
	BoundingSphere = Initializer.BoundingSphere;
}

void dooms::graphics::RenderingMeshProxy::CreateBufferObject()
{
	D_ASSERT(IsBufferGenerated() == false);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		CreateVertexArrayObjectIfNotExist();
	}

	const UINT32 stride = RenderingMeshProxy::GetStride(VertexArrayFlag);
	TotalStride = stride;

	BindVertexArrayObject(); // bind vertex array buffer

	D_DEBUG_LOG(eLogType::D_LOG, "%f", sizeof(FLOAT32) * DataComponentCount);
	VertexDataBuffer = GraphicsAPI::CreateBufferObject
	(
		GraphicsAPI::eBufferTarget::ARRAY_BUFFER,
		static_cast<UINT64>(sizeof(FLOAT32) * DataComponentCount),
		MeshRawData.data(),
		bDynamicWrite
	);
	BindVertexBufferObject();

#pragma warning( disable : 4312 )

	D_ASSERT(((VertexArrayFlag & eVertexArrayFlag::VertexVector2)) > 0 != ((VertexArrayFlag & eVertexArrayFlag::VertexVector3) > 0));

	UINT64 offset = 0;
	UINT32 vertexLayoutCount = 0;
	UINT32 layoutIndex = 0;
	if (VertexArrayFlag & eVertexArrayFlag::VertexVector2)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			//mVertex
			GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
			GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 2, sizeof(math::Vector2), offset);
		}

		VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
		VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector2);
		vertexLayoutCount++;
		layoutIndex++;

		offset += VertexCount * sizeof(math::Vector2);
	}

	if (VertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			//mVertex
			GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
			GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
		}

		VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
		VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
		vertexLayoutCount++;
		layoutIndex++;

		offset += VertexCount * sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			//mTexCoord
			GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
			GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
		}

		VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
		VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
		vertexLayoutCount++;
		layoutIndex++;

		offset += VertexCount * sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			//mNormal
			GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
			GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
		}

		VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
		VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
		vertexLayoutCount++;
		layoutIndex++;

		offset += VertexCount * sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			//mTangent
			GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
			GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
		}

		VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
		VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
		vertexLayoutCount++;
		layoutIndex++;

		offset += VertexCount * sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			//mBitangent
			GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
			GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
		}

		VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
		VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
		vertexLayoutCount++;
		layoutIndex++;

		offset += VertexCount * sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mTBN)
	{
		for (size_t i = 0; i < 3; i++)
		{
			//const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mBitangent - threeDModelMesh.mMeshDatas.mData);
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mBitangent
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(VertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
			}

			VertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			VertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;
			layoutIndex++;

			offset += VertexCount * sizeof(math::Vector3);
		}

	}

	VertexBufferLayoutCount = vertexLayoutCount;

#pragma warning( disable : 4244 )

	if (IndiceList.size() > 0)
	{
		ElementBufferObjectID = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, IndiceList.size() * sizeof(UINT32), NULL, false);
		GraphicsAPI::UpdateDataToBuffer(ElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, 0, IndiceList.size() * sizeof(UINT32), reinterpret_cast<const void*>(IndiceList.data()));
	}
}


void dooms::graphics::RenderingMeshProxy::Draw() const
{
	D_ASSERT(PrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		BindVertexArrayObject();
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		BindVertexBufferObject();
	}
	else
	{
		NEVER_HAPPEN;
	}

	if (IsElementBufferGenerated() == true)
	{// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
		// you don't need bind EBO everytime, EBO will be bound automatically when bind VAO
		BindIndexBufferObject();
		GraphicsAPI::DrawIndexed(PrimitiveType, IndiceList.size());
	}
	else
	{
		GraphicsAPI::Draw(PrimitiveType, 0, VertexCount);
	}
}

void dooms::graphics::RenderingMeshProxy::DrawArray(const INT32 startVertexLocation, const UINT32 VertexCount) const
{
	D_ASSERT(PrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		BindVertexArrayObject();
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		BindVertexBufferObject();
	}
	else
	{
		NEVER_HAPPEN;
	}

	GraphicsAPI::Draw(PrimitiveType, VertexCount, startVertexLocation);
}

void dooms::graphics::RenderingMeshProxy::DrawArray(const GraphicsAPI::ePrimitiveType primitiveType, const INT32 startVertexLocation, const INT32 VertexCount) const
{
	D_ASSERT(primitiveType != GraphicsAPI::ePrimitiveType::NONE);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		BindVertexArrayObject();
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		BindVertexBufferObject();
	}
	else
	{
		NEVER_HAPPEN;
	}

	GraphicsAPI::Draw(primitiveType, VertexCount, startVertexLocation);
}

UINT32 dooms::graphics::RenderingMeshProxy::GetStride(const UINT32 VertexArrayFlag)
{
	UINT32 offset = 0;

	if (VertexArrayFlag & eVertexArrayFlag::VertexVector2)
	{
		//mVertex
		offset += sizeof(math::Vector2);
	}

	if (VertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		offset += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		offset += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		offset += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		offset += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		offset += sizeof(math::Vector3);
	}

	if (VertexArrayFlag & eVertexArrayFlag::mTBN)
	{
		//mBitangent
		offset += sizeof(math::Matrix3x3);
	}

	return offset;
}

bool dooms::graphics::RenderingMeshProxy::IsBufferGenerated() const
{
	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		return VertexDataBuffer.IsValid() && VertexArrayObjectID.IsValid();
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		return VertexDataBuffer.IsValid();
	}
	else
	{
		NEVER_HAPPEN;
		return false;
	}
}

bool dooms::graphics::RenderingMeshProxy::IsElementBufferGenerated() const
{
	return ElementBufferObjectID.IsValid();
}

const dooms::physics::AABB3D& dooms::graphics::RenderingMeshProxy::GetBoundingBox() const
{
	return BoundingBox;
}

const dooms::physics::Sphere& dooms::graphics::RenderingMeshProxy::GetBoundingSphere() const
{
	return BoundingSphere;
}


const dooms::graphics::BufferID& dooms::graphics::RenderingMeshProxy::GetVertexArrayObjectID() const
{
	return VertexArrayObjectID;
}

const dooms::graphics::BufferID& dooms::graphics::RenderingMeshProxy::GetElementBufferObjectID() const
{
	return ElementBufferObjectID;
}

void* dooms::graphics::RenderingMeshProxy::MapVertexDataBuffer
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (VertexDataBuffer.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(VertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, mapBufferAccessOption);
	}
	D_ASSERT(bufferAddress != nullptr);

	return bufferAddress;
}

void dooms::graphics::RenderingMeshProxy::UnmapVertexDataBuffer()
{
	if (VertexDataBuffer.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(VertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER);
	}
}

void* dooms::graphics::RenderingMeshProxy::MapElementBuffer
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (VertexArrayObjectID.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(ElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, mapBufferAccessOption);
	}
	D_ASSERT(bufferAddress != nullptr);

	return bufferAddress;
}

void dooms::graphics::RenderingMeshProxy::UnmapElementBuffer()
{
	if (ElementBufferObjectID.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(ElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER);
	}
}

UINT64 dooms::graphics::RenderingMeshProxy::GetNumOfIndices() const
{
	return IndiceList.size();
}

UINT64 dooms::graphics::RenderingMeshProxy::GetNumOfVertices() const
{
	return VertexCount;
}

void dooms::graphics::RenderingMeshProxy::BindVertexArrayObject() const
{
	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(VertexArrayObjectID.IsValid() == true);
		if (BOUND_VERTEX_ARRAY_ID != VertexArrayObjectID.GetBufferID())
		{
			BOUND_VERTEX_ARRAY_ID = VertexArrayObjectID;
			dooms::graphics::GraphicsAPI::BindVertexArrayObject(VertexArrayObjectID);
		}
	}
}

void dooms::graphics::RenderingMeshProxy::BindVertexBufferObject() const
{
	D_ASSERT(VertexDataBuffer.IsValid() == true);
	D_ASSERT(TotalStride > 0);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (BOUND_VERTEX_BUFFER_ID[0] != VertexArrayObjectID.GetBufferID())
		{
			BOUND_VERTEX_BUFFER_ID[0] = VertexArrayObjectID;
			dooms::graphics::GraphicsAPI::BindVertexDataBuffer
			(
				VertexDataBuffer,
				0,
				TotalStride,
				0
			);
		}
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (UINT32 bufferLayoutIndex = 0; bufferLayoutIndex < VertexBufferLayoutCount; bufferLayoutIndex++)
		{
			if (BOUND_VERTEX_BUFFER_ID[bufferLayoutIndex] != VertexDataBuffer.GetBufferID())
			{
				BOUND_VERTEX_BUFFER_ID[bufferLayoutIndex] = VertexDataBuffer;
				dooms::graphics::GraphicsAPI::BindVertexDataBuffer
				(
					VertexDataBuffer,
					bufferLayoutIndex,
					VertexBufferLayouts[bufferLayoutIndex].mStride,
					VertexBufferLayouts[bufferLayoutIndex].mOffset
				);
			}
		}

	}
	else
	{
		NEVER_HAPPEN;
	}

}

void dooms::graphics::RenderingMeshProxy::BindVertexBufferObject(const UINT32 bindingPosition, const UINT32 stride, const UINT32 offset) const
{
	D_ASSERT(VertexDataBuffer.IsValid() == true);
	if (BOUND_VERTEX_BUFFER_ID[bindingPosition] != VertexDataBuffer.GetBufferID())
	{
		BOUND_VERTEX_BUFFER_ID[bindingPosition] = VertexDataBuffer;
		dooms::graphics::GraphicsAPI::BindVertexDataBuffer
		(
			VertexDataBuffer,
			bindingPosition,
			stride,
			offset
		);
	}
}

void dooms::graphics::RenderingMeshProxy::BindIndexBufferObject() const
{
	D_ASSERT(VertexDataBuffer.IsValid() == true);
	if (BOUND_INDEX_BUFFER_ID != ElementBufferObjectID.GetBufferID())
	{
		BOUND_INDEX_BUFFER_ID = ElementBufferObjectID;
		dooms::graphics::GraphicsAPI::BindBuffer(ElementBufferObjectID, 0, graphics::GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
	}
}

void dooms::graphics::RenderingMeshProxy::CreateVertexArrayObjectIfNotExist()
{
	D_ASSERT(graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL);

	if (VertexArrayObjectID.IsValid() == false)
	{
		VertexArrayObjectID = GraphicsAPI::CreateVertexArrayObject();
	}

	BindVertexArrayObject(); // bind vertex array buffer first
}