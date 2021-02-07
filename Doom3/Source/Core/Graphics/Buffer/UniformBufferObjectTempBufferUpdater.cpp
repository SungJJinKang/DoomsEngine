#include "UniformBufferObjectTempBufferUpdater.h"

#include <algorithm>
#include "../../Core.h"
#include "UniformBufferObjectManager.h"
#include "../../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"


doom::graphics::UniformBufferObjectTempBufferUpdater::UniformBufferObjectTempBufferUpdater()
{
	UniformBufferObjectTempBufferUpdater::mUniformBufferObjectTempBufferUpdaters.emplace_back(this);
}


doom::graphics::UniformBufferObjectTempBufferUpdater::~UniformBufferObjectTempBufferUpdater()
{
	//find this object iterator of mUniformBufferObjectTempBufferUpdaters
	auto this_iter = std::find_if(UniformBufferObjectTempBufferUpdater::mUniformBufferObjectTempBufferUpdaters.begin(), 
		UniformBufferObjectTempBufferUpdater::mUniformBufferObjectTempBufferUpdaters.end(), 
		[this](const std::unique_ptr<UniformBufferObjectTempBufferUpdater>& unique_ptr) {return unique_ptr.get() == this; });

	//remove this object from mUniformBufferObjectTempBufferUpdaters
	std::vector_swap_erase(UniformBufferObjectTempBufferUpdater::mUniformBufferObjectTempBufferUpdaters, this_iter);
}

void doom::graphics::UniformBufferObjectTempBufferUpdater::Init()
{

}

void doom::graphics::UniformBufferObjectTempBufferUpdater::Update()
{
	for (auto& updater : mUniformBufferObjectTempBufferUpdaters)
	{
		updater->UpdateUniformBufferObjectTempBuffer();
	}
}
