#include "LightManager.h"

#include "Buffer/UniformBufferObject/UniformBlockOffsetInfo.h"
#include "Buffer/UniformBufferObject/UniformBufferObjectManager.h"

void dooms::graphics::LightManager::UpdateUniformBufferObject(const bool force)
{
	if (force || (bmIsAmbientLightIntensityDirty == true))
	{
		D_ASSERT(dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(LIGHT_DATA_CONSTANT_BUFFER_NAME)->GetUniformVariableOffset("ambientLightIntensity") == graphics::eUniformBlock_Global::ambientLightIntensity);
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(LIGHT_DATA_CONSTANT_BUFFER_NAME)->UpdateDataToGPU((void*)&mAmbientLightIntensity, graphics::eUniformBlock_Global::ambientLightIntensity, sizeof(FLOAT32));
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
