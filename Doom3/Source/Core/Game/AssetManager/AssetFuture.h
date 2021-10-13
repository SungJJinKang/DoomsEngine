#pragma once

#include <future>
#include <Asset/AssetsForwardDeclaration.h>

namespace doom
{
	namespace assetimporter
	{
		class AssetFuture
		{
		private:
			doom::asset::Asset* mAsset;
			std::future<bool> mFuture;
			bool isWaitingEnd = false;

		public:

			AssetFuture(doom::asset::Asset* const asset, std::future<bool>&& future) noexcept;
			AssetFuture(const AssetFuture&) = delete;
			AssetFuture(AssetFuture&&) noexcept = default;
			AssetFuture& operator=(const AssetFuture&) = delete;
			AssetFuture& operator=(AssetFuture&&) noexcept = default;
			~AssetFuture();

			void WaitAsset();
			doom::asset::Asset* GetAsset();

			template <doom::asset::eAssetType AssetType>
			typename doom::asset::AssetType<AssetType>::type* GetAsset()
			{
				static_assert(std::is_base_of_v<doom::asset::Asset, AssetType> == true);
				
				return static_cast<typename doom::asset::AssetType<AssetType>::type*>(GetAsset());
			}
			
		};
	}
}