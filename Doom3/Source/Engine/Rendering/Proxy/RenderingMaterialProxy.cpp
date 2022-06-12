#include "RenderingMaterialProxy.h"

#include "Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h"
#include "Rendering/Material/FixedMaterial.h"

void dooms::graphics::RenderingMaterialProxy::BindMaterial()
{
	if (FixedMaterial::GetSingleton()->GetIsFixedMaterialExist() == false)
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

			D_ASSERT(IsValid(ShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]) && ShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER));
			if (IsValid(ShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]) && ShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER))
			{
				const graphics::BufferID& inputLayoutForD3D = ShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->GetInputLayoutForD3D();
				D_ASSERT(inputLayoutForD3D.IsValid());
				if (inputLayoutForD3D.IsValid())
				{
					if (BOUND_INPUT_LAYOUT_ID != inputLayoutForD3D.GetBufferID())
					{
						BOUND_INPUT_LAYOUT_ID = inputLayoutForD3D;
						GraphicsAPI::BindInputLayoutForD3D(inputLayoutForD3D);
					}
				}
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

		for (UINT32 i = 0; i < TargetTextures.size(); i++)
		{
			if (IsValid(TargetTextures[i]) == true)
			{
				TargetTextures[i]->BindTexture();
			}
		}

		for (const UniformBufferObjectView& uboView : mTargetUniformBufferObjectViews)
		{
			uboView.BindUniformBufferObject();
		}

	}
}

void dooms::graphics::RenderingMaterialProxy::UnBindMaterial()
{
	if (FixedMaterial::GetSingleton()->GetIsFixedMaterialExist() == false)
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

		for (UINT32 i = 0; i < TargetTextures.size(); i++)
		{
			if (IsValid(TargetTextures[i]) == true)
			{
				TargetTextures[i]->UnBindTexture();
			}
		}

		for (const UniformBufferObjectView& uboView : TargetUniformBufferObjectViews)
		{
			uboView.UnBindUniformBufferObject();
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
	mMaterialStatus = eStatus::READY;
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

	mTargetUniformBufferObjectViews.clear();

	mMaterialStatus = eStatus::READY;
}

void dooms::graphics::RenderingMaterialProxy::DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType)
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (ProgramIDForOpenGL.IsValid() && IsValid(mShaderAsset[shaderType]) && mShaderAsset[shaderType]->GetShaderObject(shaderType).IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial(mPipeLineShaderView[shaderType], ProgramIDForOpenGL, mShaderAsset[shaderType]->GetShaderObject(shaderType));
			mPipeLineShaderView[shaderType].Reset();
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		if (mPipeLineShaderView[shaderType].IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial
			(
				mPipeLineShaderView[shaderType],
				ProgramIDForOpenGL,
				(IsValid(mShaderAsset[shaderType]) == true) ? static_cast<UINT64>(mShaderAsset[shaderType]->GetShaderObject(shaderType)) : static_cast<UINT64>(0)
			);
			mPipeLineShaderView[shaderType].Reset();
		}
	}
}
