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

			const UINT64 staticIndex = UniformBufferCounter;
			UniformBufferCounter++;
			if (staticIndex < MAX_POINT_LIGHT_COUNT)
			{
				dooms::graphics::UniformBufferObject* const ubo = dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_NAME);
				D_ASSERT(IsValid(ubo));

				if (IsValid(ubo))
				{
					ubo->UpdateLocalBuffer((void*)pos.data(), graphics::eUniformBlock_Global::pointLight0_Pos + 4 * staticIndex, sizeof(pos));
					ubo->UpdateLocalBuffer((void*)radiance.data(), graphics::eUniformBlock_Global::pointLight0_Col + 4 * staticIndex, sizeof(radiance));
				}
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
