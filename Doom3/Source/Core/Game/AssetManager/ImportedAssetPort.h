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
		template<::doom::asset::eAssetType loopVariable>
		struct ImportAssetFunctor;

	
		/// <summary>
		/// Store Imported or Scheduled to be imported Assets 
		/// Store AssetContainer
		/// </summary>
		template <::doom::asset::eAssetType assetType>
		class ImportedAssetPort
		{
			friend class AssetManager;

			template<::doom::asset::eAssetType loopVariable>
			friend struct ImportAssetFunctor;


			static_assert(std::is_base_of_v<::doom::asset::Asset, ::doom::asset::Asset::asset_type_t<assetType>>);

		private:

			//TODO : Tree형태로 에셋 path directory를 따라가면서 leaf node에 에셋을 std::ref로 저장

			/// <summary>
			///
			/// </summary>
			std::unordered_map<D_UUID, ::doom::asset::Asset::asset_type_t<assetType>> mAssets;

			/// <summary>
			/// this is much faster than iterating unordered_map
			/// when insert to map and rehashing happen, reference of assetvalue isn't invalidated (safe)
			/// </summary>
			std::vector<::doom::asset::Asset::asset_type_t<assetType>*> mAssetsForIterating;

			/// <summary>
			/// this will be used when find Asset with assetName
			/// AssetName contain extension!!
			/// </summary>
			std::unordered_map<std::string, ::doom::asset::Asset::asset_type_t<assetType>*> mAssetsForAssetName;

			std::vector<::doom::asset::Asset::asset_type_t<assetType>*> PostProcessWaitingAssets{};

			constexpr ImportedAssetPort();


			typename ::doom::asset::Asset::asset_type_t<assetType>* AddNewAsset(const std::filesystem::path& assetFileDirectory);
			//typename ::doom::asset::Asset::asset_type_t<assetType>* AddAsset(::doom::asset::Asset::asset_type_t<assetType>&& asset);

		


		};

		

	}
}