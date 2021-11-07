#include "UniformBufferObjectUpdater.h"

#include "../../Core.h"
#include "UniformBufferObjectManager.h"


dooms::graphics::UniformBufferObjectUpdater::UniformBufferObjectUpdater()
	: bmUpdateWhenManagerUpdate(true)
{
	UniformBufferObjectManager::GetSingleton()->PushUniformBufferObjectTempBufferUpdater(this);
}

dooms::graphics::UniformBufferObjectUpdater::UniformBufferObjectUpdater(const bool _updateWhenManagerUpdate)
	: UniformBufferObjectUpdater()
{
	bmUpdateWhenManagerUpdate = _updateWhenManagerUpdate;
}

dooms::graphics::UniformBufferObjectUpdater::~UniformBufferObjectUpdater()
{
	UniformBufferObjectManager::GetSingleton()->EraseUniformBufferObjectTempBufferUpdater(this);
}
