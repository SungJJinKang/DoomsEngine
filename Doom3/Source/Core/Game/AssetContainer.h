#pragma once
#include <optional>
#include <type_traits>
#include <vector>
#include <future>

#include "../Asset/Asset.h"


namespace doom
{
	template <Asset::eAssetType assetType>
	class AssetContainer
	{
		using this_asset_type_t = Asset::asset_type_t<assetType>;
		using this_imported_asset_future_t = typename std::future<std::optional<Asset::asset_type_t<assetType>>>;

	private:

		static_assert(std::is_base_of_v<Asset, this_asset_type_t>);

		std::unordered_map<D_UUID, this_asset_type_t> Assets;

		std::vector<std::reference_wrapper<this_asset_type_t>> AssetsForIterating;

		

		std::vector<this_imported_asset_future_t> ImportedAssetFutures; // store imported asset futue temporally
	public:

		constexpr AssetContainer() : Assets{}, AssetsForIterating{}, ImportedAssetFutures{}
		{

		}

		void AddAsset(this_asset_type_t& asset)
		{
			auto pair = this->Assets.emplace(std::make_pair(asset.uuid, std::move(asset)));

			if (pair.second == true)
			{
				AssetsForIterating.push_back(pair.first->second);
			}
			else
			{
				DEBUG_LOG("UUID is already inserted", log::LogType::D_ERROR);
			}
		}


		/// <summary>
		/// push future of imported asset
		/// </summary>
		/// <param name="asset"></param>
		void AddAsset(this_imported_asset_future_t&& asset)
		{
			ImportedAssetFutures.push_back(std::move(asset));
		}

		/// <summary>
		/// push futures of imported asset
		/// </summary>
		/// <param name="asset"></param>
		void AddAsset(std::vector<this_imported_asset_future_t>&& assets)
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

		std::optional<this_asset_type_t&> GetAsset(const D_UUID& uuid);
		std::optional<const this_asset_type_t&> GetAsset_const(const D_UUID& uuid) const;

		const std::vector<this_asset_type_t&>& GetAssets();
	};

}