#include "UniformBufferObjectManager.h"

#include "UniformBufferObjectUpdater.h"
#include "../../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

void dooms::graphics::UniformBufferObjectManager::UpdateUniformBufferObjects()
{
	for (UniformBufferObjectUpdater* updater : mUniformBufferObjectTempBufferUpdaters)
	{
		if (updater->GetIsUpdateWhenManagerUpdate() == true)
		{
			updater->UpdateUniformBufferObject();
		}
	}
}

void dooms::graphics::UniformBufferObjectManager::PushUniformBufferObjectTempBufferUpdater(UniformBufferObjectUpdater* update_ptr)
{
	mUniformBufferObjectTempBufferUpdaters.push_back(update_ptr);
}

void dooms::graphics::UniformBufferObjectManager::EraseUniformBufferObjectTempBufferUpdater(UniformBufferObjectUpdater* const update_ptr)
{
	auto iter_end = mUniformBufferObjectTempBufferUpdaters.end();
	auto this_iter = std::find_if(mUniformBufferObjectTempBufferUpdaters.begin(),
		iter_end,
		[update_ptr](const UniformBufferObjectUpdater* stored_update_ptr) {return stored_update_ptr == update_ptr; });

	if(this_iter != iter_end)
	{
		swap_popback::vector_swap_popback(mUniformBufferObjectTempBufferUpdaters, this_iter);
	}
}

void dooms::graphics::UniformBufferObjectManager::UpdateUniformObjects()
{
	UpdateUniformBufferObjects();
	BufferDateOfUniformBufferObjects();
}

dooms::graphics::UniformBufferObject* dooms::graphics::UniformBufferObjectManager::GetUniformBufferObject(const std::string& uniformBufferName)
{
	dooms::graphics::UniformBufferObject* uniformBufferObject = nullptr;

	auto uniformBufferObjectNode = mUniformBufferObjects.find(uniformBufferName);
	D_ASSERT(uniformBufferObjectNode != mUniformBufferObjects.end());
	if (uniformBufferObjectNode != mUniformBufferObjects.end())
	{
		uniformBufferObject = uniformBufferObjectNode->second;
	}

	D_ASSERT(IsValid(uniformBufferObject));

	return uniformBufferObject;
}


void dooms::graphics::UniformBufferObjectManager::BufferDateOfUniformBufferObjects()
{
	for (auto uniformBufferObjectNode : mUniformBufferObjects)
	{
		dooms::graphics::UniformBufferObject* uniformBufferObject = uniformBufferObjectNode.second;
		D_ASSERT(IsValid(uniformBufferObject));

		if (uniformBufferObject->IsBufferGenerated())
		{
			uniformBufferObject->UpdateLocalBufferToGPU();
		}	
	}
}

dooms::graphics::UniformBufferObject* dooms::graphics::UniformBufferObjectManager::GetOrGenerateUniformBufferObject
(
	const std::string& uniformBufferName,
	const UINT64 uniformBufferSize,
	const UINT32 bindingPoint,
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage,
	const void* const initialData
)
{
	dooms::graphics::UniformBufferObject* uniformBufferObject = nullptr;

	auto uniformBufferObjectNode = mUniformBufferObjects.find(uniformBufferName);
	if(uniformBufferObjectNode == mUniformBufferObjects.end())
	{
		uniformBufferObject = GenerateUniformBufferObject(uniformBufferName, uniformBufferSize, bindingPoint, targetPipeLineStage, initialData);
	}
	else
	{
		uniformBufferObject = uniformBufferObjectNode->second;
	}

	return uniformBufferObject;
}

dooms::graphics::UniformBufferObject* dooms::graphics::UniformBufferObjectManager::GenerateUniformBufferObject
(
	const std::string& uniformBufferName,
	const UINT64 uniformBufferSize,
	const UINT32 bindingPoint, 
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage,
	const void* const initialData
)
{
	D_ASSERT(mUniformBufferObjects.find(uniformBufferName) == mUniformBufferObjects.end());
	dooms::graphics::UniformBufferObject* const generatedUniformBufferObject = dooms::CreateDObject<dooms::graphics::UniformBufferObject>(uniformBufferName, uniformBufferSize, bindingPoint, targetPipeLineStage, initialData);
	D_ASSERT(IsValid(generatedUniformBufferObject));
	mUniformBufferObjects.emplace(uniformBufferName, generatedUniformBufferObject);

	return generatedUniformBufferObject;
}


dooms::graphics::UniformBufferObjectManager::UniformBufferObjectManager()
{

}

