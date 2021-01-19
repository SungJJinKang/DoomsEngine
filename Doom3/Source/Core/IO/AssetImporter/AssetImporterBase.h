#pragma once


#include <filesystem>
#include <type_traits>
#include <map>
#include <string>
#include <optional>
#include <utility>
#include <functional>
#include <queue>
#include <fstream>

#include <thread>
#include <mutex>
#include <future>

#include "../../Core.h"

#include "../../Asset/Asset.h"

#ifdef DEBUG_MODE
#define THREADPOOL_DEBUG
#endif
#include "../../../Helper/ThreadPool_Cpp/ThreadPool.h"



namespace Doom
{
	class DummyApiImporter
	{
	};
	extern const DummyApiImporter dummyApiImporter;
	extern const std::map<std::string, Doom::AssetType> AssetExtension;



	

	template <AssetType assetType>
	struct ApiImporterTypeConditional;
	template <AssetType assetType>
	using ApiImporterTypeConditional_t = typename ApiImporterTypeConditional<assetType>::type;

	template <AssetType assetType>
	class AssetImporter;

	/// <summary>
	/// RAII
	/// </summary>
	template <AssetType assetType>
	class ApiImporter
	{
	private:

		using ApiImporterType = typename ApiImporterTypeConditional_t<assetType>;

		AssetImporter<assetType>* assetImporter;
		ApiImporterType* importer;

	public:
		ApiImporter(AssetImporter<assetType>* assetImporter, ApiImporterType* importer)
			: assetImporter{ assetImporter }, importer{ importer }
		{
		}

		ApiImporterType* operator->() const {
			return importer;
		}

		~ApiImporter();
	};

	template <AssetType assetType>
	class AssetImporter
	{
		friend class ApiImporter<assetType>;
	private:

		std::optional<AssetTypeConditional_t<assetType>> ReadAssetFile(std::filesystem::path path, AssetImporter<assetType>* assetImporter)
		{
			static_assert(false, "Please put proper type");
			return {};
		}
		
		

	private:

		ThreadPool threadPool;

		using ApiImporterType = typename ApiImporterTypeConditional_t<assetType>;

		std::mutex apiImporterMutex;

		ApiImporterType* ApiImporters;

		void InitApiImporter(ApiImporterType& apiImporter) {}

		std::queue<ApiImporterType*> ImporterQueue;

		
		public:
		AssetImporter(size_t threadPoolSize);

		/// <summary>
		/// if workers is doing Task, Instance Destruction is postponed until Worker finish its task.
		/// And unfinished tasks is abandoned(not executed)
		/// </summary>
		~AssetImporter();

	private:
		
		ApiImporter<assetType> GetMultithreadApiImporter();
		void ReleaseMultithreadApiImporter(ApiImporterType* apiImporterType);

	public:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		std::optional<AssetTypeConditional_t<assetType>> ImportAsset(const std::filesystem::path& path);

		
		/// <summary>
		/// If you wanna check if future is ready without block
		/// use this future.wait_for(std::chrono::seconds(0)). if future isn't ready, current thread just pass wait
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		std::optional<std::future<std::optional<AssetTypeConditional_t<assetType>>>> ImportAssetAsync(const std::filesystem::path& path);
		
		/// <summary>
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>S
		/// <returns></returns>
		std::vector<std::optional<AssetTypeConditional_t<assetType>>> ImportAsset(const std::vector<std::filesystem::path>& paths);

		/// <summary>
		/// Import Assets on multithread
		/// Main Thread wait until Every Importing Works is done
		/// Should Call This Function when you need So many Assets at time like Scene Loading
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		std::vector<std::future<std::optional<AssetTypeConditional_t<assetType>>>> ImportAssetAsync(const std::vector<std::filesystem::path>& paths);
		
	};

	Doom::AssetType GetAssetType(const std::filesystem::path& path);
	
}


