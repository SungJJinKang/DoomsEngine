#pragma once
#include <optional>
#include <unordered_map>
#include <string>
#include <functional>

#include "../../Core.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker.h"

#include "../ResourceManagement/JobSystem_cpp/JobSystem.h"
#include "UI/PrintText.h"

namespace doom
{
	namespace assetimporter
	{
		class AssetManager;

		

		class DOOM_API Assetimporter : public DObject
		{
			friend class AssetManager;

			template <::doom::asset::eAssetType assetType>
			friend class AssetImporterWorker;

			template<::doom::asset::eAssetType loopVariable>
			friend struct ImportAssetFunctor;

		private:

			/// <summary>
			/// Avaliable Asset Extensions of ::doom::asset::eAssetType
			/// </summary>
			static const std::unordered_map<std::string, ::doom::asset::eAssetType> AssetExtension;
			/// <summary>
			/// This extensions will be included in build(release) version
			/// if there is no InBuildExtension of AssetType(::doom::asset::eAssetType), Any extensions is allowed
			/// </summary>
			static const std::unordered_map<::doom::asset::eAssetType, std::string> AssetInBuildExtension;

			/// <summary>
			/// 
			/// </summary>
			/// <param name="path"></param>
			/// <param name="asset"></param>
			/// <returns>Is Success??</returns>
			template <::doom::asset::eAssetType assetType>
			static bool ImportAssetJob(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<assetType>* asset)
			{
				bool isSuccess = AssetImporterWorker<assetType>::ImportSpecificAsset(path, *asset);
				if (isSuccess)
				{
					asset->mAssetStatus = ::doom::asset::Asset::AssetStatus::CompletlyImported;
					doom::ui::PrintText("Import Success : %s", path.string().c_str());
				}
				else
				{
					asset->mAssetStatus = ::doom::asset::Asset::AssetStatus::FailToImport;
				}
				
				return isSuccess;
				
			}
			

			/// <summary>
			/// Import A Asset Asyncly
			/// You Should check path extension using GetAssetType function
			/// </summary>
			/// <param name="path"></param>
			/// <returns></returns>
			template <::doom::asset::eAssetType assetType>
			[[nodiscard]] static std::future<bool> PushImportingAssetJobToThreadPool(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<assetType>* asset)
			{
				std::function<bool()> newTask = std::bind(ImportAssetJob<assetType>, path, asset);
				asset->mAssetStatus = ::doom::asset::Asset::AssetStatus::WaitingImport;

				return resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(std::move(newTask));
			}



			/// <summary>
			/// Import A Asset Asyncly
			/// If you need import multiple assets, use this function
			/// You Should check path extension using GetAssetType function
			/// </summary>
			/// <param name="path"></param>
			/// <param name="assets"></param>
			/// <returns></returns>
			template <::doom::asset::eAssetType assetType>
			[[nodiscard]] static std::vector<std::future<bool>> PushImportingAssetJobToThreadPool(const std::vector<std::filesystem::path>& paths, const std::vector<::doom::asset::Asset::asset_type_t<assetType>*>& assets)
			{
				D_ASSERT(paths.size() == assets.size());

				std::vector<std::function<bool()>> newTasks{};
				newTasks.reserve(paths.size());
				for (unsigned int i = 0 ; i < paths.size() ; i++)
				{
					newTasks.push_back(std::bind(ImportAssetJob<assetType>, paths[i], assets[i]));
					assets[i]->mAssetStatus = ::doom::asset::Asset::AssetStatus::WaitingImport;
				}

				/// <summary>
				/// maybe will be copied
				/// </summary>
				/// <param name="paths"></param>
				/// <returns></returns>
				return resource::JobSystem::GetSingleton()->PushBackJobChunkToPriorityQueue(std::move(newTasks));
			}

			///////////////////

			static std::optional<::doom::asset::eAssetType> GetAssetType(const std::filesystem::path& path);
		};

		
	}
}
