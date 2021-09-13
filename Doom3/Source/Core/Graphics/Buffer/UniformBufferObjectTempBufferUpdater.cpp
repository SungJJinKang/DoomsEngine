#include "UniformBufferObjectTempBufferUpdater.h"

#include <algorithm>
#include "../../Core.h"
#include "UniformBufferObjectManager.h"


doom::graphics::UniformBufferObjectTempBufferUpdater::UniformBufferObjectTempBufferUpdater()
{
	UniformBufferObjectManager::GetSingleton()->PushUniformBufferObjectTempBufferUpdater(this);
}


doom::graphics::UniformBufferObjectTempBufferUpdater::~UniformBufferObjectTempBufferUpdater()
{
	UniformBufferObjectManager::GetSingleton()->EraseUniformBufferObjectTempBufferUpdater(this);
}

void doom::graphics::UniformBufferObjectTempBufferUpdater::UpdateUniformBufferObjectTempBuffer()
{
	graphics::UniformBufferObjectManager* const uniformBufferObjectMgr = graphics::UniformBufferObjectManager::GetSingleton();
	if (uniformBufferObjectMgr != nullptr)
	{
		UpdateUniformBufferObjectTempBuffer(*uniformBufferObjectMgr);
	}
}
