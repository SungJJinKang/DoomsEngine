#pragma once
#include <array>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <optional>
#include <filesystem>

#include "../Core.h"
#include "../Asset/Asset.h"
namespace Doom
{
	template <Doom::Asset::AssetType assetType>
	class AssetContainer
	{
	public:

		using asset_type = Doom::Asset::AssetTypeConditional_t< assetType>;
	private:
	
		static_assert(std::is_base_of_v<Doom::Asset, asset_type>);

		std::unordered_map<D_UUID, asset_type> Assets;

		/// <summary>
		/// if you want iterate assets, use this
		/// </summary>
		std::vector<typename std::unordered_map<D_UUID, asset_type>::iterator> AssetIterators;
	public:
		
		constexpr AssetContainer() : Assets{}, AssetIterators{}
		{
			D_UUID::
		}

		inline void AddAsset(asset_type&& asset)
		{
			AssetIterators.push_back(this->Assets.emplace(std::make_pair(asset.uuid, std::move(asset))).first);
		}

		
		std::optional<asset_type&> GetAsset(const D_UUID& uuid);
		std::optional<const asset_type&> GetAsset_const(const D_UUID& uuid) const;

		const std::vector<typename std::map<D_UUID, asset_type>::iterator>& GetAssets
	};



	

	class AssetManager
	{
	private:
		static const std::filesystem::path AssetFolderPath;

		template <Asset::AssetType assetType>
		static void ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths);

		template <Asset::AssetType assetType>
		static AssetContainer<assetType> ImportedAssets;

	public:
		static void ImportEntireAsset();


	};
}


