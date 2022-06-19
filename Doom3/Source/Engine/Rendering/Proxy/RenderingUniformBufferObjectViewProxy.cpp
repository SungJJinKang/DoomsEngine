#include "RenderingUniformBufferObjectViewProxy.h"

void dooms::graphics::RenderingUniformBufferObjectViewProxy::InitRenderingUniformBufferObjectViewProxy(FRenderingUniformBufferObjectViewProxyInitializer& Initializer)
{
	TargetMaterialProxy = Initializer.TargetMaterialProxy;
	TargetUniformBufferProxy = Initializer.TargetUniformBufferProxy;
	DefaultBindingPoint = Initializer.DefaultBindingPoint;
	DefaultTargetPipeLineStage = Initializer.DefaultTargetPipeLineStage;
}

void dooms::graphics::RenderingUniformBufferObjectViewProxy::BindUniformBufferObject() const noexcept
{
	D_ASSERT(TargetUniformBufferProxy != nullptr);
	
	TargetUniformBufferProxy->BindBuffer(DefaultBindingPoint, DefaultTargetPipeLineStage);
}

void dooms::graphics::RenderingUniformBufferObjectViewProxy::BindUniformBufferObject
(
	const UINT32 BindingPoint,
	const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage
) const noexcept
{
	D_ASSERT(TargetUniformBufferProxy != nullptr);
	
	TargetUniformBufferProxy->BindBuffer(BindingPoint, TargetPipeLineStage);
}

void dooms::graphics::RenderingUniformBufferObjectViewProxy::UnBindUniformBufferObject() const noexcept
{
	D_ASSERT(TargetUniformBufferProxy != nullptr);

	TargetUniformBufferProxy->UnBindBuffer(DefaultBindingPoint, DefaultTargetPipeLineStage);
}

dooms::graphics::RenderingMaterialProxy* dooms::graphics::RenderingUniformBufferObjectViewProxy::GetTargetMaterialProxy() const
{
	return TargetMaterialProxy;
}

