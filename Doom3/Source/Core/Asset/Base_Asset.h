#pragma once

#include <string>
#include <filesystem>
#include "../API/UUID.h"

namespace Doom
{

	struct AudioAsset;
	struct FontAsset;
	struct TextAsset;
	struct TextureAsset;
	struct ThreeDModelAsset;

	struct Asset
	{
		static constexpr inline short int AssetTypeCount = 5;
		enum AssetType : short int
		{
			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODELL,
		};

		

		template <Asset::AssetType assetType>
		struct AssetTypeConditional;

		template <AssetType assetType>
		using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

		D_UUID uuid;
		std::string AssetName;
		std::filesystem::path AssetPath;

		inline void SetBaseMetaData(const std::filesystem::path& path)
		{
			AssetName = path.has_filename() ? path.filename().string() : "";
			AssetPath = path.string();
		}

		bool IsContainingData;
		Asset(bool isConatiningData) : IsContainingData{ isConatiningData }
		{
			if (isConatiningData == true)
			{
				this->uuid = GenerateUUID();
			}
		}

		Asset() : uuid{ GenerateUUID() }, IsContainingData{ true }
		{

		}
	};
}


