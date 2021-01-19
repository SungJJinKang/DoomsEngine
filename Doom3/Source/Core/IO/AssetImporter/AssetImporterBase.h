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
	public:
		constexpr DummyApiImporter() {}
	};
	inline DummyApiImporter dummyApiImporter{};



	const inline std::map<std::string, Doom::Asset::AssetType> AssetExtension
	{
		//3D Model Asset Formats
		{"dae", Doom::Asset::AssetType::THREE_D_MODELL},
		{"blend", Doom::Asset::AssetType::THREE_D_MODELL},
		{"bvh", Doom::Asset::AssetType::THREE_D_MODELL},
		{"3ds", Doom::Asset::AssetType::THREE_D_MODELL},
		{"ase", Doom::Asset::AssetType::THREE_D_MODELL},
		{"obj", Doom::Asset::AssetType::THREE_D_MODELL},
		{"glFT", Doom::Asset::AssetType::THREE_D_MODELL},
		{"ply", Doom::Asset::AssetType::THREE_D_MODELL},
		{"dxf", Doom::Asset::AssetType::THREE_D_MODELL},
		{"ifc", Doom::Asset::AssetType::THREE_D_MODELL},
		{"nff", Doom::Asset::AssetType::THREE_D_MODELL},
		{"smd", Doom::Asset::AssetType::THREE_D_MODELL},
		{"vta", Doom::Asset::AssetType::THREE_D_MODELL},
		{"mdl", Doom::Asset::AssetType::THREE_D_MODELL},
		{"mdl2", Doom::Asset::AssetType::THREE_D_MODELL},
		{"mdl3", Doom::Asset::AssetType::THREE_D_MODELL},
		{"pk3", Doom::Asset::AssetType::THREE_D_MODELL},
		{"mdmdcl2", Doom::Asset::AssetType::THREE_D_MODELL},
		{"md5mesh", Doom::Asset::AssetType::THREE_D_MODELL},
		{"md5anim", Doom::Asset::AssetType::THREE_D_MODELL},
		{"md5camera ", Doom::Asset::AssetType::THREE_D_MODELL},
		{"q3o", Doom::Asset::AssetType::THREE_D_MODELL},
		{"q3s", Doom::Asset::AssetType::THREE_D_MODELL},
		{"raw", Doom::Asset::AssetType::THREE_D_MODELL},
		{"ac", Doom::Asset::AssetType::THREE_D_MODELL},
		{"stl", Doom::Asset::AssetType::THREE_D_MODELL},
		{"dxf", Doom::Asset::AssetType::THREE_D_MODELL},
		{"irrmesh", Doom::Asset::AssetType::THREE_D_MODELL},
		{"irr", Doom::Asset::AssetType::THREE_D_MODELL},
		{"off", Doom::Asset::AssetType::THREE_D_MODELL},
		{"dterxf", Doom::Asset::AssetType::THREE_D_MODELL},
		{"mdl", Doom::Asset::AssetType::THREE_D_MODELL},
		{"hmp", Doom::Asset::AssetType::THREE_D_MODELL},
		{"mesh", Doom::Asset::AssetType::THREE_D_MODELL},
		{"skeleton", Doom::Asset::AssetType::THREE_D_MODELL},
		{"material", Doom::Asset::AssetType::THREE_D_MODELL},
		{"ms3d", Doom::Asset::AssetType::THREE_D_MODELL},
		{"lwo", Doom::Asset::AssetType::THREE_D_MODELL},
		{"lws", Doom::Asset::AssetType::THREE_D_MODELL},
		{"lxo", Doom::Asset::AssetType::THREE_D_MODELL},
		{"csm", Doom::Asset::AssetType::THREE_D_MODELL},
		{"ply", Doom::Asset::AssetType::THREE_D_MODELL},
		{"cob", Doom::Asset::AssetType::THREE_D_MODELL},
		{"scn", Doom::Asset::AssetType::THREE_D_MODELL},

		//////////////////////////////////////////////////////////////////////////

		{"txt", Doom::Asset::AssetType::TEXT},
		{"glsl", Doom::Asset::AssetType::TEXT},
		{"ini", Doom::Asset::AssetType::TEXT},

	};



	

	template <Asset::AssetType assetType>
	struct ApiImporterTypeConditional
	{
		using type = typename DummyApiImporter;
	};

	template <Asset::AssetType assetType>
	using ApiImporterTypeConditional_t = typename ApiImporterTypeConditional<assetType>::type;





	template <Asset::AssetType assetType>
	class AssetImporter;

	/// <summary>
	/// RAII
	/// </summary>
	template <Asset::AssetType assetType>
	class ApiImporter
	{
	private:

		using ApiImporterType = typename ApiImporterTypeConditional_t<assetType>;

		AssetImporter<assetType>* assetImporter;
		ApiImporterType* importer;

	public:
		constexpr ApiImporter(AssetImporter<assetType>* assetImporter, ApiImporterType* importer)
			: assetImporter{ assetImporter }, importer{ importer }
		{
		}

		constexpr ApiImporterType* operator->() const {
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



	template <Asset::AssetType assetType>
	class AssetImporter
	{
		friend class ApiImporter<assetType>;
	private:

		std::optional<Asset::AssetTypeConditional_t<assetType>> ReadAssetFile(std::filesystem::path path, AssetImporter<assetType>* assetImporter)
		{
			static_assert(false, "Please put proper type");
			return {};
		}
		
		

	private:

		ThreadPool threadPool;

		using ApiImporterType = typename ApiImporterTypeConditional_t<assetType>;

		std::mutex apiImporterMutex;

		std::vector<ApiImporterType> ApiImporters;

		void InitApiImporter(ApiImporterType& apiImporter) {}

		std::queue<ApiImporterType*> ImporterQueue;

		
		public:
		constexpr AssetImporter(size_t threadPoolSize) : threadPool{ threadPoolSize }, ApiImporters{ threadPoolSize }, apiImporterMutex{}, ImporterQueue{}
		{
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
				return { this, &dummyApiImporter };
			}
		}

		constexpr void ReleaseMultithreadApiImporter(ApiImporterType* apiImporterType)
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
		const std::optional<Asset::AssetTypeConditional_t<assetType>> ImportAsset(const std::filesystem::path& path)
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
				catch (...)
				{
					DEBUG_LOG({ "Can't Find proper extension : ", extension });
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
		const std::optional<std::future<std::optional<Asset::AssetTypeConditional_t<assetType>>>> ImportAssetAsync(const std::filesystem::path& path)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						std::function<std::optional<Asset::AssetTypeConditional_t<assetType>>()> newTask = std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this);
						return this->threadPool.AddTask(std::move(newTask));
					}
				}
				catch (...)
				{
					DEBUG_LOG({ "Can't Find proper extension : ", extension });
				}
			}

			return {};
		}
		
		/// <summary>
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>S
		/// <returns></returns>
		const std::vector<std::optional<Asset::AssetTypeConditional_t<assetType>>> ImportAsset(const std::vector<std::filesystem::path>& paths)
		{

			std::vector<std::optional<Asset::AssetTypeConditional_t<assetType>>> Assets{};

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
					catch (...)
					{
						DEBUG_LOG({ "Can't Find proper extension : ", extension });
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

		constexpr std::optional<Asset::AssetTypeConditional_t<assetType>> DummyFunction() { return {}; }
		/// <summary>
		/// Import Assets on multithread
		/// Main Thread wait until Every Importing Works is done
		/// Should Call This Function when you need So many Assets at time like Scene Loading
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		const std::vector<std::future<std::optional<Asset::AssetTypeConditional_t<assetType>>>> ImportAssetAsync(const std::vector<std::filesystem::path>& paths)
		{

			std::vector<std::function<std::optional<Asset::AssetTypeConditional_t<assetType>>()>> Tasks{};

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
					catch (...)
					{
						DEBUG_LOG({ "Can't Find proper extension : ", extension });
					}
				}
				else
				{
					DEBUG_LOG({ path.string(), " : Doesn't have file extension" });
				}
				DEBUG_LOG({ "Fail To ImportAsset", path.string() });
				Tasks.push_back(std::bind(&AssetImporter<assetType>::DummyFunction, this));

			}

			/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
			return this->threadPool.AddTaskChunk(Tasks);
		}
		
	};

	inline std::optional<Doom::Asset::AssetType> GetAssetType(const std::filesystem::path& path)
	{
		if (path.has_extension())
		{
			auto extension = path.extension().string();
			try
			{
				return AssetExtension.at(extension.substr(1, extension.length() - 1));

			}
			catch (...)
			{
				return {};
			}
		}

		return {};
	}
	

	
}


