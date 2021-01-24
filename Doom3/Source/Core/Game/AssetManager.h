#pragma once
#include <filesystem>
#include <vector>
#include <array>

#include "../Core.h"
#include "../Asset/Asset.h"
#include "AssetContainer.h"
#include "../IO/AssetImporter/AssetImporter.h"



namespace doom
{
	class AssetManager
	{

	private:
		static const std::filesystem::path AssetFolderPath;

		//template <Asset::AssetType assetType>
		//static constexpr void ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths);

		

	public:
		static void ImportEntireAsset();

		template <Asset::eAssetType assetType>
		static inline AssetContainer<assetType> ImportedAssets{};

	private:
		template<Asset::eAssetType loopVariable>
		struct ImportAssetFutureFunctor
		{
			constexpr inline void operator()(const std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()>& AssetPaths)
			{
				AssetManager::ImportedAssets<loopVariable>.AddAsset(doom::assetimporter::Assetimporter::ImportAsset<loopVariable>(AssetPaths[loopVariable]));
			}
		};

		template<Asset::eAssetType loopVariable>
		struct GetAssetFutureFunctor
		{
			constexpr inline void operator()()
			{
				AssetManager::ImportedAssets<loopVariable>.GetAssetFutures();
			}
		};
	};

}




