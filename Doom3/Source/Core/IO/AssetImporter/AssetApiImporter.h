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


		template <Asset::eAssetType assetType>
		struct api_importer_type
		{
			using type = typename DummyApiImporter;
		};

		template <Asset::eAssetType assetType>
		using api_importer_type_t = typename api_importer_type<assetType>::type;

		/// <summary>
		/// RAII
		/// </summary>
		template <Asset::eAssetType assetType>
		class AssetApiImporter
		{
		private:
			std::unique_ptr<api_importer_type_t<assetType>> apiImporter;

			void InitApiImporter(api_importer_type_t<assetType>& apiImporter) {}
			static inline std::mutex ApiImporterMutex{};
			static inline std::queue<std::unique_ptr<api_importer_type_t<assetType>>> ApiImporterQueue;
		public:

			constexpr AssetApiImporter(std::unique_ptr<api_importer_type_t<assetType>> importer) : apiImporter{ std::move(importer) }
			{
			}

			const std::unique_ptr<api_importer_type_t<assetType>>& operator->() {
				return apiImporter;
			}

			constexpr void Release()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					DEBUG_LOG("Release Api Importer");
					auto lck = std::scoped_lock(ApiImporterMutex);
					ApiImporterQueue.push(std::move(apiImporter));
				
					//DEBUG_LOG({ std::to_string(assetType), "   ", std::to_string(ApiImporterQueue.size()) });
				}
				else
				{
					return;
				}
			}

			static constexpr void ClearApiImporterQueue()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					while (ApiImporterQueue.size() > 0)
					{
						ApiImporterQueue.pop();
					}
					DEBUG_LOG({ "Clear ApiImporterQueue ", assetType });
				}
			}

			static constexpr AssetApiImporter<assetType> GetApiImporter()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					ApiImporterMutex.lock();

					std::unique_ptr<api_importer_type_t<assetType>> importer{};
					if (ApiImporterQueue.empty())
					{
						ApiImporterMutex.unlock();
						DEBUG_LOG("Create New AssetApiImporter", log::LogType::D_ERROR);
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
					return std::unique_ptr(&_DummyApiImporter);
				}
			}



			

		};

		template<Asset::eAssetType loopVariable>
		struct ClearApiImporterQueueFunctor
		{
			constexpr inline void operator()()
			{
				AssetApiImporter<loopVariable>::ClearApiImporterQueue();
			}
		};
		inline void ClearAllApiImporterQueue()
		{
			ForLoop_CompileTime<Asset::eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, ClearApiImporterQueueFunctor>();
		}
		
	}
}