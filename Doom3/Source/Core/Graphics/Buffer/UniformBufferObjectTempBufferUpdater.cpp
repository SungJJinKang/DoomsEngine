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
