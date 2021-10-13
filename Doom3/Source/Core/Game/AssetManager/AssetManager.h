#pragma once
#include <filesystem>
#include <vector>
#include <array>

#include "../Core.h"
#include "../IGameFlow.h"

#include "../Asset/Asset.h"
#include "AssetContainer.h"
#include "../IO/AssetImporter/AssetImporter.h"
#include <Asset/AssetsForwardDeclaration.h>
#include "AssetFuture.h"
#include <IO/AssetImporter/Manager/AssetImporterWorkerManager.h>

namespace doom
{
	namespace assetimporter
	{
		class DOOM_API AssetManager : public IGameFlow, public ISingleton<AssetManager>
		{
			friend class AssetFuture;

		private:

			AssetImporterWorkerManager mAssetImporterWorkerManager;

			const std::filesystem::path AssetFolderPath{ doom::path::_GetAssetFolderDirectory() };
			
			std::array<doom::asset::AssetContainer, doom::asset::ENUM_ASSETTYPE_COUNT> mAssetConatiners
			{
				doom::asset::AssetContainer(doom::asset::eAssetType::AUDIO),
				doom::asset::AssetContainer(doom::asset::eAssetType::FONT),
				doom::asset::AssetContainer(doom::asset::eAssetType::TEXT),
				doom::asset::AssetContainer(doom::asset::eAssetType::TEXTURE),
				doom::asset::AssetContainer(doom::asset::eAssetType::THREE_D_MODEL),
				doom::asset::AssetContainer(doom::asset::eAssetType::SHADER)
			}
			;
			
			void LoadAssetManagerSetting();

			static bool CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry);


			void ImportEntireAsset();
			void DestroyAllAssets();

			doom::asset::AssetContainer& GetAssetContainer(const doom::asset::eAssetType eAssetType);

			void AddAssetToAssetContainer(doom::asset::Asset* const asset);

			doom::asset::Asset* _ImportAssetInstantly(std::filesystem::path& path, const doom::asset::eAssetType assetType);
			doom::assetimporter::AssetFuture _ImportAssetAsync(std::filesystem::path& path, const doom::asset::eAssetType assetType);
			std::vector < doom::assetimporter::AssetFuture> _ImportAssetAsync(std::vector<std::filesystem::path>& paths, const std::vector<doom::asset::eAssetType>& assetTypes);
	

			doom::asset::Asset* _GetAsset(const D_UUID& UUID, const doom::asset::eAssetType assetType);
			doom::asset::Asset* _GetAsset(const unsigned int index, const doom::asset::eAssetType assetType);
			doom::asset::Asset* _GetAsset(const std::string& filename, const doom::asset::eAssetType assetType);

		public:

			AssetManager() = default;
			~AssetManager();

			

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			
			template<::doom::asset::eAssetType AssetType>
			typename doom::asset::AssetType<AssetType>::type* ImportAssetInstantly(std::filesystem::path path)
			{
				static_assert(std::is_base_of_v<doom::asset::Asset, AssetType> == true);

				doom::asset::Asset* const newAsset = _ImportAssetInstantly(path, AssetType);
				return reinterpret_cast<typename doom::asset::AssetType<AssetType>::type*>(newAsset);
			}
			
			doom::assetimporter::AssetFuture ImportAssetAsync(std::filesystem::path path, const ::doom::asset::eAssetType assetType)
			{
				doom::assetimporter::AssetFuture importedAssetFuture = _ImportAssetAsync(path, assetType);
				return importedAssetFuture;
			}

			

			template<::doom::asset::eAssetType AssetType>
			typename doom::asset::AssetType<AssetType>::type* GetAsset(const D_UUID& UUID)
			{
				doom::asset::Asset* const asset = _GetAsset(UUID, AssetType);
				return reinterpret_cast<typename doom::asset::AssetType<AssetType>::type*>(asset);
			}

			template<::doom::asset::eAssetType AssetType>
			typename doom::asset::AssetType<AssetType>::type* GetAsset(const unsigned int index)
			{
				doom::asset::Asset* const asset = _GetAsset(index, AssetType);
				return reinterpret_cast<typename doom::asset::AssetType<AssetType>::type*>(asset);
			}

			/// <summary>
			/// BE CAREFUL, This function is so slow
			/// </summary>
			/// <param name="filename"></param>
			/// <returns></returns>
			template<::doom::asset::eAssetType AssetType>
			typename doom::asset::AssetType<AssetType>::type* GetAsset(const std::string& filename)
			{
				doom::asset::Asset* const asset = _GetAsset(filename, AssetType);
				return reinterpret_cast<typename doom::asset::AssetType<AssetType>::type* const>(asset);
			}


		
			
		};


	}
}



