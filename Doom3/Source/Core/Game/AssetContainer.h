#pragma once
#include <optional>
#include <type_traits>
#include <vector>

#include "../Asset/Asset.h"

#include "../IO/AssetImporter/AssetImporter.h"

namespace Doom
{
	template <Asset::AssetType assetType>
	class AssetContainer
	{
		using asset_type = Asset::asset_type_t<assetType>;
	private:

		static_assert(std::is_base_of_v<Asset, asset_type>);

		std::unordered_map<D_UUID, asset_type> Assets;

		std::vector<std::reference_wrapper<asset_type>> AssetsForIterating;

		std::vector<AssetImporter::imported_asset_future_t<assetType>> ImportedAssetFutures; // store imported asset futue temporally
	public:

		constexpr AssetContainer() : Assets{}, AssetsForIterating{}, ImportedAssetFutures{}
		{

		}

		void AddAsset(asset_type& asset)
		{
			auto pair = this->Assets.emplace(std::make_pair(asset.uuid, std::move(asset)));

			if (pair.second == true)
			{
				AssetsForIterating.push_back(pair.first->second);
			}
			else
			{
				DEBUG_LOG("UUID is already inserted", LogType::D_ERROR);
			}
		}


		/// <summary>
		/// push future of imported asset
		/// </summary>
		/// <param name="asset"></param>
		void AddAsset(AssetImporter::imported_asset_future_t<assetType>&& asset)
		{
			ImportedAssetFutures.push_back(std::move(asset));
		}

		/// <summary>
		/// push futures of imported asset
		/// </summary>
		/// <param name="asset"></param>
		void AddAsset(std::vector<AssetImporter::imported_asset_future_t<assetType>>&& assets)
		{
			ImportedAssetFutures.insert(ImportedAssetFutures.end(), std::make_move_iterator(assets.begin()), std::make_move_iterator(assets.end()));
		}

		/// <summary>
		/// Get Stored Asset Futures and Move it's asset to Assets
		/// </summary>
		void GetAssetFutures()
		{
			for (auto& future : this->ImportedAssetFutures)
			{
				auto asset = future.get();
				if (asset.has_value())
				{
					this->AddAsset(asset.value());
				}
			}
			this->ImportedAssetFutures.clear();
		}

		std::optional<asset_type&> GetAsset(const D_UUID& uuid);
		std::optional<const asset_type&> GetAsset_const(const D_UUID& uuid) const;

		const std::vector<asset_type&>& GetAssets();
	};

}