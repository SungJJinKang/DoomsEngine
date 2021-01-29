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

		/*
		template<Asset::eAssetType loopVariable>
		struct OnEndImportInSubThreadFunctor
		{
			constexpr inline void operator()()
			{
				for (auto& asset : AssetManager::ImportedAssets<loopVariable>.GetAssetsForIterating())
				{
					asset.OnEndImportInSubThread();
				}
			}
		};
		*/

		/// <summary>
		/// 
		/// </summary>
		template<Asset::eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor
		{
			constexpr inline void operator()()
			{
				for (auto& asset : AssetManager::ImportedAssets<loopVariable>.GetAssets())
				{
					asset.get().OnEndImportInMainThread();
				}
			}
		};

	private:
		static const std::filesystem::path AssetFolderPath;

		//template <Asset::AssetType assetType>
		//static constexpr void ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths);

		

	public:
		static void ImportEntireAsset();

		template <Asset::eAssetType assetType>
		static inline AssetContainer<assetType> ImportedAssets{};

		
	};

}




