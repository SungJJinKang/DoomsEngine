#pragma once
#include <type_traits>
#include <vector>
#include <future>

#include "../Asset/Asset.h"

//template class DOOM_DLL_EXPORTS std::unordered_map<D_UUID, ::dooms::asset::Asset>

#include "AssetContainer.reflection.h"
namespace dooms
{
	namespace asset
	{
		/// <summary>
		/// Store Imported or Scheduled to be imported Assets 
		/// Store AssetContainer
		/// </summary>
		class DOOM_API D_CLASS AssetContainer : public DObject
		{
			GENERATE_BODY()

		public:

			dooms::asset::eAssetType mAssetTypeOfContainer;

			//TODO : Tree���·� ���� path directory�� ���󰡸鼭 leaf node�� ������ std::ref�� ����

			/// <summary>
			///
			/// </summary>
			std::unordered_map<D_UUID, ::dooms::asset::Asset*> mAssets;

			/// <summary>
			/// this is much faster than iterating unordered_map
			/// when insert to map and rehashing happen, reference of assetvalue isn't invalidated (safe)
			/// </summary>
			D_PROPERTY() // for the GC
			std::vector<::dooms::asset::Asset*> mAssetsForIterating;

			/// <summary>
			/// this will be used when find Asset with assetName
			/// AssetName contain extension!!
			/// </summary>
			std::unordered_map<std::string, ::dooms::asset::Asset*> mAssetsForAssetName;
			
			
			explicit AssetContainer(const dooms::asset::eAssetType assetTypeOfContainer);
			~AssetContainer();

			virtual void OnSetPendingKill() override;

			void ClearAssets();
			void AddNewAsset(::dooms::asset::Asset* const newAsset);
		};

		

	}
}