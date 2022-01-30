#include "PointLight.h"
#include "Transform.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Graphics/Buffer/UniformBufferObject/UniformBlockOffsetInfo.h"
#include "Graphics/Buffer/UniformBufferObject/UniformBufferObjectManager.h"

void dooms::PointLight::InitComponent()
{
	Light::InitComponent();
}

void dooms::PointLight::UpdateComponent()
{
	Light::UpdateComponent();
}

void dooms::PointLight::OnEndOfFrame_Component()
{
	Light::OnEndOfFrame_Component();

	UniformBufferCounter = 0;
}

void dooms::PointLight::OnActivated()
{
	AddToStaticContainer();
	Light::OnActivated();
}

void dooms::PointLight::OnDeActivated()
{
	RemoveFromStaticContainer();
	Light::OnDeActivated();
}

#pragma warning( disable : 4267 )

void dooms::PointLight::UpdateUniformBufferObject(const bool force)
{
	if (force || GetIsComponentEnabled() == true)
	{
		//if (bmIsLightUboDirty.GetIsDirty(true))
		//{//when transform value is changed
			auto transform = GetTransform();
			math::Vector3 pos = transform->GetPosition();
			math::Vector4 radiance = GetRadiance();

			const UINT32 staticIndex = UniformBufferCounter;
			UniformBufferCounter++;
			const UINT32 staticCount = GetStaticElementCount();
			if (staticIndex < MAX_POINT_LIGHT_COUNT)
			{
				dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_NAME)->UpdateDataToGPU((void*)pos.data(), sizeof(pos), graphics::eUniformBlock_Global::pointLight0_Pos + 32 * staticIndex);
				dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_NAME)->UpdateDataToGPU((void*)radiance.data(), sizeof(radiance), graphics::eUniformBlock_Global::pointLight0_Col + 32 * staticIndex);
				dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_NAME)->UpdateDataToGPU((void*)&staticCount, sizeof(staticCount), graphics::eUniformBlock_Global::pointLightCount); // TODO : DO this from every lights, just one call is enough per frame
			}
			else
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Point Light is supported until count : %d", MAX_POINT_LIGHT_COUNT);
			}

		//}
	}
}

void dooms::PointLight::OnDestroy()
{
	UniformBufferCounter = 0;
	RemoveFromStaticContainer();
	Light::OnDestroy();
}

dooms::PointLight::~PointLight()
{
}
