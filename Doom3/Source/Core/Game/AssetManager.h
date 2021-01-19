#pragma once
#include <array>
#include <type_traits>
#include <map>
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
	private:
		using type = Doom::Asset::AssetTypeConditional_t< assetType>;
		static_assert(std::is_base_of_v<Doom::Asset, type>);
		std::map<D_UUID, type> Assets;

	public:

		constexpr AssetContainer() : Assets{}
		{

		}

		inline void AddAsset(type&& asset)
		{
			this->Assets.emplace(std::make_pair(asset.uuid, std::move(asset)));
		}

		

		std::optional<const type&> GetAsset(const D_UUID& uuid);
	};
	
	

	class AssetManager
	{
	private:
		static const std::filesystem::path AssetFolderPath;

		template <Asset::AssetType assetType, size_t ThreadSize>
		static void ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths);

		template <Asset::AssetType assetType>
		static AssetContainer<assetType> ImportedAssets;

	public:
		static void ImportEntireAsset();



	};
}


