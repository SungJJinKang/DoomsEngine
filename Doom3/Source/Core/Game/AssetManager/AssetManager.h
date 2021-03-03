#pragma once
#include <filesystem>
#include <vector>
#include <array>

#include "../Core.h"
#include "../Asset/Asset.h"
#include "ImportedAssetPort.h"
#include "../IO/AssetImporter/AssetImporter.h"
#include "../IGameFlow.h"



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
					for (auto& asset : AssetManager::ImportedAssetPorts<loopVariable>.GetAssetsForIterating())
					{
						asset.OnEndImportInSubThread();
					}
				}
			};
			*/

			

		private:
			const std::filesystem::path AssetFolderPath{ ASSET_FOLDER_DIRECTORY };

			static inline std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()> AssetPaths{};

			template<eAssetType assetType>
			static inline ImportedAssetPort<assetType> ImportedAssetPorts{};

			static bool CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry);

		protected:
			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
		public:
			void ImportEntireAsset();
			
			template<eAssetType assetType>
			static typename ImportedAssetPort<assetType>::container_asset_type_t* ImportAsset(const std::filesystem::path& path)
			{
				auto importedAsset = doom::assetimporter::Assetimporter::ImportAsset<assetType>(path);
				if (importedAsset.has_value())
				{
					importedAsset.value().OnEndImportInMainThread();
					return AssetManager::ImportedAssetPorts<assetType>.SetAsset(std::move(importedAsset.value()));
				}			
				else
				{
					return nullptr;
				}
			}

			/// TODO : return 값으로 AssetContainer 안에 있는 asset container return 해주자
			template<eAssetType assetType>
			AssetContainer<assetType>& ImportAssetAsync(const std::filesystem::path& path)
			{
				return AssetManager::ImportedAssetPorts<assetType>.AddAssetFuture(doom::assetimporter::Assetimporter::PushImportingAssetJobToThreadPool<assetType>(path));
			}

			template<eAssetType assetType>
			std::vector<std::reference_wrapper<AssetContainer<assetType>>> ImportAssetAsync(const std::vector<std::filesystem::path>& paths)
			{
				return AssetManager::ImportedAssetPorts<assetType>.AddAssetFuture(doom::assetimporter::Assetimporter::PushImportingAssetJobToThreadPool<assetType>(paths));
			}

			

			template<eAssetType assetType>
			static typename ImportedAssetPort<assetType>::container_asset_type_t::asset_type* GetAsset(const D_UUID& UUID)
			{
				auto& assetCotainer = AssetManager::ImportedAssetPorts<assetType>;

				auto iter = assetCotainer.mAssets.find(UUID);
				if (iter != assetCotainer.mAssets.end())
				{//find!!
					return &(iter->second.get().GetImportedAsset());
				}
				else
				{//element containing UUID key doesn't exist
					return nullptr;
				}
			}

			template<eAssetType assetType>
			static typename ImportedAssetPort<assetType>::container_asset_type_t::asset_type* GetAsset(const unsigned int index)
			{
				if (index >= 0 && index < AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating.size())
				{
					return AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating[index].GetImportedAsset();
				}
				else
				{
					D_DEBUG_LOG({ "Cant Find Asset Index : ", std::to_string(index) }, eLogType::D_ERROR);
					return nullptr;
				}
			}

			/// <summary>
			/// BE CAREFUL, This function is so slow
			/// </summary>
			/// <param name="filename"></param>
			/// <returns></returns>
			template<eAssetType assetType>
			static typename ImportedAssetPort<assetType>::container_asset_type_t::asset_type* GetAsset(const std::string& filename)
			{
				auto iter = AssetManager::ImportedAssetPorts<assetType>.mAssetsForAssetName.find(filename);
				if (iter != AssetManager::ImportedAssetPorts<assetType>.mAssetsForAssetName.end())
				{//find!!
					return iter->second.get().GetImportedAsset();
				}
				else
				{//element containing UUID key doesn't exist
					D_DEBUG_LOG({ "Cant Find Asset Name : ", filename }, eLogType::D_ERROR);
					return nullptr;
				}
			}


			template<eAssetType assetType>
			static const std::vector<typename ImportedAssetPort<assetType>::container_asset_type_t::asset_type*> GetAssets()
			{
				std::vector<typename ImportedAssetPort<assetType>::container_asset_type_t::asset_type*> importedAssets{};
				for (auto& assetContainer : AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating)
				{
					importedAssets.push_back(assetContainer.get().GetImportedAsset());
				}
				return importedAssets;
			}

			static const std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()>& GetAllAssetPath();
			
		};

		template<eAssetType loopVariable>
		struct ImportAssetInitSetting
		{
			constexpr inline void operator()()
			{
				doom::assetimporter::InitAssetImport<loopVariable>();
			}

		};
		template<eAssetType loopVariable>
		struct ImportAssetFutureFunctor
		{
			constexpr inline void operator()(const std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()>& AssetPaths)
			{
				D_START_PROFILING("Add Importing Asset To ThreadPool : " + doom::Asset::GetAssetTypeString(loopVariable), doom::profiler::eProfileLayers::CPU);

				AssetManager::ImportedAssetPorts<loopVariable>.AddAssetFutures(doom::assetimporter::Assetimporter::PushImportingAssetJobToThreadPool<loopVariable>(AssetPaths[static_cast<unsigned int>(loopVariable)]), AssetPaths[static_cast<unsigned int>(loopVariable)]);

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

				AssetManager::ImportedAssetPorts<loopVariable>.GetAssetFutures();

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
					asset->OnEndImportInMainThread();
				}
			}
		};
	}
}



