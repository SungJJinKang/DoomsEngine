#include "LightManager.h"

#include "Buffer/UniformBlockOffsetInfo.h"
#include "Buffer/UniformBufferObjectManager.h"

void dooms::graphics::LightManager::UpdateUniformBufferObject(const bool force)
{
	if (force || (bmIsAmbientLightIntensityDirty == true))
	{
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(LIGHT_DATA_CONSTANT_BUFFER_NAME)->StoreDataAtTempBuffer((void*)&mAmbientLightIntensity, sizeof(FLOAT32), graphics::eUniformBlock_Global::ambientLightIntensity);
		bmIsAmbientLightIntensityDirty = false;
	}
}

FLOAT32 dooms::graphics::LightManager::GetAmbientLightIntensity() const
{
	return mAmbientLightIntensity;
}

void dooms::graphics::LightManager::SetAmbientLightIntensity(const FLOAT32 intensity)
{
	mAmbientLightIntensity = intensity;
	bmIsAmbientLightIntensityDirty = true;
}
