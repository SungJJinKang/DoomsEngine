#pragma once
#include <Core.h>

#include <unordered_map>
#include <string>
#include <filesystem>
#include <future>
#include <optional>

#include <Asset/eAssetType.h>


namespace dooms
{
	namespace asset
	{
		class Asset;
	}
	
	namespace assetImporter
	{

		/// <summary>
		/// Avaliable Asset Extensions of ::dooms::asset::eAssetType
		/// </summary>
		extern const std::unordered_map<std::string, ::dooms::asset::eAssetType> AssetExtension;
		/// <summary>
		/// This extensions will be included in build(release) version
		/// if there is no InBuildExtension of AssetType(::dooms::asset::eAssetType), Any extensions is allowed
		/// </summary>
		extern const std::unordered_map<::dooms::asset::eAssetType, std::string> AssetInBuildExtension;

		extern std::optional<::dooms::asset::eAssetType> GetAssetType(const std::filesystem::path& path);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path"></param>
		/// <param name="asset"></param>
		/// <returns>Is Success??</returns>
		extern bool ImportAssetJob(std::filesystem::path path, ::dooms::asset::Asset* const asset);


		/// <summary>
		/// Import A Asset Asyncly
		/// You Should check path extension using GetAssetType function
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		NO_DISCARD extern std::future<bool> PushImportingAssetJobToThreadPool(
			std::filesystem::path path, ::dooms::asset::Asset* const asset
		);


		/// <summary>
		/// Import A Asset Asyncly
		/// If you need import multiple assets, use this function
		/// You Should check path extension using GetAssetType function
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		NO_DISCARD extern std::vector<std::future<bool>> PushImportingAssetJobToThreadPool(
			const std::vector<std::filesystem::path>& paths, 
			const std::vector<::dooms::asset::Asset*>& assets
		);

		///////////////////

	
		;


	}
}
