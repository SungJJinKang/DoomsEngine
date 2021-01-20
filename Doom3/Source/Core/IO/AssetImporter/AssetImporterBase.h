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
		{"dae", Doom::Asset::AssetType::THREE_D_MODEL},
		{"blend", Doom::Asset::AssetType::THREE_D_MODEL},
		{"bvh", Doom::Asset::AssetType::THREE_D_MODEL},
		{"3ds", Doom::Asset::AssetType::THREE_D_MODEL},
		{"ase", Doom::Asset::AssetType::THREE_D_MODEL},
		{"obj", Doom::Asset::AssetType::THREE_D_MODEL},
		{"glFT", Doom::Asset::AssetType::THREE_D_MODEL},
		{"ply", Doom::Asset::AssetType::THREE_D_MODEL},
		{"dxf", Doom::Asset::AssetType::THREE_D_MODEL},
		{"ifc", Doom::Asset::AssetType::THREE_D_MODEL},
		{"nff", Doom::Asset::AssetType::THREE_D_MODEL},
		{"smd", Doom::Asset::AssetType::THREE_D_MODEL},
		{"vta", Doom::Asset::AssetType::THREE_D_MODEL},
		{"mdl", Doom::Asset::AssetType::THREE_D_MODEL},
		{"mdl2", Doom::Asset::AssetType::THREE_D_MODEL},
		{"mdl3", Doom::Asset::AssetType::THREE_D_MODEL},
		{"pk3", Doom::Asset::AssetType::THREE_D_MODEL},
		{"mdmdcl2", Doom::Asset::AssetType::THREE_D_MODEL},
		{"md5mesh", Doom::Asset::AssetType::THREE_D_MODEL},
		{"md5anim", Doom::Asset::AssetType::THREE_D_MODEL},
		{"md5camera ", Doom::Asset::AssetType::THREE_D_MODEL},
		{"q3o", Doom::Asset::AssetType::THREE_D_MODEL},
		{"q3s", Doom::Asset::AssetType::THREE_D_MODEL},
		{"raw", Doom::Asset::AssetType::THREE_D_MODEL},
		{"ac", Doom::Asset::AssetType::THREE_D_MODEL},
		{"stl", Doom::Asset::AssetType::THREE_D_MODEL},
		{"dxf", Doom::Asset::AssetType::THREE_D_MODEL},
		{"irrmesh", Doom::Asset::AssetType::THREE_D_MODEL},
		{"irr", Doom::Asset::AssetType::THREE_D_MODEL},
		{"off", Doom::Asset::AssetType::THREE_D_MODEL},
		{"dterxf", Doom::Asset::AssetType::THREE_D_MODEL},
		{"mdl", Doom::Asset::AssetType::THREE_D_MODEL},
		{"hmp", Doom::Asset::AssetType::THREE_D_MODEL},
		{"mesh", Doom::Asset::AssetType::THREE_D_MODEL},
		{"skeleton", Doom::Asset::AssetType::THREE_D_MODEL},
		{"material", Doom::Asset::AssetType::THREE_D_MODEL},
		{"ms3d", Doom::Asset::AssetType::THREE_D_MODEL},
		{"lwo", Doom::Asset::AssetType::THREE_D_MODEL},
		{"lws", Doom::Asset::AssetType::THREE_D_MODEL},
		{"lxo", Doom::Asset::AssetType::THREE_D_MODEL},
		{"csm", Doom::Asset::AssetType::THREE_D_MODEL},
		{"ply", Doom::Asset::AssetType::THREE_D_MODEL},
		{"cob", Doom::Asset::AssetType::THREE_D_MODEL},
		{"scn", Doom::Asset::AssetType::THREE_D_MODEL},
		{"fbx", Doom::Asset::AssetType::THREE_D_MODEL},
		//////////////////////////////////////////////////////////////////////////

		{"txt", Doom::Asset::AssetType::TEXT},
		{"ini", Doom::Asset::AssetType::TEXT},

		/////////////////////////////////////////////////////

		{"glsl", Doom::Asset::AssetType::SHADER},

		/////////////////////////////////////////////////////////

		{"jpg", Doom::Asset::AssetType::TEXTURE},
		{"jpeg", Doom::Asset::AssetType::TEXTURE},
		{"png", Doom::Asset::AssetType::TEXTURE},
		{"bmp", Doom::Asset::AssetType::TEXTURE},
		{"psd", Doom::Asset::AssetType::TEXTURE},
		{"tga", Doom::Asset::AssetType::TEXTURE},
		{"hdr", Doom::Asset::AssetType::TEXTURE},
		{"pic", Doom::Asset::AssetType::TEXTURE},
		{"pnm", Doom::Asset::AssetType::TEXTURE},


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

	

	/// <summary>
	/// ThreadPool Manager For AssetImporter
	/// This exist for managing Life cycle of ThreadPool (RAII)
	/// Use Scope "{ AssetImporterThreadPoolManager pool{5}  }" !!!!!
	/// </summary>
	class AssetImporterThreadPool
	{
	private:
		static inline ::ThreadPool* threadPool{ nullptr };
		
		static void InitializeThreadPool(size_t poolSize)
		{
			DEBUG_LOG( { "Create Asset Importer Thread Pool", std::to_string(poolSize) } );
			AssetImporterThreadPool::threadPool = new ::ThreadPool(poolSize);
		}
	public:
		

		AssetImporterThreadPool(size_t poolSize)
		{
			if (threadPool == nullptr)
			{
				InitializeThreadPool(poolSize);
			}
			else
			{
				DEBUG_LOG("AssetImporter Thread Pool is already initialized");
			}
		}

		~AssetImporterThreadPool()
		{
			if (threadPool != nullptr)
			{
				DEBUG_LOG("Deleting Importer Thread Pool");
				delete AssetImporterThreadPool::threadPool;
				DEBUG_LOG("Complete Delete Importer Thread Pool");
				AssetImporterThreadPool::threadPool = nullptr;
			}
		}

		static ::ThreadPool* const GetThreadPool()
		{
			if (threadPool == nullptr)
			{
				InitializeThreadPool(1);
			}

			return threadPool;
		}

		static bool IsThreadPoolInitialized()
		{
			return threadPool != nullptr;
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
		

		using ApiImporterType = typename ApiImporterTypeConditional_t<assetType>;

		std::mutex apiImporterMutex;

		std::vector<ApiImporterType> ApiImporters;

		void InitApiImporter(ApiImporterType& apiImporter) {}

		std::queue<ApiImporterType*> ImporterQueue;

		
		public:
		constexpr AssetImporter() : ApiImporters{ AssetImporterThreadPool::GetThreadPool()->PoolSize }, apiImporterMutex{}, ImporterQueue{}
		{

			for (size_t i = 0; i < AssetImporterThreadPool::GetThreadPool()->PoolSize; i++)
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
		/// Import A Asset Asyncly
		/// You Should check path extension using GetAssetType function
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		const std::future<std::optional<Asset::AssetTypeConditional_t<assetType>>>  ImportAsset(const std::filesystem::path& path)
		{
			if (AssetImporterThreadPool::IsThreadPoolInitialized() == false)
			{//if threadpool isn't initialized
				DEBUG_LOG("You should Initialize AssetImporter Thread Pool using \"InitializeThreadPool\"  Before Import Asset ", LogType::D_ERROR);
				
			}

			std::function<std::optional<Asset::AssetTypeConditional_t<assetType>>()> newTask = std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this);
			return AssetImporterThreadPool::GetThreadPool()->AddTask(std::move(newTask));
		}

		constexpr std::optional<Asset::AssetTypeConditional_t<assetType>> DummyFunction() { return {}; }
		
		/// <summary>
		/// Import A Asset Asyncly
		/// If you need import multiple assets, use this function
		/// You Should check path extension using GetAssetType function
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		const std::vector<std::future<std::optional<Asset::AssetTypeConditional_t<assetType>>>> ImportAsset(const std::vector<std::filesystem::path>& paths)
		{
			if (AssetImporterThreadPool::IsThreadPoolInitialized() == false)
			{//if threadpool isn't initialized
				DEBUG_LOG("You should Initialize AssetImporter Thread Pool using \"InitializeThreadPool\"  Before Import Asset ", LogType::D_ERROR);
			}

			std::vector<std::function<std::optional<Asset::AssetTypeConditional_t<assetType>>()>> Tasks{};
			Tasks.reserve(paths.size());
			for (auto& path : paths)
			{
				Tasks.push_back(std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this));
			}
			
			
			/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
			return AssetImporterThreadPool::GetThreadPool()->AddTaskChunk(Tasks);
		}
		
	};

	inline std::optional<Doom::Asset::AssetType> GetAssetType(const std::filesystem::path& path)
	{
		if (path.has_extension())
		{auto extension = path.extension().string();
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


