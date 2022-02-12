#include "AssetIOWorker.h"

void dooms::AssetIOWorker::LoadRequiredDLLs()
{
	if (bmIsRequiredDllIsLoaded == false)
	{
		const std::vector<std::string> requiredDLLPathList = GetRequiredDLLPathList();
		for (const std::string& requiredDLLPath : requiredDLLPathList)
		{
			mDynamicLinkedDLLs.emplace_back(requiredDLLPath);
		}

		bmIsRequiredDllIsLoaded = true;
	}
}


dooms::AssetIOWorker::AssetIOWorker()
	: mDynamicLinkedDLLs(), bmIsRequiredDllIsLoaded(false)
{
	AddToRootObjectList();

	LoadRequiredDLLs();
}

std::vector<std::string> dooms::AssetIOWorker::GetRequiredDLLPathList()
{
	return {};
}
