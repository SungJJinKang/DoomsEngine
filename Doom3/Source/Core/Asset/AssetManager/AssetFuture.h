#pragma once

#include <future>
#include <Core.h>
#include <Asset/AssetsForwardDeclaration.h>

#include "AssetFuture.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetFuture : public DObject
		{
			GENERATE_BODY()

		private:
			dooms::asset::Asset* mAsset;
			std::future<bool> mFuture;
			bool isWaitingEnd = false;

		public:

			AssetFuture(dooms::asset::Asset* const asset, std::future<bool>&& future) noexcept;
			AssetFuture(const AssetFuture&) = delete;
			AssetFuture(AssetFuture&&) noexcept = default;
			AssetFuture& operator=(const AssetFuture&) = delete;
			AssetFuture& operator=(AssetFuture&&) noexcept = default;
			~AssetFuture();

			void WaitAsset();
			dooms::asset::Asset* GetAsset();

			template <dooms::asset::eAssetType AssetType>
			typename dooms::asset::AssetType<AssetType>::type* GetAsset()
			{
				static_assert(std::is_base_of_v<dooms::asset::Asset, AssetType> == true);
				
				return static_cast<typename dooms::asset::AssetType<AssetType>::type*>(GetAsset());
			}
			
		};
	}
}