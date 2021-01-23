#pragma once
#include <filesystem>
#include <vector>
#include <array>

#include "../Core.h"
#include "../Asset/Asset.h"
#include "AssetContainer.h"
#include "../IO/AssetImporter/AssetImporter.h"



namespace Doom
{
	class AssetManager
	{

	private:
		static const std::filesystem::path AssetFolderPath;

		//template <Asset::AssetType assetType>
		//static constexpr void ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths);

		

	public:
		static void ImportEntireAsset();

		template <Asset::AssetType assetType>
		static inline AssetContainer<assetType> ImportedAssets{};

	private:
		template<Asset::AssetType loopVariable>
		struct ImportAssetFutureFunctor
		{
			constexpr inline void operator()(const std::array<std::vector<std::filesystem::path>, Doom::Asset::GetAssetTypeCount()>& AssetPaths)
			{
				//TODO : ApiImporters in AssetImporter instance is destoyed befroe import job completed
				
				AssetManager::ImportedAssets<loopVariable>.AddAsset(Doom::AssetImporter::Assetimporter::ImportAsset<loopVariable>(AssetPaths[loopVariable]));
			}
		};

		template<Asset::AssetType loopVariable>
		struct GetAssetFutureFunctor
		{
			constexpr inline void operator()()
			{
				AssetManager::ImportedAssets<loopVariable>.GetAssetFutures();
			}
		};
	};

}




