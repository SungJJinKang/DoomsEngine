#pragma once

#include "Asset.h"
#include <string>

#include "TextAsset.reflection.h."
namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker_Text;
	}

	namespace asset
	{
		class DOOM_API D_CLASS TextAsset : public Asset
		{
			GENERATE_BODY()
			

			friend class ::dooms::assetImporter::AssetImporterWorker_Text;
			
		private:

			D_PROPERTY()
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
			virtual void OnSetPendingKill() override;


			virtual dooms::asset::eAssetType GetEAssetType() const final;
		};
	}
}