#include "EnginePluginManager.h"

#include "EnginePlugin.h"

bool dooms::plugin::EnginePluginManager::AddEnginePlugins(EnginePlugin* const enginePlugin)
{
	bool isSuccess = false;

	D_ASSERT(IsValid(enginePlugin));
	if(IsValid(enginePlugin))
	{
		D_ASSERT(mEnginePlugins.find(enginePlugin->GetTypeHashVlue()) == mEnginePlugins.end());
		if(mEnginePlugins.find(enginePlugin->GetTypeHashVlue()) == mEnginePlugins.end())
		{
			mEnginePlugins.emplace(enginePlugin->GetTypeHashVlue(), enginePlugin);
			isSuccess = true;
		}
	}

	return isSuccess;
}

bool dooms::plugin::EnginePluginManager::RemoveEnginePlugins(EnginePlugin* const enginePlugin)
{
	bool isSuccess = false;

	D_ASSERT(mEnginePlugins.find(enginePlugin->GetTypeHashVlue()) == mEnginePlugins.end());
	auto node = mEnginePlugins.find(enginePlugin->GetTypeHashVlue());
	if (node != mEnginePlugins.end())
	{
		mEnginePlugins.erase(node);
		isSuccess = true;
	}

	return isSuccess;
}
