#include "UniformBufferObjectTempBufferUpdater.h"

#include <algorithm>
#include "../../Core.h"
#include "UniformBufferObjectManager.h"


doom::graphics::UniformBufferObjectTempBufferUpdater::UniformBufferObjectTempBufferUpdater()
	: bmUpdateWhenManagerUpdate(true)
{
	UniformBufferObjectManager::GetSingleton()->PushUniformBufferObjectTempBufferUpdater(this);
}

doom::graphics::UniformBufferObjectTempBufferUpdater::UniformBufferObjectTempBufferUpdater(const bool _updateWhenManagerUpdate)
	: UniformBufferObjectTempBufferUpdater()
{
	bmUpdateWhenManagerUpdate = _updateWhenManagerUpdate;
}

doom::graphics::UniformBufferObjectTempBufferUpdater::~UniformBufferObjectTempBufferUpdater()
{
	UniformBufferObjectManager::GetSingleton()->EraseUniformBufferObjectTempBufferUpdater(this);
}
