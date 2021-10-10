#include "UniformBufferObjectUpdater.h"

#include "../../Core.h"
#include "UniformBufferObjectManager.h"


doom::graphics::UniformBufferObjectUpdater::UniformBufferObjectUpdater()
	: bmUpdateWhenManagerUpdate(true)
{
	UniformBufferObjectManager::GetSingleton()->PushUniformBufferObjectTempBufferUpdater(this);
}

doom::graphics::UniformBufferObjectUpdater::UniformBufferObjectUpdater(const bool _updateWhenManagerUpdate)
	: UniformBufferObjectUpdater()
{
	bmUpdateWhenManagerUpdate = _updateWhenManagerUpdate;
}

doom::graphics::UniformBufferObjectUpdater::~UniformBufferObjectUpdater()
{
	UniformBufferObjectManager::GetSingleton()->EraseUniformBufferObjectTempBufferUpdater(this);
}
