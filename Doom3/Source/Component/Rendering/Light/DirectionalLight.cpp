#include "DirectionalLight.h"
#include "Transform.h"
#include "Vector3.h"
#include "Graphics/Buffer/UniformBlockOffsetInfo.h"
#include "Graphics/Buffer/UniformBufferObjectManager.h"

void doom::DirectionalLight::InitComponent()
{
	Light::InitComponent();
}

void doom::DirectionalLight::UpdateComponent()
{
	Light::UpdateComponent();
}

void doom::DirectionalLight::OnEndOfFrame_Component()
{
	Light::OnEndOfFrame_Component();
}

#pragma warning( disable : 4267 )

void doom::DirectionalLight::UpdateUniformBufferObject()
{
	if (bmIsLightUboDirty.GetIsDirty(true))
	{//when transform value is changed
		auto transform = GetTransform();
		math::Vector3 dir = transform->forward();
		math::Vector4 radiance = GetRadiance();

		UINT32 staticIndex = GetStaticElementIndex();
		UINT32 staticCount = GetStaticElementCount();
		if (staticIndex < MAX_DIRECTIONAL_LIGHT_COUNT)
		{
			doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)dir.data(), sizeof(dir), graphics::eUniformBlock_Global::dirLight0_Dir + 32 * staticIndex);
			doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)radiance.data(), sizeof(radiance), graphics::eUniformBlock_Global::dirLight0_Col + 32 * staticIndex);
			doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)&staticCount, sizeof(staticCount), graphics::eUniformBlock_Global::dirLightCount);
		}
		else
		{
			D_DEBUG_LOG({ "Directional Light is supported until count : ", std::to_string(MAX_DIRECTIONAL_LIGHT_COUNT) }, eLogType::D_ERROR);
		}
	
	}
}
