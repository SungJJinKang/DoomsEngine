#include "DirectionalLight.h"
#include "Transform.h"
#include "Vector3.h"

void doom::DirectionalLight::InitComponent()
{

}

void doom::DirectionalLight::UpdateComponent()
{

}

void doom::DirectionalLight::OnEndOfFrame_Component()
{

}

#pragma warning( disable : 4267 )

void doom::DirectionalLight::UpdateUniformBufferObjectTempBuffer(graphics::UniformBufferObjectManager& uboManager)
{
	if (this->bmIsLightUboDirty.GetIsDirty(true))
	{//when transform value is changed
		auto transform = this->GetTransform();
		math::Vector3 dir = transform->forward();
		math::Vector4 radiance = this->GetRadiance();

		unsigned int staticIndex = this->GetComponentStaticIndex();
		unsigned int staticCount = this->GetComponentStaticCount();
		if (staticIndex < MAX_DIRECTIONAL_LIGHT_COUNT)
		{
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)dir.data(), sizeof(dir), graphics::eUniformBlock_Global::dirLight0_Dir + 32 * staticIndex);
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)radiance.data(), sizeof(radiance), graphics::eUniformBlock_Global::dirLight0_Col + 32 * staticIndex);
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)&staticCount, sizeof(staticCount), graphics::eUniformBlock_Global::dirLightCount);
		}
		else
		{
			D_DEBUG_LOG({ "Directional Light is supported until count : ", std::to_string(MAX_DIRECTIONAL_LIGHT_COUNT) }, eLogType::D_ERROR);
		}
	
	}
}
