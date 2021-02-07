#include "UniformBufferObjectManager.h"

void doom::graphics::UniformBufferObjectManager::Init()
{

}

void doom::graphics::UniformBufferObjectManager::UpdateUniformBufferObjectTempBuffer()
{
	
}

void doom::graphics::UniformBufferObjectManager::Update()
{
	for (auto& uniformBufferObject : UniformBufferObjectManager::mUniformBufferObjects)
	{
		uniformBufferObject.BufferData();
	}
}

doom::graphics::UniformBufferObject& doom::graphics::UniformBufferObjectManager::GetOrAssignUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize)
{
	auto& uniformBufferObject = UniformBufferObjectManager::mUniformBufferObjects[bindingPoint];
	if (uniformBufferObject.IsBufferGenerated() == false)
	{//if uniformBufferObject is not initialized
		uniformBufferObject.GenUniformBufferObject(bindingPoint, uniformBlockSize);
	}
	return uniformBufferObject;
}

doom::graphics::UniformBufferObject& doom::graphics::UniformBufferObjectManager::GetUniformBufferObject(unsigned int bindingPoint)
{
	return UniformBufferObjectManager::mUniformBufferObjects[bindingPoint];
}

