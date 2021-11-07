#include "UniformBufferObjectManager.h"

#include "UniformBufferObjectUpdater.h"
#include "../../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

void dooms::graphics::UniformBufferObjectManager::UpdateUniformBufferObjects()
{
	for (UniformBufferObjectUpdater* updater : mUniformBufferObjectTempBufferUpdaters)
	{
		if (updater->bmUpdateWhenManagerUpdate == true)
		{
			updater->UpdateUniformBufferObject();
		}
	}
}

void dooms::graphics::UniformBufferObjectManager::PushUniformBufferObjectTempBufferUpdater(UniformBufferObjectUpdater* update_ptr)
{
	mUniformBufferObjectTempBufferUpdaters.push_back(update_ptr);
}

void dooms::graphics::UniformBufferObjectManager::EraseUniformBufferObjectTempBufferUpdater(UniformBufferObjectUpdater* update_ptr)
{
	auto iter_end = mUniformBufferObjectTempBufferUpdaters.end();
	auto this_iter = std::find_if(mUniformBufferObjectTempBufferUpdaters.begin(),
		iter_end,
		[update_ptr](const UniformBufferObjectUpdater* stored_update_ptr) {return stored_update_ptr == update_ptr; });

	D_ASSERT(this_iter != iter_end); // this_iter == iter_end mean mUniformBufferObjectTempBufferUpdaters doesn't contain update_ptr, this is undefined

	//remove this object from mUniformBufferObjectTempBufferUpdaters
	std::vector_swap_popback(mUniformBufferObjectTempBufferUpdaters, this_iter);
}

void dooms::graphics::UniformBufferObjectManager::UpdateUniformObjects()
{
	UpdateUniformBufferObjects();
	BufferDateOfUniformBufferObjects();
}


void dooms::graphics::UniformBufferObjectManager::BufferDateOfUniformBufferObjects()
{
	for (dooms::graphics::UniformBufferObject& uniformBufferObject : UniformBufferObjectManager::mUniformBufferObjects)
	{
		if (uniformBufferObject.IsBufferGenerated())
		{
			uniformBufferObject.BufferData();
		}	
	}
}

dooms::graphics::UniformBufferObject& dooms::graphics::UniformBufferObjectManager::GetOrGenerateUniformBufferObject(UINT32 bindingPoint, UINT32 uniformBlockSizeInByte)
{
	auto& uniformBufferObject = UniformBufferObjectManager::mUniformBufferObjects[bindingPoint];
	if (uniformBufferObject.IsBufferGenerated() == false)
	{//if uniformBufferObject is not initialized
		uniformBufferObject.GenerateUniformBufferObject(bindingPoint, uniformBlockSizeInByte);
	}
	return uniformBufferObject;
}

dooms::graphics::UniformBufferObject& dooms::graphics::UniformBufferObjectManager::GetUniformBufferObject(UINT32 bindingPoint)
{
	return UniformBufferObjectManager::mUniformBufferObjects[bindingPoint];
}

dooms::graphics::UniformBufferObjectManager::UniformBufferObjectManager()
{

}

