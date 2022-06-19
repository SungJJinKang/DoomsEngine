#include "RenderingFixedMaterialProxy.h"

#include <Rendering/Proxy/RenderingMaterialProxy.h>

dooms::graphics::RenderingMaterialProxy* dooms::graphics::RenderingFixedMaterialProxy::FixedRenderingMaterialProxy = nullptr;

bool dooms::graphics::RenderingFixedMaterialProxy::IsExistFixedMaterialProxy()
{
	return (FixedRenderingMaterialProxy != nullptr);
}

const dooms::graphics::RenderingMaterialProxy* dooms::graphics::RenderingFixedMaterialProxy::GetFixedMaterialProxy()
{
	return FixedRenderingMaterialProxy;
}

void dooms::graphics::RenderingFixedMaterialProxy::SetFixedMaterial(RenderingMaterialProxy* const InFixedRenderingMaterialProxy)
{
	ClearFixedMaterialProxy();

	if (InFixedRenderingMaterialProxy != nullptr)
	{
		InFixedRenderingMaterialProxy->BindMaterial();
	}

	FixedRenderingMaterialProxy = InFixedRenderingMaterialProxy;
}

void dooms::graphics::RenderingFixedMaterialProxy::ClearFixedMaterialProxy()
{
	if (FixedRenderingMaterialProxy != nullptr)
	{
		FixedRenderingMaterialProxy->UnBindMaterial();
	}

	FixedRenderingMaterialProxy = nullptr;
}
