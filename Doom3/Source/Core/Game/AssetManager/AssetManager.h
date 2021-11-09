#pragma once
#include <filesystem>
#include <vector>
#include <array>

#include "../Core.h"
#include "../IGameFlow.h"

#include "../Asset/Asset.h"
#include "AssetContainer.h"
#include "../IO/AssetImporter/assetImporter.h"
#include <Asset/AssetsForwardDeclaration.h>
#include "AssetFuture.h"
#include <IO/AssetImporter/Manager/AssetImporterWorkerManager.h>

namespace dooms
{
	D_NAMESPACE(dooms::assetImporter)
	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetManager : public IGameFlow, public ISingleton<AssetManager>
		{

			DOBJECT_CLASS_BODY(AssetManager, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(IGameFlow)

			friend class AssetFuture;

		private:

			AssetImporterWorkerManager mAssetImporterWorkerManager;

			const std::filesystem::path AssetFolderPath{ dooms::path::_GetAssetFolderDirectory() };
			
			std::array<dooms::asset::AssetContainer, dooms::asset::ENUM_ASSETTYPE_COUNT> mAssetConatiners
			{
				dooms::asset::AssetContainer(dooms::asset::eAssetType::AUDIO),
				dooms::asset::AssetContainer(dooms::asset::eAssetType::FONT),
				dooms::asset::AssetContainer(dooms::asset::eAssetType::TEXT),
				dooms::asset::AssetContainer(dooms::asset::eAssetType::TEXTURE),
				dooms::asset::AssetContainer(dooms::asset::eAssetType::THREE_D_MODEL),
				dooms::asset::AssetContainer(dooms::asset::eAssetType::SHADER)
			}
			;
			
			void LoadAssetManagerSetting();

			static bool CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry);


			void ImportEntireAsset();
			void DestroyAllAssets();

			dooms::asset::AssetContainer& GetAssetContainer(const dooms::asset::eAssetType eAssetType);

			void AddAssetToAssetContainer(dooms::asset::Asset* const asset);

			dooms::asset::Asset* _ImportAssetInstantly(std::filesystem::path& path, const dooms::asset::eAssetType assetType);
			dooms::assetImporter::AssetFuture _ImportAssetAsync(std::filesystem::path& path, const dooms::asset::eAssetType assetType);
			std::vector < dooms::assetImporter::AssetFuture> _ImportAssetAsync(std::vector<std::filesystem::path>& paths, const std::vector<dooms::asset::eAssetType>& assetTypes);
	

			dooms::asset::Asset* _GetAsset(const D_UUID& UUID, const dooms::asset::eAssetType assetType);
			dooms::asset::Asset* _GetAsset(const UINT32 index, const dooms::asset::eAssetType assetType);
			dooms::asset::Asset* _GetAsset(const std::string& filename, const dooms::asset::eAssetType assetType);

		public:

			AssetManager() = default;
			~AssetManager();

			

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			
			template<::dooms::asset::eAssetType AssetType>
			typename dooms::asset::AssetType<AssetType>::type* ImportAssetInstantly(std::filesystem::path path)
			{
				static_assert(std::is_base_of_v<dooms::asset::Asset, AssetType> == true);

				dooms::asset::Asset* const newAsset = _ImportAssetInstantly(path, AssetType);
				return reinterpret_cast<typename dooms::asset::AssetType<AssetType>::type*>(newAsset);
			}
			
			dooms::assetImporter::AssetFuture ImportAssetAsync(std::filesystem::path path, const ::dooms::asset::eAssetType assetType)
			{
				dooms::assetImporter::AssetFuture importedAssetFuture = _ImportAssetAsync(path, assetType);
				return importedAssetFuture;
			}

			

			template<::dooms::asset::eAssetType AssetType>
			typename dooms::asset::AssetType<AssetType>::type* GetAsset(const D_UUID& UUID)
			{
				dooms::asset::Asset* const asset = _GetAsset(UUID, AssetType);
				return reinterpret_cast<typename dooms::asset::AssetType<AssetType>::type*>(asset);
			}

			template<::dooms::asset::eAssetType AssetType>
			typename dooms::asset::AssetType<AssetType>::type* GetAsset(const UINT32 index)
			{
				dooms::asset::Asset* const asset = _GetAsset(index, AssetType);
				return reinterpret_cast<typename dooms::asset::AssetType<AssetType>::type*>(asset);
			}

			/// <summary>
			/// BE CAREFUL, This function is so slow
			/// </summary>
			/// <param name="filename"></param>
			/// <returns></returns>
			template<::dooms::asset::eAssetType AssetType>
			typename dooms::asset::AssetType<AssetType>::type* GetAsset(const std::string& filename)
			{
				dooms::asset::Asset* const asset = _GetAsset(filename, AssetType);
				return reinterpret_cast<typename dooms::asset::AssetType<AssetType>::type* const>(asset);
			}


		
			
		};


	}
}



