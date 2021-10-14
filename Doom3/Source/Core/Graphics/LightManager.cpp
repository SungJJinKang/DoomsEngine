#include "LightManager.h"

#include "Buffer/UniformBlockOffsetInfo.h"
#include "Buffer/UniformBufferObjectManager.h"

void doom::graphics::LightManager::UpdateUniformBufferObject()
{
	if (bmIsAmbientLightIntensityDirty == true)
	{
		doom::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)&mAmbientLightIntensity, sizeof(FLOAT32), graphics::eUniformBlock_Global::ambientLightIntensity);
		bmIsAmbientLightIntensityDirty = false;
	}
}

FLOAT32 doom::graphics::LightManager::GetAmbientLightIntensity() const
{
	return mAmbientLightIntensity;
}

void doom::graphics::LightManager::SetAmbientLightIntensity(const FLOAT32 intensity)
{
	mAmbientLightIntensity = intensity;
	bmIsAmbientLightIntensityDirty = true;
}
