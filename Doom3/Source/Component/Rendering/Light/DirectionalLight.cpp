#include "DirectionalLight.h"
#include "Transform.h"
#include "Vector3.h"
#include "Graphics/Buffer/UniformBufferObject/UniformBlockOffsetInfo.h"
#include "Graphics/Buffer/UniformBufferObject/UniformBufferObjectManager.h"

void dooms::DirectionalLight::InitComponent()
{
	Light::InitComponent();
	
}

void dooms::DirectionalLight::UpdateComponent()
{
	Light::UpdateComponent();
}

void dooms::DirectionalLight::OnEndOfFrame_Component()
{
	Light::OnEndOfFrame_Component();

	UniformBufferCounter = 0;
}

void dooms::DirectionalLight::OnActivated()
{
	AddToStaticContainer();
	Light::OnActivated();
}

void dooms::DirectionalLight::OnDeActivated()
{
	RemoveFromStaticContainer();
	Light::OnDeActivated();
}

#pragma warning( disable : 4267 )

void dooms::DirectionalLight::UpdateUniformBufferObject(const bool force)
{
	if(force || GetIsComponentEnabled() == true)
	{
		//if (bmIsLightUboDirty.GetIsDirty(true))
		//{//when transform value is changed
			auto transform = GetTransform();
			math::Vector3 dir = transform->forward();
			math::Vector4 radiance = GetRadiance();

			const UINT32 staticIndex = UniformBufferCounter;
			UniformBufferCounter++;
			const UINT32 staticCount = GetStaticElementCount();
			if (staticIndex < MAX_DIRECTIONAL_LIGHT_COUNT)
			{
				dooms::graphics::UniformBufferObject* const ubo = dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_NAME);
				D_ASSERT(IsValid(ubo));

				if (IsValid(ubo))
				{
					ubo->UpdateDataToGPU((void*)dir.data(), graphics::eUniformBlock_Global::dirLight0_Dir + 32 * staticIndex, sizeof(dir));
					ubo->UpdateDataToGPU((void*)radiance.data(), graphics::eUniformBlock_Global::dirLight0_Col + 32 * staticIndex, sizeof(radiance));
					ubo->UpdateDataToGPU((void*)&staticCount, graphics::eUniformBlock_Global::dirLightCount, sizeof(staticCount));
				}
			}
			else
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Directional Light is supported until count : %d", MAX_DIRECTIONAL_LIGHT_COUNT);
			}

		//}
	}

	
}

void dooms::DirectionalLight::OnDestroy()
{
	UniformBufferCounter = 0;
	RemoveFromStaticContainer();
	Light::OnDestroy();
	
	
}

dooms::DirectionalLight::~DirectionalLight()
{
}
