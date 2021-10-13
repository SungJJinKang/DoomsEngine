#pragma once
#include <type_traits>
#include <vector>
#include <future>

#include "../Asset/Asset.h"

//template class DOOM_DLL_EXPORTS std::unordered_map<D_UUID, ::doom::asset::Asset>

namespace doom
{
	namespace asset
	{
		/// <summary>
		/// Store Imported or Scheduled to be imported Assets 
		/// Store AssetContainer
		/// </summary>
		struct DOOM_API AssetContainer
		{
			doom::asset::eAssetType mAssetTypeOfContainer;

			//TODO : Tree형태로 에셋 path directory를 따라가면서 leaf node에 에셋을 std::ref로 저장

			/// <summary>
			///
			/// </summary>
			std::unordered_map<D_UUID, ::doom::asset::Asset*> mAssets;

			/// <summary>
			/// this is much faster than iterating unordered_map
			/// when insert to map and rehashing happen, reference of assetvalue isn't invalidated (safe)
			/// </summary>
			std::vector<::doom::asset::Asset*> mAssetsForIterating;

			/// <summary>
			/// this will be used when find Asset with assetName
			/// AssetName contain extension!!
			/// </summary>
			std::unordered_map<std::string, ::doom::asset::Asset*> mAssetsForAssetName;
			
			
			explicit AssetContainer(const doom::asset::eAssetType assetTypeOfContainer);
			~AssetContainer();

			void ClearAssets();
			void AddNewAsset(::doom::asset::Asset* const newAsset);
		};

		

	}
}