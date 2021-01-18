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
	struct AssetTypeConditional;
	template <AssetType assetType>
	using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

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

		~ApiImporter()
		{
			if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
			{
				assetImporter->ReleaseMultithreadApiImporter(importer);
			}

		}
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
		AssetImporter(size_t threadPoolSize) : threadPool{ threadPoolSize }, ApiImporters{}, apiImporterMutex{}, ImporterQueue{}
		{
			ApiImporters = new ApiImporterType[threadPoolSize];
			for (size_t i = 0; i < threadPool.PoolSize; i++)
			{
				this->InitApiImporter(ApiImporters[i]);
				
				ImporterQueue.push(&ApiImporters[i]);
			}
			
		}

		/// <summary>
		/// if workers is doing Task, Instance Destruction is postponed until Worker finish its task.
		/// And unfinished tasks is abandoned(not executed)
		/// </summary>
		~AssetImporter()
		{
			this->threadPool.TerminateThreadPool();
		}

	private:
		

		ApiImporter<assetType> GetMultithreadApiImporter()
		{
			if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
			{
				auto lck = std::scoped_lock(apiImporterMutex);

				ApiImporterType* importer{};
				if (this->ImporterQueue.empty())
				{
					DEBUG_LOG("Create New ApiImporter");
					importer = new ApiImporterTypeConditional_t<assetType>();
				}
				else
				{
					importer = this->ImporterQueue.front();
					ImporterQueue.pop();
				}

				return { this, importer };
			}
			else
			{
				return {this, &dummyApiImporter};
			}
		}

		void ReleaseMultithreadApiImporter(ApiImporterType* apiImporterType)
		{
			if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
			{
				auto lck = std::scoped_lock(apiImporterMutex);
				this->ImporterQueue.push(apiImporterType);
			}
			else
			{
				return;
			}
		}

		
		


		
	public:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		std::optional<AssetTypeConditional_t<assetType>> ImportAsset(const std::filesystem::path& path)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						return AssetImporter<assetType>::ReadAssetFile(path, this);
					}
				}
				catch (std::out_of_range& e)
				{
					DEBUG_LOG({ "Can't Find proper extension : ", extension });
				}
				catch (...)
				{
					DEBUG_LOG("Can't import asset");
				}
			}

			return {};
		}

		
		/// <summary>
		/// If you wanna check if future is ready without block
		/// use this future.wait_for(std::chrono::seconds(0)). if future isn't ready, current thread just pass wait
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		std::optional<std::future<std::optional<AssetTypeConditional_t<assetType>>>> ImportAssetAsync(const std::filesystem::path& path)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						std::function<std::optional<AssetTypeConditional_t<assetType>>()> newTask = std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this);
						return this->threadPool.AddTask(std::move(newTask));
					}
				}
				catch (std::out_of_range& e)
				{
					DEBUG_LOG({ "Can't Find proper extension : ", extension });
				}
				catch (...)
				{
					DEBUG_LOG("Can't import asset");
				}
			}
			
			return {};
		}

		
	

		/// <summary>
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>S
		/// <returns></returns>
		std::vector<std::optional<AssetTypeConditional_t<assetType>>> ImportAsset(const std::vector<std::filesystem::path>& paths)
		{

			std::vector<std::optional<AssetTypeConditional_t<assetType>>> Assets{};

			for (auto& path : paths)
			{
				if (path.has_extension())
				{
					auto extension = path.extension().string();
					try
					{
						if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
						{
							Assets.push_back(AssetImporter<assetType>::ReadAssetFile(path, this));
							continue;
						}
					}
					catch (std::out_of_range& e)
					{
						DEBUG_LOG({ "Can't Find proper extension : ", extension });
					}
					catch (...)
					{
						DEBUG_LOG({ "Undefined Error : ", extension });
					}
				}
				else
				{
					DEBUG_LOG({ path.string(), " : Doesn't have file extension" });
				}
				DEBUG_LOG({ "Fail To ImportAsset", path.string() });
				Assets.push_back({});

			}

			
			return Assets;
		}

		/// <summary>
		/// Import Assets on multithread
		/// Main Thread wait until Every Importing Works is done
		/// Should Call This Function when you need So many Assets at time like Scene Loading
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		std::vector<std::future<std::optional<AssetTypeConditional_t<assetType>>>> ImportAssetAsync(const std::vector<std::filesystem::path>& paths)
		{

			std::vector<std::function<std::optional<AssetTypeConditional_t<assetType>>()>> Tasks{};

			for (auto& path : paths)
			{
				if (path.has_extension())
				{
					auto extension = path.extension().string();
					try
					{
						if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
						{
							Tasks.push_back(std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this));
							continue;
						}
					}
					catch (std::out_of_range& e)
					{
						DEBUG_LOG({ "Can't Find proper extension : ", extension });
					}
					catch (...)
					{
						DEBUG_LOG({ "Undefined Error : ", extension });
					}
				}
				else
				{
					DEBUG_LOG({ path.string(), " : Doesn't have file extension"});
				}
				DEBUG_LOG({"Fail To ImportAsset", path.string()});
				Tasks.push_back(std::bind(&AssetImporter<assetType>::Dummy, this));
				
			}
			
			/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
			return this->threadPool.AddTaskChunk(Tasks);
		}
		
	};

	
	
}


