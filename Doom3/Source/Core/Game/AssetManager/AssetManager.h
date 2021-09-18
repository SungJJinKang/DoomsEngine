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
		template<::doom::asset::eAssetType loopVariable>
		struct ImportAssetFunctor;

		template<::doom::asset::eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor;

		class AssetManager : public IGameFlow, public ISingleton<AssetManager>
		{
			template<::doom::asset::eAssetType loopVariable>
			friend struct ImportAssetFunctor;

			template<::doom::asset::eAssetType loopVariable>
			friend struct OnEndImportInMainThreadFunctor;
			/*
			template<::doom::asset::eAssetType loopVariable>
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

			std::array<std::vector<std::filesystem::path>, doom::asset::ENUM_ASSETTYPE_COUNT> AssetPaths{};

			template<::doom::asset::eAssetType assetType>
			static inline ImportedAssetPort<assetType> ImportedAssetPorts{};

			void LoadAssetManagerSetting();

			static bool CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry);

			std::vector<std::future<bool>> mWaitingImportFuture{};
			void GetWaitingImportFuture();
		
			void ImportEntireAsset();

		public:

	

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			
			template<::doom::asset::eAssetType assetType>
			static ::doom::asset::Asset::asset_type_t<assetType>* ImportAssetInstantly(std::filesystem::path& path)
			{
				path.make_preferred();
				doom::asset::Asset::asset_type_t<assetType>* newAsset = AssetManager::ImportedAssetPorts<assetType>.AddNewAsset(path);
				bool IsSuccess = doom::assetimporter::Assetimporter::ImportAssetJob<assetType>(path, newAsset);

				if (IsSuccess)
				{
					newAsset->OnEndImportInMainThread_Internal();
					return newAsset;
				}			
				else
				{
					return nullptr;
				}
			}

			/// TODO : return 값으로 AssetContainer 안에 있는 asset container return 해주자
			template<::doom::asset::eAssetType assetType>
			void ImportAssetAsync(std::filesystem::path& path)
			{
				path.make_preferred();
				doom::asset::Asset::asset_type_t<assetType>* newAsset = AssetManager::ImportedAssetPorts<assetType>.AddNewAsset(path);
				std::future<bool> assetFuture{ doom::assetimporter::Assetimporter::PushImportingAssetJobToThreadPool<assetType>(path, newAsset) };
				mWaitingImportFuture.push_back(std::move(assetFuture));
			}

			template<::doom::asset::eAssetType assetType>
			void ImportAssetAsync(std::vector<std::filesystem::path>& paths)
			{
				std::vector<::doom::asset::Asset::asset_type_t<assetType>*> newAssets{};
				newAssets.reserve(paths.size());
				for (unsigned int i = 0; i < paths.size(); i++)
				{
					paths[i].make_preferred();
					newAssets.push_back(AssetManager::ImportedAssetPorts<assetType>.AddNewAsset(paths[i]));
				}

				std::vector<std::future<bool>> assetFutures = doom::assetimporter::Assetimporter::PushImportingAssetJobToThreadPool<assetType>(paths, newAssets);
				mWaitingImportFuture.insert(mWaitingImportFuture.end(), std::make_move_iterator(assetFutures.begin()), std::make_move_iterator(assetFutures.end()));
			}

			

			template<::doom::asset::eAssetType assetType>
			static typename ::doom::asset::Asset::asset_type_t<assetType>* GetAsset(const D_UUID& UUID)
			{
				auto& assetCotainer = AssetManager::ImportedAssetPorts<assetType>;

				auto iter = assetCotainer.mAssets.find(UUID);
				if (iter != assetCotainer.mAssets.end())
				{//find!!
					return &(iter->second);
				}
				else
				{//element containing UUID key doesn't exist
					D_ASSERT("Can't Find Asset");
					return nullptr;
				}
			}

			template<::doom::asset::eAssetType assetType>
			static typename ::doom::asset::Asset::asset_type_t<assetType>* GetAsset(const unsigned int index)
			{
				if (index >= 0 && index < AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating.size())
				{
					return AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating[index];
				}
				else
				{
					D_ASSERT("Can't Find Asset");
					return nullptr;
				}
			}

			/// <summary>
			/// BE CAREFUL, This function is so slow
			/// </summary>
			/// <param name="filename"></param>
			/// <returns></returns>
			template<::doom::asset::eAssetType assetType>
			static typename ::doom::asset::Asset::asset_type_t<assetType>* GetAsset(const std::string& filename)
			{
				auto iter = AssetManager::ImportedAssetPorts<assetType>.mAssetsForAssetName.find(filename);
				if (iter != AssetManager::ImportedAssetPorts<assetType>.mAssetsForAssetName.end())
				{//find!!
					return iter->second;
				}
				else
				{//element containing UUID key doesn't exist
					D_ASSERT("Can't Find Asset");
					return nullptr;
				}
			}


			template<::doom::asset::eAssetType assetType>
			static std::vector<::doom::asset::Asset::asset_type_t<assetType>*> GetAssets()
			{
				std::vector<typename ::doom::asset::Asset::asset_type_t<assetType>* > importedAssets{};
				importedAssets.reserve(AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating.size());
				importedAssets.insert(importedAssets.end(), AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating.begin(), AssetManager::ImportedAssetPorts<assetType>.mAssetsForIterating.end());
				return importedAssets;
			}

			const std::array<std::vector<std::filesystem::path>, doom::asset::ENUM_ASSETTYPE_COUNT>& GetAllAssetPath();
			
		};

		template<::doom::asset::eAssetType loopVariable>
		struct ImportAssetInitSetting
		{
			constexpr inline void operator()()
			{
				doom::assetimporter::InitAssetImport<loopVariable>();
			}

		};
		template<::doom::asset::eAssetType loopVariable>
		struct ImportAssetFunctor
		{
			constexpr inline void operator()(std::array<std::vector<std::filesystem::path>, doom::asset::ENUM_ASSETTYPE_COUNT>& assetPaths)
			{
				AssetManager::GetSingleton()->ImportAssetAsync<loopVariable>(assetPaths[static_cast<unsigned int>(loopVariable)]);
			}
		};

		/// <summary>
		/// 
		/// </summary>
		template<::doom::asset::eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor
		{
			constexpr inline void operator()()
			{
				for (auto asset : AssetManager::GetAssets<loopVariable>())
				{
					asset->OnEndImportInMainThread();
				}
			}
		};
	}
}



