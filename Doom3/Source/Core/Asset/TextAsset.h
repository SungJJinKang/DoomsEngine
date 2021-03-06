#pragma once

#include "Base_Asset.h"
#include <string>

namespace doom
{
	namespace asset
	{
		class TextAsset : public Asset
		{
			friend class ::doom::assetimporter::ImportedAssetPort<eAssetType::TEXT>;

			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;

		private:

			std::string mText;

		protected:



		public:

			const std::string& GetText();

			void SetText(const std::string& str);
			TextAsset() = default;
			TextAsset(const TextAsset&) = delete;
			TextAsset(TextAsset&&) noexcept = default;
			TextAsset& operator=(const TextAsset&) = delete;
			TextAsset& operator=(TextAsset&&) noexcept = default;
			virtual ~TextAsset() = default;
		};
		template <> struct Asset::asset_type<eAssetType::TEXT> { using type = typename TextAsset; };
	}
}