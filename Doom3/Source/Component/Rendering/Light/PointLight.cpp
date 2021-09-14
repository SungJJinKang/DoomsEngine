#include "PointLight.h"
#include "Transform.h"
#include "Vector3.h"
#include "Vector4.h"

void doom::PointLight::InitComponent()
{

}

void doom::PointLight::UpdateComponent()
{

}

void doom::PointLight::OnEndOfFrame_Component()
{

}

#pragma warning( disable : 4267 )

void doom::PointLight::UpdateUniformBufferObject()
{
	if (bmIsLightUboDirty.GetIsDirty(true))
	{//when transform value is changed
		auto transform = GetTransform();
		math::Vector3 pos = transform->GetPosition();
		math::Vector4 radiance = GetRadiance();

		unsigned int staticIndex = GetStaticElementIndex();
		unsigned int staticCount = GetStaticElementCount();
		if (staticIndex < MAX_POINT_LIGHT_COUNT)
		{
			doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)pos.data(), sizeof(pos), graphics::eUniformBlock_Global::pointLight0_Pos + 32 * staticIndex);
			doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)radiance.data(), sizeof(radiance), graphics::eUniformBlock_Global::pointLight0_Col + 32 * staticIndex);
			doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)&staticCount, sizeof(staticCount), graphics::eUniformBlock_Global::dirLightCount); // TODO : DO this from every lights, just one call is enough per frame
		}
		else
		{
			D_DEBUG_LOG({ "Directional Light is supported until count : ", std::to_string(MAX_POINT_LIGHT_COUNT) }, eLogType::D_ERROR);
		}

	}
}
