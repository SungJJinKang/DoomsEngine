#pragma once
#include <type_traits>
#include <memory>

#include <concurrentqueue/blockingconcurrentqueue.h>

#include "../../Asset/Asset.h"
#include "DummyApiImporter.h"


namespace doom
{
	namespace assetimporter
	{
		template <::doom::asset::eAssetType assetType>
		struct api_importer_type
		{
			using type = typename DummyApiImporter;
		};


		template <::doom::asset::eAssetType assetType>
		using api_importer_type_t = typename api_importer_type<assetType>::type;

		/// <summary>
		/// Contain Asset Api side Importer object
		/// </summary>
		template <::doom::asset::eAssetType assetType>
		class DOOM_API AssetApiImporter : public DObject
		{
			template <::doom::asset::eAssetType assetType>
			friend class AssetImporterWorker;

			template<::doom::asset::eAssetType loopVariable>
			friend struct ClearApiImporterQueueFunctor;
		private:
			std::unique_ptr<api_importer_type_t<assetType>> apiImporter;

			void InitApiImporter(api_importer_type_t<assetType>& apiImporter) {}

			static moodycamel::BlockingConcurrentQueue<std::unique_ptr<api_importer_type_t<assetType>>> ApiImporterQueue;

			constexpr AssetApiImporter(std::unique_ptr<api_importer_type_t<assetType>> importer)
				: apiImporter{ std::move(importer) }
			{
			}
			~AssetApiImporter()
			{
				Release();
			}

			api_importer_type_t<assetType>* operator->() const
			{
				return apiImporter.get();
			}

			api_importer_type_t<assetType>& operator*() const
			{
				return *(apiImporter.get());
			}

			void Release()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					if (apiImporter != nullptr)
					{
						D_DEBUG_LOG("Release Api Importer");
						ApiImporterQueue.enqueue(std::move(apiImporter));
					}
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
					std::unique_ptr<api_importer_type_t<assetType>> temp{};
					while (ApiImporterQueue.try_dequeue(temp))
					{
					}
					D_DEBUG_LOG({ "Clear ApiImporterQueue ", static_cast<unsigned int>(assetType) });
				}
			}
			static AssetApiImporter<assetType> GetApiImporter()
			{
				if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
				{
					std::unique_ptr<api_importer_type_t<assetType>> importer{};
					if (ApiImporterQueue.try_dequeue(importer) == false)
					{
						//D_DEBUG_LOG("Create New AssetApiImporter", logger::eLogType::D_ERROR);
						importer = std::make_unique<api_importer_type_t<assetType>>();
					}

					return std::move(importer);
				}
				else
				{
					return std::unique_ptr<api_importer_type_t<assetType>>(&_DummyApiImporter);
				}
			}

			

		};


		template<::doom::asset::eAssetType loopVariable>
		struct DOOM_API ClearApiImporterQueueFunctor
		{
			constexpr void operator()()
			{
				AssetApiImporter<loopVariable>::ClearApiImporterQueue();
			}
		};
		void ClearAllApiImporterQueue();
	

		
	}
}