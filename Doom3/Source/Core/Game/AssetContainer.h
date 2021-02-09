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
		template<eAssetType loopVariable>
		struct ImportAssetFutureFunctor;

		template<eAssetType loopVariable>
		struct GetAssetFutureFunctor;

		template <eAssetType assetType>
		class AssetContainer
		{
			friend class AssetManager;

			template<eAssetType loopVariable>
			friend struct assetimporter::ImportAssetFutureFunctor;

			template<eAssetType loopVariable>
			friend struct assetimporter::GetAssetFutureFunctor;


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

			constexpr AssetContainer();

			void AddAsset(container_asset_type_t& asset);
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

		public:

			std::optional<std::reference_wrapper<container_asset_type_t>> GetAsset(const D_UUID& UUID);
			std::optional<std::reference_wrapper<const container_asset_type_t>> GetAsset_const(const D_UUID& UUID) const;
			std::optional<std::reference_wrapper<container_asset_type_t>> GetAsset(const unsigned int index);
			std::optional<std::reference_wrapper<const container_asset_type_t>> GetAsset_const(const unsigned int index) const;
			const std::vector<std::reference_wrapper<container_asset_type_t>>& GetAssets();
		};

		

	}
}