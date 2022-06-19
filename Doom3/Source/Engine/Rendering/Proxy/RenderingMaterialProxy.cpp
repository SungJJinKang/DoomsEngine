#include "RenderingMaterialProxy.h"

#include "Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h"
#include <Rendering/Proxy/RenderingFixedMaterialProxy.h>
#include <Rendering/Proxy/RenderingShaderProxy.h>
#include <Rendering/Proxy/RenderingTextureProxy.h>
#include <Rendering/Proxy/RenderingTextureViewProxy.h>

void dooms::graphics::RenderingMaterialProxy::InitRenderingMaterialProxyInitializer(FRenderingMaterialProxyInitializer& Initializer)
{
}

dooms::graphics::RenderingUniformBufferObjectViewProxy* dooms::graphics::RenderingMaterialProxy::GetRenderingUniformBufferObjectViewProxyFromUBOName(const char* const uniformBufferObjectName)
{
}

void dooms::graphics::RenderingMaterialProxy::BindMaterial()
{
	if (RenderingFixedMaterialProxy::IsExistFixedMaterialProxy() == false)
	{
		if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				if (PipeLineShaderView[pipeLineStageIndex].IsValid() == true)
				{
					if (BOUND_SHADER_ID[pipeLineStageIndex] != PipeLineShaderView[pipeLineStageIndex].GetBufferID())
					{
						BOUND_SHADER_ID[pipeLineStageIndex] = PipeLineShaderView[pipeLineStageIndex].GetBufferID();
						GraphicsAPI::BindShader(PipeLineShaderView[pipeLineStageIndex], (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
					}
				}
			}

			D_ASSERT
			(
				(AttachedShaderProxyList[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER] != nullptr) &&
				(AttachedShaderProxyList[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER))
			);

			const graphics::BufferID& InputLayoutForD3D = AttachedShaderProxyList[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->GetInputLayoutForD3D();
			D_ASSERT(InputLayoutForD3D.IsValid());
			if (BOUND_INPUT_LAYOUT_ID != InputLayoutForD3D.GetBufferID())
			{
				BOUND_INPUT_LAYOUT_ID = InputLayoutForD3D;
				GraphicsAPI::BindInputLayoutForD3D(InputLayoutForD3D);
			}
		}


		else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			D_ASSERT(ProgramIDForOpenGL.IsValid());
			if (ProgramIDForOpenGL.IsValid() == true)
			{
				if (BOUND_SHADER_ID[0] != ProgramIDForOpenGL.GetBufferID())
				{
					BOUND_SHADER_ID[0] = ProgramIDForOpenGL;
					GraphicsAPI::BindShader(ProgramIDForOpenGL, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
				}
			}
		}

		for (const RenderingTextureViewProxy* TextureView : TargetTextureViewProxyList)
		{
			TextureView->BindTexture();
		}

		for (const RenderingUniformBufferObjectViewProxy* UBOViewProxy : TargetRenderingUniformBufferObjectViewProxyList)
		{
			UBOViewProxy->BindUniformBufferObject();
		}

	}
}

void dooms::graphics::RenderingMaterialProxy::UnBindMaterial()
{
	if (RenderingFixedMaterialProxy::IsExistFixedMaterialProxy() == false)
	{

		if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				if (BOUND_SHADER_ID[pipeLineStageIndex] != 0)
				{
					BOUND_SHADER_ID[pipeLineStageIndex] = 0;
					GraphicsAPI::BindShader(0, (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
				}
			}

			if (BOUND_INPUT_LAYOUT_ID != 0)
			{
				BOUND_INPUT_LAYOUT_ID = 0;
				GraphicsAPI::BindInputLayoutForD3D(0);
			}
		}
		else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			if (BOUND_SHADER_ID[0] != 0)
			{
				BOUND_SHADER_ID[0] = 0;
				GraphicsAPI::BindShader(0, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
			}
		}

		for (const RenderingTextureViewProxy* TextureView : TargetTextureViewProxyList)
		{
			TextureView->UnBindTexture();
		}

		for (const RenderingUniformBufferObjectViewProxy* UBOViewProxy : TargetRenderingUniformBufferObjectViewProxyList)
		{
			UBOViewProxy->UnBindUniformBufferObject();
		}

	}
}

void dooms::graphics::RenderingMaterialProxy::CreateMaterialObjectIfNotExist()
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (ProgramIDForOpenGL.IsValid() == false)
		{
			ProgramIDForOpenGL = GraphicsAPI::CreateMaterial();
			D_ASSERT(ProgramIDForOpenGL.IsValid() == true);
		}
	}
	MaterialStatus = eStatus::READY;
}

