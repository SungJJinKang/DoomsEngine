#include "Material.h"

#include <Asset/ShaderAsset.h>

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include <Rendering/Buffer/UniformBufferObject/UniformBufferObjectManager.h>
#include <Asset/TextureAsset.h>

#include <Rendering/Proxy/RenderingProxyManager.h>
#include <ResourceManagement/Thread/RunnableThread/RenderThread.h>
#include <Rendering/Proxy/RenderingMaterialProxy.h>

UINT64 dooms::graphics::Material::BOUND_SHADER_ID[GRAPHICS_PIPELINE_STAGE_COUNT]{ (UINT64)-1, (UINT64)-1, (UINT64)-1};
UINT64 dooms::graphics::Material::BOUND_INPUT_LAYOUT_ID{(UINT64)-1};

void dooms::graphics::Material::SetShaderAsset(dooms::asset::ShaderAsset* const ShaderAsset)
{
	D_ASSERT(IsValid(ShaderAsset));

	CreateRenderingMaterialProxyIfNotCreated();

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy, ShaderProxy = ShaderAsset->GetRenderingShaderProxy()]()
		{
			Proxy->SetShaderProxy(ShaderProxy);
		}
	);
}

void dooms::graphics::Material::SetShaderAsset(dooms::asset::ShaderAsset* const ShaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType)
{
	D_ASSERT(IsValid(ShaderAsset));

	CreateRenderingMaterialProxyIfNotCreated();

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy, ShaderProxy = ShaderAsset->GetRenderingShaderProxy(), ShaderType]()
		{
			Proxy->SetShaderProxy(ShaderProxy, ShaderType);
		}
	);
}

void dooms::graphics::Material::SetShaderAsset(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& ShaderAssets)
{
	CreateRenderingMaterialProxyIfNotCreated();

	std::array<dooms::graphics::RenderingShaderProxy*, GRAPHICS_PIPELINE_STAGE_COUNT> RenderShaderProxyList;
	for(INT32 i = 0 ; i < GRAPHICS_PIPELINE_STAGE_COUNT ; i++)
	{
		RenderShaderProxyList[i] = (ShaderAssets[i] != nullptr) ? (ShaderAssets[i]->GetRenderingShaderProxy()) : nullptr;
	}

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy, RenderShaderProxyList]()
		{
			Proxy->SetShaderProxy(RenderShaderProxyList);
		}
	);
}

void dooms::graphics::Material::AddTexture
(
	const UINT32 BindingPoint, 
	const dooms::asset::TextureAsset* const TextureAsset,
	const graphics::GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage
)
{
	D_ASSERT(IsValid(TextureAsset));
	D_ASSERT(TextureAsset->IsRenderingTextureProxyCreated());

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy, BindingPoint, TextureProxy = TextureAsset->GetRenderingTextureProxy(), DefaultTargetGraphicsPipeLineStage]()
		{
			Proxy->AddTexture(BindingPoint, TextureProxy, DefaultTargetGraphicsPipeLineStage);
		}
	);
}

dooms::graphics::Material::Material(dooms::asset::ShaderAsset* const ShaderAsset)
{
	D_ASSERT(IsValid(ShaderAsset));

	SetShaderAsset(ShaderAsset);
}

dooms::graphics::Material::Material(dooms::asset::ShaderAsset* const ShaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
{
	D_ASSERT(IsValid(ShaderAsset));

	SetShaderAsset(ShaderAsset, shaderType);
}

dooms::graphics::Material::Material(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& ShaderAssets)
{
	SetShaderAsset(ShaderAssets);
}

dooms::graphics::Material::~Material()
{
	DestroyRenderingMaterialProxy();
}

void dooms::graphics::Material::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyRenderingMaterialProxy();
}

void dooms::graphics::Material::CreateRenderingMaterialProxy()
{
	D_ASSERT(IsRenderingMaterialProxyCreated() == false);

	MaterialProxy = new graphics::RenderingMaterialProxy();

	graphics::RenderingMaterialProxy::FRenderingMaterialProxyInitializer Initializer;
	MaterialProxy->InitRenderingMaterialProxyInitializer(Initializer);

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy]()
		{
			dooms::graphics::RenderingProxyManager::GetSingleton()->AddedRenderingMaterialProxyList.push_back(Proxy);
		}
	);
}

void dooms::graphics::Material::CreateRenderingMaterialProxyIfNotCreated()
{
	if (IsRenderingMaterialProxyCreated() == false)
	{
		CreateRenderingMaterialProxy();
	}
}

void dooms::graphics::Material::DestroyRenderingMaterialProxy()
{
	if (IsRenderingMaterialProxyCreated())
	{
		graphics::RenderingMaterialProxy* const Proxy = MaterialProxy;
		MaterialProxy = nullptr;

		dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
		(
			[Proxy]()
			{
				dooms::graphics::RenderingProxyManager::GetSingleton()->DestroyedRenderingMaterialProxyList.push_back(Proxy);
			}
		);
	}
}

dooms::graphics::RenderingMaterialProxy* dooms::graphics::Material::GetRenderingMaterialProxy() const
{
	return MaterialProxy;
}

bool dooms::graphics::Material::IsRenderingMaterialProxyCreated() const
{
	return (MaterialProxy != nullptr);
}

void dooms::graphics::Material::BindMaterial() const
{
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy]()
		{
			Proxy->BindMaterial();
		}
	);
}

void dooms::graphics::Material::UnBindMaterial() const
{
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = MaterialProxy]()
		{
			Proxy->UnBindMaterial();
		}
	);
}
