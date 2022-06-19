#include "RenderingUniformBufferProxy.h"

UINT64 dooms::graphics::RenderingUniformBufferProxy::BOUND_UNIFORM_BUFFER_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_UNIFORM_BUFFER_SLOT_COUNT]{ (UINT64)-1 };

dooms::graphics::RenderingUniformBufferProxy::~RenderingUniformBufferProxy()
{
	DeleteBuffers();
}

void dooms::graphics::RenderingUniformBufferProxy::InitUniformBufferProxy(FRenderingUniformBufferProxyInitializer& Initializer)
{
	UniformBufferName = Initializer.UniformBufferName;
	UniformBufferSize = Initializer.UniformBufferSize;
	DefaultBindingPoint = Initializer.DefaultBindingPoint;
	UniformVariableInfos = std::move(Initializer.UniformVariableInfos);
}

void dooms::graphics::RenderingUniformBufferProxy::DeleteBuffers()
{
	if (UniformBufferObject.IsValid())
	{
		dooms::graphics::GraphicsAPI::DestroyBuffer(UniformBufferObject);
		UniformBufferObject.Reset();
	}

	if (UniformBufferLocalBuffer != nullptr)
	{
		UniformBufferLocalBuffer.reset();
	}
	
	UniformBufferSize = 0;
	DefaultBindingPoint = 0;
}

void dooms::graphics::RenderingUniformBufferProxy::BindBuffer(const UINT32 BindingPoint,const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage) const noexcept
{
	D_ASSERT(UniformBufferObject.IsValid() == true);
	if (IsBufferGenerated() == true)
	{
		if (BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(TargetPipeLineStage)][BindingPoint] != UniformBufferObject.GetBufferID())
		{
			BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(TargetPipeLineStage)][BindingPoint] = UniformBufferObject.GetBufferID();
			GraphicsAPI::BindConstantBuffer(UniformBufferObject, BindingPoint, TargetPipeLineStage);
		}
	}
}

void dooms::graphics::RenderingUniformBufferProxy::UnBindBuffer(const UINT32 BindingPoint, const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage) const noexcept
{
	if (BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(TargetPipeLineStage)][BindingPoint] != 0)
	{
		BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(TargetPipeLineStage)][BindingPoint] = 0;
		GraphicsAPI::BindConstantBuffer(0, BindingPoint, TargetPipeLineStage);
	}
}

void dooms::graphics::RenderingUniformBufferProxy::UpdateLocalBuffer(const void* const SourceData,const UINT64 OffsetInUniformBlock, const UINT64 SizeOfSourceData)
{
	D_ASSERT(IsBufferGenerated() == true);
	D_ASSERT_LOG(static_cast<UINT64>(OffsetInUniformBlock) + static_cast<UINT64>(SizeOfSourceData) <= UniformBufferSize, "Updated data is out of range");

	D_ASSERT(UniformBufferLocalBuffer);
	UpdateLocalBuffer_Internal(SourceData, OffsetInUniformBlock, SizeOfSourceData);
	bIsLocalBufferDirty = true;
}

void dooms::graphics::RenderingUniformBufferProxy::UpdateLocalBufferToGPU() noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	if ((bIsLocalBufferDirty == true) && (IsBufferGenerated() == true))
	{
		D_ASSERT(UniformBufferLocalBuffer);
		UpdateDataToGPU_Internal(UniformBufferLocalBuffer.get(), 0, UniformBufferSize);
		bIsLocalBufferDirty = false;
	}
}

UINT64 dooms::graphics::RenderingUniformBufferProxy::GetUniformVariableOffset(const char* const TargetVariableName) const
{
	size_t Offset = 0;

	D_ASSERT(IsBufferGenerated() == true);
	auto Node = UniformVariableInfos.find(TargetVariableName);

	D_DEBUG_LOG(eLogType::D_ERROR, "Fail to find uniform variable ( %s ) from uniform buffer object", TargetVariableName);
	D_ASSERT(Node != UniformVariableInfos.end());

	if (Node != UniformVariableInfos.end())
	{
		Offset = Node->second.mOffset;
	}
	return Offset;
}

void dooms::graphics::RenderingUniformBufferProxy::UpdateDataToGPU(const void* const SourceData, const UINT64 OffsetInUniformBlock, const UINT64 SizeOfSourceData) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	UpdateLocalBuffer_Internal(SourceData, OffsetInUniformBlock, SizeOfSourceData);
	UpdateDataToGPU_Internal(SourceData, OffsetInUniformBlock, SizeOfSourceData);
}

void dooms::graphics::RenderingUniformBufferProxy::UpdateDataToGPU(const void* const SourceData, const char* const TargetVariableName, const UINT64 SizeOfSourceData) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	D_DEBUG_LOG(eLogType::D_WARNING, "Uniform buffer object is updated with string variable name. This is slow operation. Please pass offset directly");
	const UINT64 Offset = GetUniformVariableOffset(TargetVariableName);

	UpdateLocalBuffer_Internal(SourceData, Offset, SizeOfSourceData);
	UpdateDataToGPU_Internal(SourceData, Offset, SizeOfSourceData);
}

bool dooms::graphics::RenderingUniformBufferProxy::IsBufferGenerated() const
{
	return UniformBufferObject.IsValid();
}

const std::string& dooms::graphics::RenderingUniformBufferProxy::GetUniformBufferName() const
{
	return UniformBufferName;
}

UINT64 dooms::graphics::RenderingUniformBufferProxy::GetUniformBufferSize() const
{
	return UniformBufferSize;
}

UINT32 dooms::graphics::RenderingUniformBufferProxy::GetDefaultBindingPoint() const
{
	return DefaultBindingPoint;
}

void dooms::graphics::RenderingUniformBufferProxy::UpdateLocalBuffer_Internal(const void* sourceData,const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData)
{
	D_ASSERT(IsBufferGenerated() == true);

	std::memcpy(UniformBufferLocalBuffer.get() + offsetInUniformBlock, sourceData, sizeOfSourceData);
}

void dooms::graphics::RenderingUniformBufferProxy::UpdateDataToGPU_Internal(const void* sourceData,const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	GraphicsAPI::UpdateDataToBuffer(UniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offsetInUniformBlock, sizeOfSourceData, sourceData);
}

void dooms::graphics::RenderingUniformBufferProxy::GenerateUniformBufferObject(const void* const InitialData)
{
	D_ASSERT(IsBufferGenerated() == false); // prevent overlap generating buffer
	
	UniformBufferObject = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, UniformBufferSize, InitialData, false /* if you*/);
	
	if (UniformBufferLocalBuffer)
	{
		UniformBufferLocalBuffer.reset();
	}

	UniformBufferLocalBuffer = std::make_unique<UINT8[]>(UniformBufferSize);
	std::memset(UniformBufferLocalBuffer.get(), 0x00, UniformBufferSize);
}
