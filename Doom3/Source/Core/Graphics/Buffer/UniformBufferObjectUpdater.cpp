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

dooms::graphics::UniformBufferObjectUpdater::UniformBufferObjectUpdater(const UniformBufferObjectUpdater& updater)
	: bmUpdateWhenManagerUpdate(updater.bmUpdateWhenManagerUpdate)
{
	UniformBufferObjectManager::GetSingleton()->PushUniformBufferObjectTempBufferUpdater(this);
}

dooms::graphics::UniformBufferObjectUpdater& dooms::graphics::UniformBufferObjectUpdater::operator=(const UniformBufferObjectUpdater& updater)
{
	bmUpdateWhenManagerUpdate = updater.bmUpdateWhenManagerUpdate;
	UniformBufferObjectManager::GetSingleton()->PushUniformBufferObjectTempBufferUpdater(this);
	return *this;
}

dooms::graphics::UniformBufferObjectUpdater::~UniformBufferObjectUpdater()
{
	RemoveFromUniformBufferObjectManager();
}

void dooms::graphics::UniformBufferObjectUpdater::RemoveFromUniformBufferObjectManager()
{
	if (UniformBufferObjectManager::GetSingleton() != nullptr)
	{
		UniformBufferObjectManager::GetSingleton()->EraseUniformBufferObjectTempBufferUpdater(this);
	}
}
