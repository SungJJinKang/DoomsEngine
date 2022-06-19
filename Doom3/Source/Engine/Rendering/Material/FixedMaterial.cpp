#include "FixedMaterial.h"

#include "Material.h"
#include <Rendering/Proxy/RenderingFixedMaterialProxy.h>
#include "ResourceManagement/Thread/RunnableThread/RenderThread.h"


void dooms::graphics::FixedMaterial::SetFixedMaterial(Material* const InFixedMaterial)
{
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[MaterialProxy = InFixedMaterial->GetRenderingMaterialProxy()]()
		{
			RenderingFixedMaterialProxy::SetFixedMaterial(MaterialProxy);
		}
	);
}

void dooms::graphics::FixedMaterial::ClearFixedMaterial()
{
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[]()
		{
			RenderingFixedMaterialProxy::ClearFixedMaterialProxy();
		}
	);
}
