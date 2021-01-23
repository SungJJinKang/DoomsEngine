#pragma once
#include <type_traits>
#include <queue>
#include <memory>
#include <mutex>

#include "../../Asset/Asset.h"

namespace Doom
{
	namespace AssetImporter
	{
		class DummyApiImporter
		{
		public:
			constexpr DummyApiImporter() {}
		};
		inline DummyApiImporter _DummyApiImporter{};


		template <Asset::AssetType assetType>
		struct api_importer_type
		{
			using type = typename DummyApiImporter;
		};

		template <Asset::AssetType assetType>
		using api_importer_type_t = typename api_importer_type<assetType>::type;

		/// <summary>
		/// RAII
		/// </summary>
		template <Asset::AssetType assetType>
		class AssetApiImporter
		{
		private:
			std::unique_ptr<api_importer_type_t<assetType>> apiImporter;

		public:

			static inline std::mutex ApiImporterMutex{};

			void InitApiImporter(api_importer_type_t<assetType>& apiImporter) {}

			static inline std::queue<std::unique_ptr<api_importer_type_t<assetType>>> ImporterQueue{};

			constexpr AssetApiImporter(std::unique_ptr<api_importer_type_t<assetType>> importer) : apiImporter{ std::move(importer) }
			{
			}

			const std::unique_ptr<api_importer_type_t<assetType>>& operator->() {
				return apiImporter;
			}

			void Release()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					DEBUG_LOG("Release Api Importer");
					auto lck = std::scoped_lock(ApiImporterMutex);
					ImporterQueue.push(std::move(apiImporter));
				}
				else
				{
					return;
				}
			}

			static AssetApiImporter<assetType> GetApiImporter()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					auto lck = std::scoped_lock(ApiImporterMutex);

					std::unique_ptr<api_importer_type_t<assetType>> importer{};
					if (ImporterQueue.empty())
					{
						DEBUG_LOG("Create New AssetApiImporter", LogType::D_ERROR);
						importer = std::make_unique<api_importer_type_t<assetType>>();
					}
					else
					{
						importer = std::move(ImporterQueue.front());
						ImporterQueue.pop(); // TODO : Check if front of queue is moved, What happen when pop
					}

					return std::move(importer);
				}
				else
				{
					return std::unique_ptr(&_DummyApiImporter);
				}
			}



			

		};

		

		
	}
}