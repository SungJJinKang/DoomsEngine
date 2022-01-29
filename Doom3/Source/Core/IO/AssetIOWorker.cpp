#include "AssetIOWorker.h"

std::array<std::vector<dooms::AssetIOWorker::RequiredDynamicLibrary>, dooms::asset::ENUM_ASSETTYPE_COUNT> dooms::AssetIOWorker::mRequiredDynamicLibrary{};

bool dooms::AssetIOWorker::RequiredDynamicLibrary::LoadIfNotLoaded()
{
	D_ASSERT(mLibraryName.empty() == false);

	bool isLoaded = false;

	if (mLibraryName.empty() == false)
	{
		if(mSmartDynamicLinking.IsDynamicLibraryLoaded() == false)
		{
			isLoaded = mSmartDynamicLinking.LoadDynamicLinkingLibrary(mLibraryName);
			D_ASSERT(isLoaded == true);
		}
		else
		{
			isLoaded = true;
		}
	}

	return isLoaded;
}

void dooms::AssetIOWorker::RequiredDynamicLibrary::UnLoad()
{
	mSmartDynamicLinking.ReleaseDynamicLinkingLibrary();
}

bool dooms::AssetIOWorker::RequiredDynamicLibrary::IsLoaded() const
{
	return mSmartDynamicLinking.IsDynamicLibraryLoaded();
}

bool dooms::AssetIOWorker::LoadRequiredDynamicLibrariesIfNotLoaded(const dooms::asset::eAssetType targetAssetType)
{
	bool isLoaded = true;
	for(RequiredDynamicLibrary& library : mRequiredDynamicLibrary[static_cast<UINT32>(targetAssetType)])
	{
		isLoaded &= library.LoadIfNotLoaded();
	}

	return isLoaded;
}

void dooms::AssetIOWorker::UnLoadRequiredDynamicLibraries(const dooms::asset::eAssetType targetAssetType)
{
	for (RequiredDynamicLibrary& library : mRequiredDynamicLibrary[static_cast<UINT32>(targetAssetType)])
	{
		library.UnLoad();
	}
}

bool dooms::AssetIOWorker::IsAllRequiredDynamicLibrariesLoaded(const dooms::asset::eAssetType targetAssetType)
{
	bool isLoaded = true;
	for (RequiredDynamicLibrary& library : mRequiredDynamicLibrary[static_cast<UINT32>(targetAssetType)])
	{
		isLoaded &= library.IsLoaded();
		if(isLoaded == false)
		{
			break;
		}
	}

	return isLoaded;
}
