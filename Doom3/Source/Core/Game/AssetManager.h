#pragma once
#include <filesystem>
#include <vector>
#include <array>

#include "../Core.h"
#include "../Asset/Asset.h"
#include "AssetContainer.h"
#include "../IO/AssetImporter/AssetImporter.h"
#include "IGameFlow.h"
#include "../../Helper/Singleton.h"



namespace doom
{

	namespace assetimporter
	{
		template<eAssetType loopVariable>
		struct ImportAssetFutureFunctor;
		template<eAssetType loopVariable>
		struct GetAssetFutureFunctor;
		template<eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor;

		class AssetManager : public IGameFlow, public ISingleton<AssetManager>
		{
			template<eAssetType loopVariable>
			friend struct ImportAssetFutureFunctor;

			template<eAssetType loopVariable>
			friend struct GetAssetFutureFunctor;

			template<eAssetType loopVariable>
			friend struct OnEndImportInMainThreadFunctor;
			/*
			template<eAssetType loopVariable>
			struct OnEndImportInSubThreadFunctor
			{
				constexpr inline void operator()()
				{
					for (auto& asset : AssetManager::ImportedAssets<loopVariable>.GetAssetsForIterating())
					{
						asset.OnEndImportInSubThread();
					}
				}
			};
			*/

			

		private:
			const std::filesystem::path AssetFolderPath{ ASSET_FOLDER_DIRECTORY };

			template<eAssetType assetType>
			static inline AssetContainer<assetType> ImportedAssets{};

		protected:
			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
		public:
			void ImportEntireAsset();

		
			template<eAssetType assetType>
			static std::optional<std::reference_wrapper<typename AssetContainer<assetType>::container_asset_type_t>> GetAsset(const D_UUID& UUID) 
			{
				auto& assetCotainer = AssetManager::ImportedAssets<assetType>;

				auto iter = assetCotainer.mAssets.find(UUID);
				if (iter != assetCotainer.mAssets.end())
				{//find!!
					return iter->second;
				}
				else
				{//element containing UUID key doesn't exist
					return {};
				}
			}

			template<eAssetType assetType>
			static std::optional<std::reference_wrapper<typename AssetContainer<assetType>::container_asset_type_t>> GetAsset(const unsigned int index)
			{
				if (index >= 0 && index < AssetManager::ImportedAssets<assetType>.mAssetsForIterating.size())
				{
					return AssetManager::ImportedAssets<assetType>.mAssetsForIterating[index];
				}
				else
				{
					return {};
				}
			}

			template<eAssetType assetType>
			static std::optional<std::reference_wrapper<typename AssetContainer<assetType>::container_asset_type_t>> GetAsset(const std::string& filename)
			{
				for (auto& asset : AssetManager::ImportedAssets<assetType>.mAssetsForIterating)
				{
					if (asset.GetAssetFileName() == filename)
					{
						return asset;
					}
				}
				
				return {};
			}


			template<eAssetType assetType>
			static const std::vector<std::reference_wrapper<typename AssetContainer<assetType>::container_asset_type_t>>& GetAssets()
			{
				return AssetManager::ImportedAssets<assetType>.mAssetsForIterating;
			}

		};

		template<eAssetType loopVariable>
		struct ImportAssetFutureFunctor
		{
			constexpr inline void operator()(const std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()>& AssetPaths)
			{
				std::string name{ "Add Importing Asset To ThreadPool : " };
				name += doom::Asset::GetAssetTypeString(loopVariable);
				D_START_PROFILING(name.c_str(), doom::profiler::eProfileLayers::CPU);

				AssetManager::ImportedAssets<loopVariable>.AddAssetFutures(doom::assetimporter::Assetimporter::PushImportingAssetJobToThreadPool<loopVariable>(AssetPaths[static_cast<unsigned int>(loopVariable)]));

				D_END_PROFILING(name.c_str());
			}
		};

		template<eAssetType loopVariable>
		struct GetAssetFutureFunctor
		{
			constexpr inline void operator()()
			{
				std::string name{ "Get Imported Assets's Future : " };
				name += doom::Asset::GetAssetTypeString(loopVariable);
				D_START_PROFILING(name.c_str(), doom::profiler::eProfileLayers::CPU);

				AssetManager::ImportedAssets<loopVariable>.GetAssetFutures();

				D_END_PROFILING(name.c_str());
			}
		};

		/// <summary>
		/// 
		/// </summary>
		template<eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor
		{
			constexpr inline void operator()()
			{
				for (auto& asset : AssetManager::GetAssets<loopVariable>())
				{
					asset.get().OnEndImportInMainThread();
				}
			}
		};
	}
}