void dooms::graphics::RenderingMaterialProxy::DestroyMaterialObjectIfExist()
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (ProgramIDForOpenGL.IsValid())
		{
			GraphicsAPI::DestroyMaterial(ProgramIDForOpenGL);
			ProgramIDForOpenGL.Reset();
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
		{
			DestroyShaderFromMaterial(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
		}


	}

	TargetRenderingUniformBufferObjectViewProxyList.clear();

	MaterialStatus = eStatus::READY;
}

void dooms::graphics::RenderingMaterialProxy::DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType)
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if
		(
			ProgramIDForOpenGL.IsValid() && 
			(AttachedShaderProxyList[ShaderType] != nullptr) && 
			AttachedShaderProxyList[ShaderType]->GetShaderObject(ShaderType).IsValid()
		)
		{
			GraphicsAPI::DetachShaderFromMaterial(PipeLineShaderView[ShaderType], ProgramIDForOpenGL, AttachedShaderProxyList[ShaderType]->GetShaderObject(ShaderType));
			PipeLineShaderView[ShaderType].Reset();
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		if (PipeLineShaderView[ShaderType].IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial
			(
				PipeLineShaderView[ShaderType],
				ProgramIDForOpenGL,
				(AttachedShaderProxyList[ShaderType] != nullptr) ? static_cast<UINT64>(AttachedShaderProxyList[ShaderType]->GetShaderObject(ShaderType)) : static_cast<UINT64>(0)
			);
			PipeLineShaderView[ShaderType].Reset();
		}
	}

	PoolMaterialHashValue();
}

void dooms::graphics::RenderingMaterialProxy::SetShaderProxy(dooms::graphics::RenderingShaderProxy* const ShaderProxy)
{
	for (size_t ShaderTypeIndex = 0; ShaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT; ShaderTypeIndex++)
	{
		if (ShaderProxy->IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(ShaderTypeIndex)))
		{
			SetShaderProxy(ShaderProxy, static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(ShaderTypeIndex));
		}
	}
}

void dooms::graphics::RenderingMaterialProxy::SetShaderProxy(dooms::graphics::RenderingShaderProxy* const ShaderProxy, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType)
{
	D_ASSERT(ShaderProxy->IsShaderObjectSuccessfullyCreated(ShaderType));

	AttachShaderProxyToMaterialProxy(ShaderProxy, ShaderType);
}

void dooms::graphics::RenderingMaterialProxy::SetShaderProxy
(
	const std::array<dooms::graphics::RenderingShaderProxy*, 
	GRAPHICS_PIPELINE_STAGE_COUNT>& ShaderProxyList
)
{
}

void dooms::graphics::RenderingMaterialProxy::AddTexture
(
	const UINT32 BindingPoint, 
	const RenderingTextureProxy* const TextureProxy,
	const graphics::GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage
)
{
	TargetTextureViewProxyList.push_back(TextureProxy->GenerateTextureView(BindingPoint, DefaultTargetGraphicsPipeLineStage));

	PoolMaterialHashValue();
}


dooms::eStatus dooms::graphics::RenderingMaterialProxy::GetMaterialStatus() const
{
	return MaterialStatus;
}

dooms::graphics::RenderingUniformBufferObjectViewProxy* dooms::graphics::RenderingMaterialProxy::GetUniformBufferObjectViewFromUBOName(const char* const UBOName) const
{
	RenderingUniformBufferObjectViewProxy* ReturnedUBOViewProxy = nullptr;

	D_DEBUG_LOG(eLogType::D_WARNING, "Calling Material::GetUniformBufferObjectView function with string ubo name is slow operator. Please use the function with index parameter");

	for (RenderingUniformBufferObjectViewProxy* UBOViewProxy : TargetRenderingUniformBufferObjectViewProxyList)
	{
		const RenderingUniformBufferProxy* const UBOProxy = UBOViewProxy->GetTargetUniformBufferProxy();
		if (UBOProxy->GetUniformBufferName() == UBOName)
		{
			ReturnedUBOViewProxy = UBOViewProxy;
			break;
		}
	}

	D_ASSERT(ReturnedUBOViewProxy != nullptr);

	return ReturnedUBOViewProxy;
}

const dooms::graphics::RenderingTextureViewProxy* dooms::graphics::RenderingMaterialProxy::GetTextureView(const size_t Index) const
{
	return TargetTextureViewProxyList[Index];
}

size_t dooms::graphics::RenderingMaterialProxy::GetTextureViewCount() const
{
	return TargetTextureViewProxyList.size();
}

UINT64 dooms::graphics::RenderingMaterialProxy::GetMaterialHashValue() const
{
	return MaterialHashValue;
}

