#pragma once
#include "Base_Asset.h"

namespace doom
{
	class TextureAsset : public Asset
	{
		template<Asset::eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;
	};

	template <> struct Asset::asset_type<Asset::eAssetType::TEXTURE> { using type = typename TextureAsset; };
}


