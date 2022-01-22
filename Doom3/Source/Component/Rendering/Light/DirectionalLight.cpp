#include "DirectionalLight.h"
#include "Transform.h"
#include "Vector3.h"
#include "Graphics/Buffer/UniformBlockOffsetInfo.h"
#include "Graphics/Buffer/UniformBufferObjectManager.h"

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
				dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->StoreDataAtTempBuffer((void*)dir.data(), sizeof(dir), graphics::eUniformBlock_Global::dirLight0_Dir + 32 * staticIndex);
				dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->StoreDataAtTempBuffer((void*)radiance.data(), sizeof(radiance), graphics::eUniformBlock_Global::dirLight0_Col + 32 * staticIndex);
				dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->StoreDataAtTempBuffer((void*)&staticCount, sizeof(staticCount), graphics::eUniformBlock_Global::dirLightCount);
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
