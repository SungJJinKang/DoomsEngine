#pragma once

#include "eAssetType.h"

namespace doom
{
	namespace asset
	{
		class Asset;
		class AudioAsset;
		class FontAsset;
		class ShaderAsset;
		class TextAsset;
		class TextureAsset;
		class ThreeDModelAsset;

		template <eAssetType assetType>
		struct AssetType
		{
			using type = void;
		};

		template<>
		struct AssetType<eAssetType::AUDIO>
		{
			using type = AudioAsset;
		};

		template<>
		struct AssetType<eAssetType::FONT>
		{
			using type = FontAsset;
		};

		template<>
		struct AssetType<eAssetType::SHADER>
		{
			using type = ShaderAsset;
		};

		template<>
		struct AssetType<eAssetType::TEXTURE>
		{
			using type = TextureAsset;
		};

		template<>
		struct AssetType<eAssetType::THREE_D_MODEL>
		{
			using type = ThreeDModelAsset;
		};

		template<>
		struct AssetType<eAssetType::TEXT>
		{
			using type = TextAsset;
		};

	}
}
