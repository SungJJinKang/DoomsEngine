#pragma once

#include "Base_Asset.h"
namespace doom
{

	class FontAsset : public Asset
	{
		template<Asset::eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;
	};
	template <> struct Asset::asset_type<Asset::eAssetType::FONT> { using type = typename FontAsset; };
}