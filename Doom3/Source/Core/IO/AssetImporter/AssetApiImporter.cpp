#include "AssetApiImporter.h"

#include "../../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"

#include "AssetImporterWorker_Three_D_Model.h"
namespace doom
{
	namespace assetimporter
	{

		template struct ClearApiImporterQueueFunctor<Asset::eAssetType::AUDIO>;
		template struct ClearApiImporterQueueFunctor<Asset::eAssetType::FONT>;
		template struct ClearApiImporterQueueFunctor<Asset::eAssetType::SHADER>;
		template struct ClearApiImporterQueueFunctor<Asset::eAssetType::TEXT>;
		template struct ClearApiImporterQueueFunctor<Asset::eAssetType::TEXTURE>;
		template struct ClearApiImporterQueueFunctor<Asset::eAssetType::THREE_D_MODEL>;

		template class AssetApiImporter<Asset::eAssetType::AUDIO>;
		template class AssetApiImporter<Asset::eAssetType::FONT>;
		template class AssetApiImporter<Asset::eAssetType::SHADER>;
		template class AssetApiImporter<Asset::eAssetType::TEXT>;
		template class AssetApiImporter<Asset::eAssetType::TEXTURE>;
		template class AssetApiImporter<Asset::eAssetType::THREE_D_MODEL>;

		DummyApiImporter _DummyApiImporter{};

		template <Asset::eAssetType assetType>
		constexpr AssetApiImporter<assetType>::AssetApiImporter(std::unique_ptr<api_importer_type_t<assetType>> importer) 
			: apiImporter{ std::move(importer) }
		{
		}

		template <Asset::eAssetType assetType>
		constexpr api_importer_type_t<assetType>* AssetApiImporter<assetType>::Get()
		{
			return apiImporter.get();
		}

		template <Asset::eAssetType assetType>
		constexpr void AssetApiImporter<assetType>::Release()
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

		template <Asset::eAssetType assetType>
		void AssetApiImporter<assetType>::ClearApiImporterQueue()
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

		template <Asset::eAssetType assetType>
		AssetApiImporter<assetType> AssetApiImporter<assetType>::GetApiImporter()
		{
			if constexpr (!std::is_same_v<api_importer_type_t<assetType>, DummyApiImporter>)
			{
				ApiImporterMutex.lock();

				std::unique_ptr<api_importer_type_t<assetType>> importer{};
				if (ApiImporterQueue.empty())
				{
					ApiImporterMutex.unlock();
					D_DEBUG_LOG("Create New AssetApiImporter", logger::LogType::D_ERROR);
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

		template<doom::Asset::eAssetType loopVariable>
		constexpr void doom::assetimporter::ClearApiImporterQueueFunctor<loopVariable>::operator()()
		{
			AssetApiImporter<loopVariable>::ClearApiImporterQueue();
		}

		void ClearAllApiImporterQueue()
		{
			ForLoop_CompileTime<Asset::eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, ClearApiImporterQueueFunctor>();
		}
	
	
		
	}
}

