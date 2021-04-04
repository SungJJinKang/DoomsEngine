#include "UniformBufferObjectManager.h"

#include "UniformBufferObjectTempBufferUpdater.h"
#include "../../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"

void doom::graphics::UniformBufferObjectManager::UpdateUniformBufferObjectTempBufferUpdaters()
{
	for (auto updater : this->mUniformBufferObjectTempBufferUpdaters)
	{
		updater->UpdateUniformBufferObjectTempBuffer(*this);
	}
}

void doom::graphics::UniformBufferObjectManager::PushUniformBufferObjectTempBufferUpdater(UniformBufferObjectTempBufferUpdater* update_ptr)
{
	this->mUniformBufferObjectTempBufferUpdaters.push_back(update_ptr);
}

void doom::graphics::UniformBufferObjectManager::EraseUniformBufferObjectTempBufferUpdater(UniformBufferObjectTempBufferUpdater* update_ptr)
{
	auto iter_end = this->mUniformBufferObjectTempBufferUpdaters.end();
	auto this_iter = std::find_if(this->mUniformBufferObjectTempBufferUpdaters.begin(),
		iter_end,
		[update_ptr](const UniformBufferObjectTempBufferUpdater* stored_update_ptr) {return stored_update_ptr == update_ptr; });

	D_ASSERT(this_iter != iter_end); // this_iter == iter_end mean mUniformBufferObjectTempBufferUpdaters doesn't contain update_ptr, this is undefined

	//remove this object from mUniformBufferObjectTempBufferUpdaters
	std::vector_swap_popback(this->mUniformBufferObjectTempBufferUpdaters, this_iter);
}

void doom::graphics::UniformBufferObjectManager::Init()
{

}

void doom::graphics::UniformBufferObjectManager::Update()
{
	this->UpdateUniformBufferObjectTempBufferUpdaters();
	this->BufferDateOfUniformBufferObjects();
}

void doom::graphics::UniformBufferObjectManager::OnEndOfFrame()
{
}

void doom::graphics::UniformBufferObjectManager::BufferDateOfUniformBufferObjects()
{
	for (auto& uniformBufferObject : UniformBufferObjectManager::mUniformBufferObjects)
	{
		uniformBufferObject.BufferData();
	}
}

doom::graphics::UniformBufferObject& doom::graphics::UniformBufferObjectManager::GetOrGenerateUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSizeInByte)
{
	auto& uniformBufferObject = UniformBufferObjectManager::mUniformBufferObjects[bindingPoint];
	if (uniformBufferObject.IsBufferGenerated() == false)
	{//if uniformBufferObject is not initialized
		uniformBufferObject.GenerateUniformBufferObject(bindingPoint, uniformBlockSizeInByte);
	}
	return uniformBufferObject;
}

doom::graphics::UniformBufferObject& doom::graphics::UniformBufferObjectManager::GetUniformBufferObject(unsigned int bindingPoint)
{
	return UniformBufferObjectManager::mUniformBufferObjects[bindingPoint];
}

void doom::graphics::UniformBufferObjectManager::StoreDataAtTempBufferOfBindingPoint(unsigned int bindingPoint, const void* sourceData, unsigned int sizeInByteOfSourceData, unsigned int offsetInUniformBlock)
{
	this->GetUniformBufferObject(bindingPoint).StoreDataAtTempBuffer(sourceData, sizeInByteOfSourceData, offsetInUniformBlock);
}