bool dooms::graphics::RenderingMaterialProxy::Equal(const RenderingMaterialProxy* const lhs, const RenderingMaterialProxy* const rhs)
{
	D_ASSERT((lhs != nullptr) && (rhs != nullptr));
	return (lhs->GetMaterialHashValue() == rhs->GetMaterialHashValue());
}

void dooms::graphics::RenderingMaterialProxy::AttachShaderProxyToMaterialProxy(dooms::graphics::RenderingShaderProxy* const ShaderProxy, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType)
{
	D_ASSERT(ShaderProxy != nullptr);
	D_ASSERT(ShaderProxy->IsShaderObjectSuccessfullyCreated(ShaderType));
	D_ASSERT((ShaderType != dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY));
	
	CreateMaterialObjectIfNotExist();
	
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(ProgramIDForOpenGL.IsValid());

		DestroyShaderFromMaterial(ShaderType);

		const bool bIsSuccess = GraphicsAPI::AttachShaderToMaterial(PipeLineShaderView[ShaderType].GetBufferIDRef(), ProgramIDForOpenGL.GetBufferIDRef(), ShaderProxy->GetShaderObject(ShaderType), ShaderType);
		D_ASSERT(bIsSuccess == true);

		const bool isSuccessLinkMaterial = GraphicsAPI::LinkMaterial(ProgramIDForOpenGL);
		D_ASSERT(isSuccessLinkMaterial == true);
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		DestroyShaderFromMaterial(ShaderType);

		bool bIsSuccess = GraphicsAPI::AttachShaderToMaterial(PipeLineShaderView[ShaderType].GetBufferIDRef(), ProgramIDForOpenGL.GetBufferIDRef(), ShaderProxy->GetShaderObject(ShaderType), ShaderType);
		D_ASSERT(bIsSuccess == true);
	}

	const std::vector<RenderingUniformBufferProxy*>& ContainedUBOProxy = ShaderProxy->GetContainedRenderingUniformBufferProxyList();
	for (RenderingUniformBufferProxy* UBOProxy : ContainedUBOProxy)
	{
		AddRenderingUniformBufferObjectViewProxy(UBOProxy, ShaderType);
	}

	PoolMaterialHashValue();
}

dooms::graphics::RenderingUniformBufferObjectViewProxy* dooms::graphics::RenderingMaterialProxy::AddRenderingUniformBufferObjectViewProxy
(
	RenderingUniformBufferProxy* const UBOProxy,
	const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage
)
{
	RenderingUniformBufferObjectViewProxy* AddedUBOViewProxy = nullptr;

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		// In opengl, Uniform Buffer Object is bound one time regardless of target graphics pipe line stage
		for (RenderingUniformBufferObjectViewProxy* UBOViewProxy : TargetRenderingUniformBufferObjectViewProxyList)
		{
			if (UBOViewProxy->GetTargetUniformBufferProxy() == UBOProxy)
			{
				AddedUBOViewProxy = UBOViewProxy;
				break;
			}
		}

		
	}

	if
	(
		(AddedUBOViewProxy == nullptr) ||
		(graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	)
	{
		RenderingUniformBufferObjectViewProxy* const NewRenderingUniformBufferObjectViewProxy = new RenderingUniformBufferObjectViewProxy();

		RenderingUniformBufferObjectViewProxy::FRenderingUniformBufferObjectViewProxyInitializer Initializer;
		Initializer.TargetMaterialProxy = this;
		Initializer.TargetUniformBufferProxy = UBOProxy;
		Initializer.DefaultBindingPoint = UBOProxy->GetDefaultBindingPoint();
		Initializer.DefaultTargetPipeLineStage = TargetPipeLineStage;

		TargetRenderingUniformBufferObjectViewProxyList.push_back(NewRenderingUniformBufferObjectViewProxy);
		AddedUBOViewProxy = NewRenderingUniformBufferObjectViewProxy;
	}

	return AddedUBOViewProxy;
}

void dooms::graphics::RenderingMaterialProxy::PoolMaterialHashValue()
{
	UINT64 HashValue = 0;

	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (const BufferID& pipeLineShaderView : PipeLineShaderView)
		{
			if (pipeLineShaderView.IsValid())
			{
				HashValue ^= static_cast<UINT64>(pipeLineShaderView);
			}
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		HashValue = ProgramIDForOpenGL;
	}
	else
	{
		NEVER_HAPPEN;
	}

	for (const RenderingTextureViewProxy* TextureViewProxy : TargetTextureViewProxyList)
	{
		if (TextureViewProxy != nullptr)
		{
			HashValue ^= static_cast<UINT64>(TextureViewProxy->GetTextureBufferID());
		}
	}

	MaterialHashValue = HashValue;
}

