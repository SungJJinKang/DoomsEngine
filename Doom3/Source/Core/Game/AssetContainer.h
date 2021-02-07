#pragma once
#include <optional>
#include <type_traits>
#include <vector>
#include <future>

#include "../Asset/Asset.h"


namespace doom
{
	namespace assetimporter
	{
		template <Asset::eAssetType assetType>
		class AssetContainer
		{
			using container_asset_type_t = typename Asset::asset_type_t<assetType>;
			using container_imported_asset_future_t = typename std::future<std::optional<Asset::asset_type_t<assetType>>>;

			static_assert(std::is_base_of_v<Asset, container_asset_type_t>);

		private:

			/// <summary>
			///
			/// </summary>
			std::unordered_map<D_UUID, container_asset_type_t> mAssets;

			/// <summary>
			/// this is much faster than iterating unordered_map
			/// when insert to map and rehashing happen, reference of assetvalue isn't invalidated (safe)
			/// </summary>
			std::vector<std::reference_wrapper<container_asset_type_t>> mAssetsForIterating;

			/// <summary>
			/// store imported asset futue temporally
			/// </summary>
			std::vector<container_imported_asset_future_t> ImportedAssetFutures;
		public:

			constexpr AssetContainer();

			void AddAsset(container_asset_type_t& asset);


			/// <summary>
			/// push future of imported asset
			/// </summary>
			/// <param name="asset"></param>
			void AddAsset(container_imported_asset_future_t&& asset);

			/// <summary>
			/// push futures of imported asset
			/// </summary>
			/// <param name="asset"></param>
			void AddAsset(std::vector<container_imported_asset_future_t>&& assets);

			/// <summary>
			/// Get Stored Asset Futures and Move it's asset to Assets
			/// </summary>
			void GetAssetFutures();

			std::optional<std::reference_wrapper<container_asset_type_t>> GetAsset(const D_UUID& UUID);
			std::optional<std::reference_wrapper<const container_asset_type_t>> GetAsset_const(const D_UUID& UUID) const;

			const std::vector<std::reference_wrapper<container_asset_type_t>>& GetAssets();
		};

	}
}