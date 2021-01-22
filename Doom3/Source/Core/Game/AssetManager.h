#pragma once
#include <array>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <optional>
#include <filesystem>
#include <vector>
#include <functional>
#include <future>

#include "../Core.h"
#include "../Asset/Asset.h"
namespace Doom
{
	/*
	
	/// <summary>
	/// This is for keeping future temporarily
	/// Because if trying getting future block mainthread, So trying getting future should be called after pass every import job to threadpool 
	/// </summary>
	template <Doom::Asset::AssetType assetType>
	class AssetFutureTempContainer
	{
	private:
		std::vector<std::future<std::optional<Asset::AssetTypeConditional_t<assetType>>>> futures;
	public:
		AssetFutureTempContainer(const std::vector<std::future<std::optional<Asset::AssetTypeConditional_t<assetType>>>>& tempFutures)
			: futures{std::move(tempFutures)}{}

		~AssetFutureTempContainer();
	};

	*/

	template <Doom::Asset::AssetType assetType>
	class AssetContainer
	{
	public:

		using asset_type = Doom::Asset::AssetTypeConditional_t< assetType>;
	private:
	
		static_assert(std::is_base_of_v<Doom::Asset, asset_type>);

		std::unordered_map<D_UUID, asset_type> Assets;

		std::vector<std::reference_wrapper<asset_type>> AssetsForIterating;
	public:
		
		constexpr AssetContainer() : Assets{}, AssetsForIterating{}
		{
			
		}

		inline void AddAsset(const asset_type&& asset)
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

		
		std::optional<asset_type&> GetAsset(const D_UUID& uuid);
		std::optional<const asset_type&> GetAsset_const(const D_UUID& uuid) const;

		const std::vector<asset_type&>& GetAssets();
	};

	class AssetManager
	{
		template<Asset::AssetType loopVariable> friend struct LoopJobFunctor;

	private:
		static const std::filesystem::path AssetFolderPath;

		template <Asset::AssetType assetType>
		static constexpr AssetFutureTempContainer<assetType> ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths);

		

	public:
		static void ImportEntireAsset();
		template <Asset::AssetType assetType>
		static AssetContainer<assetType> ImportedAssets;

	};

	template<Asset::AssetType loopVariable>
	struct LoopJobFunctor
	{
		constexpr void operator()(const std::array<std::vector<std::filesystem::path>, Doom::Asset::GetAssetTypeCount()>& AssetPaths)
		{
			AssetManager::ImportAssetAndAddToContainer<loopVariable>(AssetPaths[loopVariable]);
		}
	};

}



