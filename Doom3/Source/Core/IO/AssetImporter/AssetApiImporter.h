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
		extern DummyApiImporter _DummyApiImporter;


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
			static inline std::queue<std::unique_ptr<api_importer_type_t<assetType>>> ApiImporterQueue{};
		public:

			constexpr AssetApiImporter(std::unique_ptr<api_importer_type_t<assetType>> importer);
			constexpr api_importer_type_t<assetType>* Get();

			constexpr void Release();
			static void ClearApiImporterQueue();
			static AssetApiImporter<assetType> GetApiImporter();
		};


		template<Asset::eAssetType loopVariable>
		struct ClearApiImporterQueueFunctor
		{
			constexpr void operator()();
		};

		

		inline void ClearAllApiImporterQueue()
		{
			ForLoop_CompileTime<Asset::eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, ClearApiImporterQueueFunctor>();
		}
		
	}
}