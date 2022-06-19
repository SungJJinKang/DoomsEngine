#include "UniformBufferObject.h"

#include "Rendering/Proxy/RenderingUniformBufferProxy.h"
#include "ResourceManagement/Thread/RunnableThread/RenderThread.h"
#include "Rendering/Proxy/RenderingProxyManager.h"


dooms::graphics::UniformBufferObject::UniformBufferObject()
	:
	UniformBlockName(), UniformBufferSize(), DefaultBindingPoint(), UniformBufferMemberList(), UniformBufferProxy(nullptr)
{
	AddToRootObjectList();
}

dooms::graphics::UniformBufferObject::UniformBufferObject
(
	const std::string& uniformBlockName,
	const UINT64 uniformBufferSize,
	const UINT32 defaultBindingPoint, 
	const void* const initialData,
	const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
)
	:
	UniformBlockName(), UniformBufferSize(), DefaultBindingPoint(), UniformBufferMemberList(), UniformBufferProxy(nullptr)
{
	AddToRootObjectList();
	InitializeUniformBufferObject(uniformBlockName, uniformBufferSize, defaultBindingPoint, initialData, uboMembers);
}

dooms::graphics::UniformBufferObject::~UniformBufferObject()
{
	if (UniformBufferProxy != nullptr)
	{
		DestroyUniformBufferProxy();
	}
}

void dooms::graphics::UniformBufferObject::InitializeUniformBufferObject
(
	const std::string& uniformBlockName,
	const UINT64 uniformBufferSize,
	const UINT32 defaultBindingPoint,
	const void* const initialData,
	const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
)
{
	UniformBlockName = uniformBlockName;
	UniformBufferSize = uniformBufferSize;
	DefaultBindingPoint = defaultBindingPoint;
	if(uboMembers != nullptr)
	{
		UniformBufferMemberList = *uboMembers;
	}
	
	CreateRenderingUniformBufferProxy();
	GenerateUniformBufferObject(initialData, uniformBufferSize);
}

std::string dooms::graphics::UniformBufferObject::GetUniformBlockName()
{
	return UniformBlockName;
}

const std::string& dooms::graphics::UniformBufferObject::GetUniformBlockName() const
{
	return UniformBlockName;
}

void dooms::graphics::UniformBufferObject::DestroyUniformBufferProxy()
{
	RenderingUniformBufferProxy* const Proxy = UniformBufferProxy;
	UniformBufferProxy = nullptr;

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy]()
		{
			dooms::graphics::RenderingProxyManager::GetSingleton()->DestroyedRenderingUniformBufferProxyList.push_back(Proxy);
		}
	);
}

void dooms::graphics::UniformBufferObject::BindBuffer(const UINT32 bindingPoint,const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) noexcept
{
	D_ASSERT(IsUniformBufferProxyCreated());

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy, BindingPoint = bindingPoint, TargetPipeLineStage = targetPipeLineStage]()
		{
			Proxy->BindBuffer(BindingPoint, TargetPipeLineStage);
		}
	);
}

void dooms::graphics::UniformBufferObject::UnBindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) noexcept
{
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy, BindingPoint = bindingPoint, TargetPipeLineStage = targetPipeLineStage]()
		{
			Proxy->UnBindBuffer(BindingPoint, TargetPipeLineStage);
		}
	);
}

void dooms::graphics::UniformBufferObject::UpdateLocalBufferToGPU() noexcept
{
	D_ASSERT(IsUniformBufferProxyCreated());

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy]()
		{
			Proxy->UpdateLocalBufferToGPU();
		}
	);
}

void dooms::graphics::UniformBufferObject::UpdateDataToGPU(const void* sourceData, const UINT64 offsetInUniformBlock,const UINT64 sizeOfSourceData) noexcept
{
	D_ASSERT(IsUniformBufferProxyCreated());

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy, SourceData = sourceData, OffsetInUniformBlock = offsetInUniformBlock, SizeOfSourceData = sizeOfSourceData]()
		{
			Proxy->UpdateDataToGPU(SourceData, OffsetInUniformBlock, SizeOfSourceData);
		}
	);
}

