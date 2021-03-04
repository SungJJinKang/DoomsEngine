#pragma once
#include <optional>
#include <type_traits>
#include <vector>
#include <future>

#include "../Asset/Asset.h"
#include "AssetContainer.h"

namespace doom
{
	namespace assetimporter
	{
		template<eAssetType loopVariable>
		struct ImportAssetFutureFunctor;

		template<eAssetType loopVariable>
		struct GetAssetFutureFunctor;

		/// <summary>
		/// Store Imported or Scheduled to be imported Assets 
		/// Store AssetContainer
		/// </summary>
		template <eAssetType assetType>
		class ImportedAssetPort
		{
			friend class AssetManager;

			template<eAssetType loopVariable>
			friend struct assetimporter::ImportAssetFutureFunctor;

			template<eAssetType loopVariable>
			friend struct assetimporter::GetAssetFutureFunctor;

			using container_asset_type_t = typename AssetContainer<assetType>;

			using asset_type = typename Asset::asset_type_t<assetType>;

			static_assert(std::is_base_of_v<Asset, typename container_asset_type_t::asset_type>);

		private:

			//TODO : Tree형태로 에셋 path directory를 따라가면서 leaf node에 에셋을 std::ref로 저장

			/// <summary>
			///
			/// </summary>
			std::unordered_map<D_UUID, typename container_asset_type_t> mAssets;

			/// <summary>
			/// this is much faster than iterating unordered_map
			/// when insert to map and rehashing happen, reference of assetvalue isn't invalidated (safe)
			/// </summary>
			std::vector<std::reference_wrapper<typename container_asset_type_t>> mAssetsForIterating;

			/// <summary>
			/// this will be used when find Asset with assetName
			/// AssetName contain extension!!
			/// </summary>
			std::unordered_map<std::string, std::reference_wrapper<typename container_asset_type_t>> mAssetsForAssetName;

			/// <summary>
			/// store imported asset futue temporally
			/// </summary>
			std::vector<std::reference_wrapper<container_asset_type_t>> GetFutureWaitingAssets{};
			std::vector<asset_type*> PostProcessWaitingAssets{};

			constexpr ImportedAssetPort();

			typename container_asset_type_t::asset_type* AddAsset(asset_type&& asset);
			/// push future of imported asset
			/// </summary>
			/// <param name="asset"></param>
			typename container_asset_type_t& AddAssetFuture(doom::assetimporter::imported_asset_future_t<assetType>&& assetFuture, const std::filesystem::path& path);
			/// <summary>
			/// push futures of imported asset
			/// </summary>
			/// <param name="asset"></param>
			std::vector<std::reference_wrapper<typename container_asset_type_t>> AddAssetFutures(std::vector<doom::assetimporter::imported_asset_future_t<assetType>>&& assetFutures, const std::vector<std::filesystem::path>& paths);

			/// <summary>
			/// GetReference Stored Asset Futures and Move it's asset to Assets
			/// </summary>
			void GetAssetFutures();


		};

		

	}
}