#pragma once
#include <optional>
#include <map>
#include <string>
#include <functional>

#include "../../Core.h"

#include "../../Asset/Asset.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker.h"

#include "../../../Helper/ThreadPool_Cpp/ThreadPool.h"

namespace doom
{
	namespace assetimporter
	{
		template <eAssetType assetType>
		using imported_asset_future_t = typename std::future<std::optional<Asset::asset_type_t<assetType>>>;

		class Assetimporter
		{
			template <eAssetType assetType>
			friend class AssetImporterWorker;

		private:

			static const std::map<std::string, doom::eAssetType> AssetExtension;
			static inline std::unique_ptr<::ThreadPool> threadPool{};
			static void InitializeThreadPool(size_t poolSize);

		public:

			Assetimporter(size_t poolSize);
			~Assetimporter();
			static const std::unique_ptr<::ThreadPool>& GetThreadPool();
			static bool IsThreadPoolInitialized();

			
			template <eAssetType assetType>
			static std::optional<Asset::asset_type_t<assetType>> ImportAsset(std::filesystem::path path)
			{
				path.make_preferred();
				std::optional<Asset::asset_type_t<assetType>> ImportedAsset = AssetImporterWorker<assetType>::ImportSpecificAsset(path);

				if (ImportedAsset.has_value())
				{
					ImportedAsset.value().SetBaseMetaData(path);
				}
				return ImportedAsset;
			}
			

			/// <summary>
			/// Import A Asset Asyncly
			/// You Should check path extension using GetAssetType function
			/// </summary>
			/// <param name="path"></param>
			/// <returns></returns>
			template <eAssetType assetType>
			[[nodiscard]] static imported_asset_future_t<assetType> PushImportingAssetJobToThreadPool(const std::filesystem::path& path)
			{
				D_ASSERT(static_cast<bool>(threadPool) != false);

				std::function<std::optional<Asset::asset_type_t<assetType>>()> newTask = std::bind(ImportAsset<assetType>, path);

				D_DEBUG_LOG("Add new task to threadpool");
				return threadPool->push_back(std::move(newTask));
			}



			/// <summary>
			/// Import A Asset Asyncly
			/// If you need import multiple assets, use this function
			/// You Should check path extension using GetAssetType function
			/// </summary>
			/// <param name="path"></param>
			/// <param name="assets"></param>
			/// <returns></returns>
			template <eAssetType assetType>
			[[nodiscard]] static std::vector<imported_asset_future_t<assetType>> PushImportingAssetJobToThreadPool(const std::vector<std::filesystem::path>& paths)
			{
				D_ASSERT(static_cast<bool>(threadPool) != false);

				std::vector<std::function<std::optional<Asset::asset_type_t<assetType>>()>> Tasks{};
				Tasks.reserve(paths.size());
				for (auto& path : paths)
				{
					Tasks.push_back(std::bind(ImportAsset<assetType>, path));
				}

				D_DEBUG_LOG("Add new task to threadpool");
				/// <summary>
				/// maybe will be copied
				/// </summary>
				/// <param name="paths"></param>
				/// <returns></returns>
				return threadPool->push_back_chunk(std::move(Tasks));
			}

			///////////////////

			static std::optional<doom::eAssetType> GetAssetType(const std::filesystem::path& path);
		};

		
	}
}
