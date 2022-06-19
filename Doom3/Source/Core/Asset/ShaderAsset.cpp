#include <sstream>

#include "ShaderAsset.h"

#include <algorithm>
#include <d3d11.h>

#include <Rendering/Material/Material.h>
#include "Utility/ShaderAsset/shaderAssetHelper.h"
#include <EngineGUI/PrintText.h>
#include "Utility/ShaderAsset/shaderConverter.h"
#include <Rendering/Buffer/UniformBufferObject/UniformBufferObjectManager.h>
#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>

#include "Rendering/Proxy/RenderingShaderProxy.h"
#include "Rendering/Proxy/RenderingProxyManager.h"
#include "Rendering/Proxy/RenderingUniformBufferProxy.h"
#include "ResourceManagement/Thread/RunnableThread/RenderThread.h"

dooms::asset::ShaderAsset::ShaderAsset()
	: ShaderTextDatas(), ShaderProxy{nullptr}
{
}

dooms::asset::ShaderAsset::ShaderAsset(ShaderAsset&& shader) noexcept = default;
dooms::asset::ShaderAsset& dooms::asset::ShaderAsset::operator=(ShaderAsset&& shader) noexcept = default;

dooms::asset::ShaderAsset::~ShaderAsset()
{
	if (IsRenderingShaderProxyCreated())
	{
		DestroyRenderingShaderProxy();
	}
	ClearShaderTextDatas();
}

void dooms::asset::ShaderAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();

	if (IsRenderingShaderProxyCreated())
	{
		DestroyRenderingShaderProxy();
	}
	ClearShaderTextDatas();
}

dooms::graphics::RenderingShaderProxy* dooms::asset::ShaderAsset::GetRenderingShaderProxy() const
{
	return ShaderProxy;
}

const std::vector<dooms::graphics::UniformBufferObject*>& dooms::asset::ShaderAsset::GetContainedUniformBufferObject() const
{
	return ContainedUniformBufferObjects;
}



void dooms::asset::ShaderAsset::ClearShaderTextDatas()
{
	for (FShaderTextData& ShaderTextData : ShaderTextDatas)
	{
		ShaderTextData.Clear();
	}
}

bool dooms::asset::ShaderAsset::SetShaderText(const std::array<FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT>& InShaderTextDatas)
{
	bool isSuccess = true;

	ClearShaderTextDatas();

	ShaderTextDatas = InShaderTextDatas;

	for(FShaderTextData& ShaderTextData : ShaderTextDatas)
	{
		if
		(
			(ShaderTextData.ShaderStringText.empty() == false) &&
			(ShaderTextData.ShaderTextGraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE)
		)
		{
			if (ShaderTextData.ShaderReflectionDataStringText.empty() == false)
			{
				ShaderTextData.LoadShaderReflectionDataFromTextIfNotLoaded();
			}

			D_ASSERT(ShaderTextData.ShaderReflectionData.TargetGraphicsAPIType == dooms::graphics::GraphicsAPIManager::GetCurrentAPIType());
		}
	}

	D_ASSERT_LOG
	(
		IsHasAnyValidShaderTextString() == true,
		"Shader Asset doesn't have any shader string ( File Path : %s )", GetAssetPathAsUTF8Str().c_str()
	);
	if (IsHasAnyValidShaderTextString() == false)
	{
		isSuccess = false;
		dooms::ui::PrintText("Shader Asset doesn't have any shader string ( File Path : %s )", GetAssetPathAsUTF8Str().c_str());
	}
	
	return isSuccess;
}

const std::string& dooms::asset::ShaderAsset::GetShaderStringText
(
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage
) const
{
	return ShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].ShaderStringText;
}

const std::string& dooms::asset::ShaderAsset::GetShaderReflectionDataStringText
(
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage
) const
{
	return ShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].ShaderReflectionDataStringText;
}

const dooms::asset::shaderReflectionDataParser::ShaderReflectionData& dooms::asset::ShaderAsset::GetShaderReflectionData
(
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage
) const
{
	D_ASSERT(ShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].ShaderReflectionData.mIsGenerated == true);
	return ShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].ShaderReflectionData;
}