void dooms::graphics::UniformBufferObject::UpdateDataToGPU(const void* sourceData, const char* const targetVariableName,const UINT64 sizeOfSourceData) noexcept
{
	D_ASSERT(IsUniformBufferProxyCreated());

	std::string TargetVariableName{ targetVariableName };

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy, SourceData = sourceData, TargetVariableName, SizeOfSourceData = sizeOfSourceData]()
		{
			Proxy->UpdateDataToGPU(SourceData, TargetVariableName.c_str(), SizeOfSourceData);
		}
	);
}


void dooms::graphics::UniformBufferObject::UpdateLocalBuffer
(
	const void* sourceData,
	const UINT64 offsetInUniformBlock,
	const UINT64 sizeOfSourceData
)
{
	D_ASSERT(IsUniformBufferProxyCreated());

	std::vector<UINT8> SourceDataBuffer{};
	SourceDataBuffer.resize(sizeOfSourceData);
	std::memcpy(SourceDataBuffer.data(), sourceData, sizeOfSourceData);

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy, SourceData = std::move(SourceDataBuffer), OffsetInUnifromBlock = offsetInUniformBlock, SizeOfSourceData = sizeOfSourceData]()
	{
		Proxy->UpdateLocalBuffer(SourceData.data(), OffsetInUnifromBlock, SizeOfSourceData);
	}
	);
}


dooms::graphics::RenderingUniformBufferProxy* dooms::graphics::UniformBufferObject::GetUniformBufferProxy() const
{
	return UniformBufferProxy;
}

bool dooms::graphics::UniformBufferObject::IsUniformBufferProxyCreated() const
{
	return (UniformBufferProxy != nullptr);
}

void dooms::graphics::UniformBufferObject::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	if (UniformBufferProxy != nullptr)
	{
		DestroyUniformBufferProxy();
	}
	
}

void dooms::graphics::UniformBufferObject::CreateRenderingUniformBufferProxy()
{
	D_ASSERT(IsUniformBufferProxyCreated() == false);
	
	UniformBufferProxy = new RenderingUniformBufferProxy();

	RenderingUniformBufferProxy::FRenderingUniformBufferProxyInitializer Initializer{};
	Initializer.UniformBufferName = GetUniformBlockName();
	Initializer.UniformBufferSize = UniformBufferSize;
	Initializer.DefaultBindingPoint = DefaultBindingPoint;
	Initializer.UniformVariableInfos.clear();
	Initializer.UniformVariableInfos.reserve(UniformBufferMemberList.size());
	for (const asset::shaderReflectionDataParser::UniformBufferMember& UBOMember : UniformBufferMemberList)
	{
		D_ASSERT_LOG(Initializer.UniformVariableInfos.find(UBOMember.mName) == Initializer.UniformVariableInfos.end(), "UBO member with same name is detected");
		Initializer.UniformVariableInfos.emplace(UBOMember.mName, UBOMember);
	}

	UniformBufferProxy->InitUniformBufferProxy(Initializer);

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy]()
		{
			RenderingProxyManager::GetSingleton()->AddedRenderingUniformBufferProxyList.push_back(Proxy);
		}
	);
}

void dooms::graphics::UniformBufferObject::GenerateUniformBufferObject(const void* const RawInitialData, const UINT64 SizeOfSourceData)
{
	D_ASSERT(UniformBufferProxy != nullptr);

	std::vector<UINT8> InitialData{};

	if((RawInitialData != nullptr) && (SizeOfSourceData != 0))
	{
		InitialData.resize(SizeOfSourceData);
		std::memcpy(InitialData.data(), RawInitialData, SizeOfSourceData);
	}

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = UniformBufferProxy, InitialData = std::move(InitialData)]()
		{
			Proxy->GenerateUniformBufferObject(InitialData.data());
		}
	);
}
