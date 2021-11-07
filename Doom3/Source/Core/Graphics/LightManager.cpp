#include "LightManager.h"

#include "Buffer/UniformBlockOffsetInfo.h"
#include "Buffer/UniformBufferObjectManager.h"

void dooms::graphics::LightManager::UpdateUniformBufferObject()
{
	if (bmIsAmbientLightIntensityDirty == true)
	{
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer((void*)&mAmbientLightIntensity, sizeof(FLOAT32), graphics::eUniformBlock_Global::ambientLightIntensity);
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
