#include "LightManager.h"

#include "Buffer/UniformBlockOffsetInfo.h"
#include "Buffer/UniformBufferObjectManager.h"

void doom::graphics::LightManager::UpdateUniformBufferObject()
{
	if (bmIsAmbientLightIntensityDirty == true)
	{
		doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)&mAmbientLightIntensity, sizeof(float), graphics::eUniformBlock_Global::ambientLightIntensity);
		bmIsAmbientLightIntensityDirty = false;
	}
}

float doom::graphics::LightManager::GetAmbientLightIntensity() const
{
	return mAmbientLightIntensity;
}

void doom::graphics::LightManager::SetAmbientLightIntensity(const float intensity)
{
	mAmbientLightIntensity = intensity;
	bmIsAmbientLightIntensityDirty = true;
}
