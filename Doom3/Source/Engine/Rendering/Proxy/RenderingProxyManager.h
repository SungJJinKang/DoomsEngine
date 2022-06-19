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
		class RenderingMeshProxy;

		class DOOM_API D_CLASS RenderingProxyManager : public DObject, public ISingleton<RenderingProxyManager>
		{

		public:

			std::vector<RenderingPrimitiveProxy*> RenderingPrimitiveProxyList{};
			std::vector<RenderingLightProxy*> RenderingLightProxyList{};
			std::vector<RenderingMaterialProxy*> RenderingMaterialProxyList{};
			std::vector<RenderingShaderProxy*> RenderingShaderProxyList{};
			std::vector<RenderingUniformBufferProxy*> RenderingUniformBufferProxyList{};
			std::vector<RenderingTextureProxy*> RenderingTextureProxyList{};
			std::vector<RenderingMeshProxy*> RenderingMeshProxyList{};

			std::vector<RenderingPrimitiveProxy*> AddedRenderingPrimitiveProxyList{};
			std::vector<RenderingLightProxy*> AddedRenderingLightProxyList{};
			std::vector<RenderingMaterialProxy*> AddedRenderingMaterialProxyList{};
			std::vector<RenderingShaderProxy*> AddedRenderingShaderProxyList{};
			std::vector<RenderingUniformBufferProxy*> AddedRenderingUniformBufferProxyList{};
			std::vector<RenderingTextureProxy*> AddedRenderingTextureProxyList{};
			std::vector<RenderingMeshProxy*> AddedRenderingMeshProxyList{};

			std::vector<RenderingPrimitiveProxy*> DestroyedRenderingPrimitiveProxyList{};
			std::vector<RenderingLightProxy*> DestroyedRenderingLightProxyList{};
			std::vector<RenderingMaterialProxy*> DestroyedRenderingMaterialProxyList{};
			std::vector<RenderingShaderProxy*> DestroyedRenderingShaderProxyList{};
			std::vector<RenderingUniformBufferProxy*> DestroyedRenderingUniformBufferProxyList{};
			std::vector<RenderingTextureProxy*> DestroyedRenderingTextureProxyList{};
			std::vector<RenderingMeshProxy*> DestroyedRenderingMeshProxyList{};
		};
	}
}


