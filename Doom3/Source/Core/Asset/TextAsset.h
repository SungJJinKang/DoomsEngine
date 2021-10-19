#pragma once

#include "Asset.h"
#include <string>

namespace doom
{
	namespace assetimporter
	{
		class AssetImporterWorker_Text;
	}

	namespace asset
	{
		class DOOM_API TextAsset : public Asset
		{
			DOBJECT_CLASS_BODY(TextAsset, doom::eDOBJECT_ClassFlags::NonCopyable)

			friend class ::doom::assetimporter::AssetImporterWorker_Text;
			
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


			virtual doom::asset::eAssetType GetEAssetType() const final;
		};
	}
}