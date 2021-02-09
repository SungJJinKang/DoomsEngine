#pragma once
#include <type_traits>
#include <queue>
#include <memory>
#include <mutex>

#include "../../Asset/Asset.h"
#include "../../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"

namespace doom
{
	namespace assetimporter
	{
		class DummyApiImporter
		{
		public:
			constexpr DummyApiImporter() {}
		};
		inline DummyApiImporter _DummyApiImporter{};


		template <eAssetType assetType>
		struct api_importer_type
		{
			using type = typename DummyApiImporter;
		};


		template <eAssetType assetType>
		using api_importer_type_t = typename api_importer_type<assetType>::type;

		/// <summary>
		/// RAII
		/// </summary>
		template <eAssetType assetType>
		class AssetApiImporter
		{
		private:
			std::unique_ptr<api_importer_type_t<assetType>> apiImporter;

			void InitApiImporter(api_importer_type_t<assetType>& apiImporter) {}
			static inline std::mutex ApiImporterMutex{};
			static inline std::queue<std::unique_ptr<api_importer_type_t<assetType>>> ApiImporterQueue{};
		public:

			constexpr AssetApiImporter(std::unique_ptr<api_importer_type_t<assetType>> importer)
				: apiImporter{ std::move(importer) }
			{
			}
			api_importer_type_t<assetType>* Get()
			{
				return apiImporter.get();
			}

			void Release()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					D_DEBUG_LOG("Release Api Importer");
					auto lck = std::scoped_lock(ApiImporterMutex);
					ApiImporterQueue.push(std::move(apiImporter));

					//DEBUG_LOG({ std::to_string(assetType), "   ", std::to_string(ApiImporterQueue.size()) });
				}
				else
				{
					return;
				}
			}
			static void ClearApiImporterQueue()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					while (ApiImporterQueue.size() > 0)
					{
						ApiImporterQueue.pop();
					}
					D_DEBUG_LOG({ "Clear ApiImporterQueue ", static_cast<unsigned int>(assetType) });
				}
			}
			static AssetApiImporter<assetType> GetApiImporter()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					ApiImporterMutex.lock();

					std::unique_ptr<api_importer_type_t<assetType>> importer{};
					if (ApiImporterQueue.empty())
					{
						ApiImporterMutex.unlock();
						D_DEBUG_LOG("Create New AssetApiImporter", logger::eLogType::D_ERROR);
						importer = std::make_unique<api_importer_type_t<assetType>>();
					}
					else
					{
						importer = std::move(ApiImporterQueue.front());
						ApiImporterQueue.pop();
						ApiImporterMutex.unlock();
						//DEBUG_LOG({ std::to_string(assetType), "   ", std::to_string(ApiImporterQueue.size()) });
					}

					return std::move(importer);
				}
				else
				{
					return std::unique_ptr<api_importer_type_t<assetType>>(&_DummyApiImporter);
				}
			}
		};


		template<eAssetType loopVariable>
		struct ClearApiImporterQueueFunctor
		{
			constexpr void operator()()
			{
				AssetApiImporter<loopVariable>::ClearApiImporterQueue();
			}
		};

		

		inline void ClearAllApiImporterQueue()
		{
			ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, ClearApiImporterQueueFunctor>();
		}
		
	}
}