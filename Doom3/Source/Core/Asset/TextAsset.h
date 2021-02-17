#pragma once

#include "Base_Asset.h"
#include <string>

namespace doom
{

	class TextAsset : public Asset
	{
		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

	private:

		std::string mText;

	protected:

		

	public:
	
		const std::string& GetText();

		TextAsset(const std::string& str);
		TextAsset() = default;
		TextAsset(const TextAsset&) = delete;
		TextAsset(TextAsset&&) noexcept = default;
		TextAsset& operator=(const TextAsset&) = delete;
		TextAsset& operator=(TextAsset&&) noexcept = default;
		virtual ~TextAsset() = default;
	};
	template <> struct Asset::asset_type<eAssetType::TEXT> { using type = typename TextAsset; };
}