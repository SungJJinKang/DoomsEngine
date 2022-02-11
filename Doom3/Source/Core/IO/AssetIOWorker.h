#pragma once

#include <Core.h>

#include <array>
#include <vector>
#include <string>

#include <Asset/eAssetType.h>
#include <Misc/DynamicLinkingHelper/SmartDynamicLinking.h>

#include "AssetIOWorker.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS AssetIOWorker : public DObject
	{
		GENERATE_BODY()
	private:

		struct RequiredDynamicLibrary
		{
			std::string mLibraryName;
			SmartDynamicLinking mSmartDynamicLinking;

			bool LoadIfNotLoaded();
			void UnLoad();
			bool IsLoaded() const;
		};

		static std::array<std::vector<RequiredDynamicLibrary>, asset::ENUM_ASSETTYPE_COUNT> mRequiredDynamicLibrary;

	public:

		static bool LoadRequiredDynamicLibrariesIfNotLoaded(const dooms::asset::eAssetType targetAssetType);
		static void UnLoadRequiredDynamicLibraries(const dooms::asset::eAssetType targetAssetType);
		static bool IsAllRequiredDynamicLibrariesLoaded(const dooms::asset::eAssetType targetAssetType);

	};
}