void dooms::asset::ShaderAsset::CreateRenderingShaderProxy()
{
	D_ASSERT(IsRenderingShaderProxyCreated() == false);

	GenerateUniformBufferObjectFromShaderReflectionData();

	ShaderProxy = new graphics::RenderingShaderProxy();

	graphics::RenderingShaderProxy::FRenderingShaderProxyInitializer Initializer{};
	Initializer.ShaderTextDatas = ShaderTextDatas;

	for(graphics::UniformBufferObject* UBO : ContainedUniformBufferObjects)
	{
		graphics::RenderingUniformBufferProxy* const UniformBufferProxy = UBO->GetUniformBufferProxy();
		D_ASSERT(UniformBufferProxy != nullptr);

		Initializer.RenderingUniformBufferProxyList.push_back(UniformBufferProxy);
	}
	
	ShaderProxy->InitRenderingShaderProxy(Initializer);

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = ShaderProxy]()
		{
			dooms::graphics::RenderingProxyManager::GetSingleton()->RenderingShaderProxyList.push_back(Proxy);
		}
	);
}

void dooms::asset::ShaderAsset::CreateRenderingShaderProxyIfNotCreated()
{
	if (IsRenderingShaderProxyCreated() == false)
	{
		CreateRenderingShaderProxy();
	}
}

void dooms::asset::ShaderAsset::DestroyRenderingShaderProxy()
{
	D_ASSERT(ShaderProxy != nullptr);
	
	graphics::RenderingShaderProxy* const Proxy = ShaderProxy;
	ShaderProxy = nullptr;

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy]()
		{
			dooms::graphics::RenderingProxyManager::GetSingleton()->DestroyedRenderingShaderProxyList.push_back(Proxy);
		}
	);
}

void dooms::asset::ShaderAsset::GenerateUniformBufferObjectFromShaderReflectionData()
{
	D_ASSERT(ContainedUniformBufferObjects.size() == 0);

	for(FShaderTextData& ShaderTextData : ShaderTextDatas)
	{
		for (const shaderReflectionDataParser::UniformBuffer& UniformBufferReflectionData : ShaderTextData.ShaderReflectionData.mUniformBuffers)
		{
			const unsigned long long AlignedSize = UniformBufferReflectionData.mBlockSize + ((UniformBufferReflectionData.mBlockSize % 16) == 0 ? 0 : (16 - (UniformBufferReflectionData.mBlockSize % 16)));
			//D3D11 require constant buffer size to be multiple of 16

			dooms::graphics::UniformBufferObject* const UBO = dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetOrGenerateUniformBufferObjectIfNotExist
			(
				UniformBufferReflectionData.mName,
				AlignedSize,
				UniformBufferReflectionData.mBindingPoint,
				nullptr,
				&(UniformBufferReflectionData.mMembers)
			);
			D_ASSERT(IsValid(UBO));

			if (std::find(ContainedUniformBufferObjects.begin(), ContainedUniformBufferObjects.end(), UBO) == ContainedUniformBufferObjects.end())
			{
				ContainedUniformBufferObjects.push_back(UBO);
			}
		}
	}
}

void dooms::asset::ShaderAsset::OnEndImportInMainThread_Internal()
{
	CreateRenderingShaderProxy();
}


bool dooms::asset::ShaderAsset::IsHasAnyValidShaderTextString() const
{
	bool isHasAnyValidShaderTextString = false;
	for (const FShaderTextData& ShaderTextStr : ShaderTextDatas)
	{
		if (ShaderTextStr.IsCompileliable() == true)
		{
			isHasAnyValidShaderTextString = true;
			break;
		}
	}

	return isHasAnyValidShaderTextString;
}




dooms::graphics::Material* dooms::asset::ShaderAsset::CreateMatrialWithThisShaderAsset()
{
	D_ASSERT(IsRenderingShaderProxyCreated() == true);

	std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderAssets;
	for(size_t ShaderTypeIndex = 0 ; ShaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT ; ShaderTypeIndex++)
	{
		if(ShaderTextDatas[ShaderTypeIndex].IsCompileliable())
		{
			ShaderAssets[ShaderTypeIndex] = this;
		}
		else
		{
			ShaderAssets[ShaderTypeIndex] = nullptr;
		}
	}

	dooms::graphics::Material* const material = dooms::CreateDObject<dooms::graphics::Material>(ShaderAssets);
	D_ASSERT(IsValid(material) == true);

	return material;
}

bool dooms::asset::ShaderAsset::IsRenderingShaderProxyCreated() const
{
	return (ShaderProxy != nullptr);
}

dooms::asset::eAssetType dooms::asset::ShaderAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::SHADER;
}

dooms::graphics::eShaderCompileStatus dooms::asset::ShaderAsset::GetCurrentShaderCompileStatus
(
	const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType
) const
{
	return	ShaderProxy->GetCurrentShaderCompileStatus(shaderType);
}

