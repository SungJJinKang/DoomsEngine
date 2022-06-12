#pragma once

#include <Core.h>

#include <vector>

#include <Simple_SingleTon/Singleton.h>

namespace dooms
{
	namespace graphics
	{
		class RenderingPrimitiveProxy;
		class RenderingLightProxy;
		class RenderingMaterialProxy;
		class RenderingShaderProxy;
		class RenderingUniformBufferProxy;
		class RenderingTextureProxy;

		class RenderingProxyManager : public DObject, public ISingleton<RenderingProxyManager>
		{

		public:

			std::vector<RenderingPrimitiveProxy*> RenderingPrimitiveProxyList{};
			std::vector<RenderingLightProxy*> RenderingLightProxyList{};
			std::vector<RenderingMaterialProxy*> RenderingMaterialProxyList{};
			std::vector<RenderingShaderProxy*> RenderingShaderProxyList{};
			std::vector<RenderingUniformBufferProxy*> RenderingUniformBufferProxyList{};
			std::vector<RenderingTextureProxy*> RenderingTextureProxyList{};

			std::vector<RenderingPrimitiveProxy*> DestroyedRenderingPrimitiveProxyList{};
			std::vector<RenderingLightProxy*> DestroyedRenderingLightProxyList{};
			std::vector<RenderingMaterialProxy*> DestroyedRenderingMaterialProxyList{};
			std::vector<RenderingShaderProxy*> DestroyedRenderingShaderProxyList{};
			std::vector<RenderingUniformBufferProxy*> DestroyedRenderingUniformBufferProxyList{};
			std::vector<RenderingTextureProxy*> DestroyedRenderingTextureProxyList{};
		};
	}
}


