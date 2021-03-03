#pragma once

#include "../Core.h"
#include "../Asset/Asset.h"
#include "../IO/AssetImporter/AssetImporter.h"
#include "../IGameFlow.h"

#include "../../API/UUID.h"
#include "../../ResourceManagement/JobSystem.h"
#include <ZeroResetMoveContainer.h>


namespace doom
{
	namespace assetimporter
	{
		template<eAssetType assetType>
		class ImportedAssetPort;

		template<eAssetType assetType>
		using imported_asset_future_t = typename std::future<std::optional<Asset::asset_type_t<assetType>>>;

		template<eAssetType assetType>
		class AssetContainer
		{
			friend class ImportedAssetPort<assetType>;

		public:
			using asset_type = typename Asset::asset_type_t<assetType>;

		private: 
			ZeroResetMoveContainer<bool> mbIsImported;
			ZeroResetMoveContainer<bool> mbIsFutureWaiting;

			/// <summary>
			/// Completly Imported Asset
			/// </summary>
			typename asset_type mImportedAsset;
			/// <summary>
			/// 
			/// </summary>
			typename imported_asset_future_t<assetType> mWaitingFuture;
			D_UUID mReservedUUID;

			void SetAsset(typename asset_type&& importedAsset)
			{
				D_ASSERT(this->mbIsImported == false);

				this->mbIsImported = true;
				this->mbIsFutureWaiting = false;
				this->mImportedAsset = std::move(importedAsset);
			}

			
		public:
			
			AssetContainer()
				:mbIsImported{ false }, mbIsFutureWaiting{ false }, mImportedAsset{}, mWaitingFuture{}, mReservedUUID{}
			{
				CHECK_IS_EXECUTED_ON_MAIN_THREAD;
			}

			AssetContainer(typename imported_asset_future_t<assetType>&& importedAssetFuture, const D_UUID& reservedUUID)
				:mbIsImported{ false }, mbIsFutureWaiting{ true }, mImportedAsset{}, mReservedUUID{ reservedUUID }, mWaitingFuture{ std::move(importedAssetFuture) }
			{
				CHECK_IS_EXECUTED_ON_MAIN_THREAD;
			}

			AssetContainer(typename asset_type&& importedAsset)
				:mbIsImported{ true }, mbIsFutureWaiting{ false }, mImportedAsset{ std::move(importedAsset) }, mWaitingFuture{}
			{
				CHECK_IS_EXECUTED_ON_MAIN_THREAD;
			}

			

			AssetContainer(const AssetContainer&) = delete;
			AssetContainer(AssetContainer&&) noexcept = default;
			AssetContainer& operator=(const AssetContainer&) = delete;
			AssetContainer& operator=(AssetContainer&&) noexcept = default;
			~AssetContainer() = default;

			typename asset_type* GetImportedAsset()
			{
				D_ASSERT(this->mbIsImported == true);
				return &(this->mImportedAsset);
			}
			typename asset_type* GetImportedAsset() const
			{
				D_ASSERT(this->mbIsImported == true);
				return &(this->mImportedAsset);
			}

			typename asset_type* operator->()
			{
				D_ASSERT(this->mbIsImported == true);
				return &(this->mImportedAsset);
			}
			typename asset_type* operator->() const
			{
				D_ASSERT(this->mbIsImported == true);
				return &(this->mImportedAsset);
			}
			
			typename asset_type* GetFuture()
			{
				CHECK_IS_EXECUTED_ON_MAIN_THREAD;
				D_ASSERT(this->mbIsFutureWaiting == true || this->mbIsImported == true);

				if (this->mbIsFutureWaiting == false && this->mbIsImported == true)
				{
					return GetImportedAsset();
				}

				auto completelyImprotedAsset = mWaitingFuture.get();
				if (completelyImprotedAsset.has_value())
				{
					this->SetAsset(std::move(completelyImprotedAsset.value()));
					this->mImportedAsset.mUUID = mReservedUUID;
					this->mbIsFutureWaiting = false;
					return GetImportedAsset();
				}
				else
				{
					D_DEBUG_LOG("Fail To Get Future Asset", eLogType::D_ERROR);
					nullptr;
				}
			}
			
		};

	

	}
}

