#pragma once

#include <string>
#include <filesystem>
#include "../API/UUID.h"

namespace Doom
{



	struct Asset
	{
		enum AssetType : short int
		{

			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODELL,
			NONE, // TRICK FOR COUNTING ENUM ELEMENT COUNT, THIS ELEMENT SHOULD BE LAST ELEMENT OF THIS ENUM
		};

		static constexpr inline short int AssetTypeCount = AssetType::NONE + 1;

		template <AssetType assetType>
		struct AssetTypeConditional;
		template <AssetType assetType>
		using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

		/// <summary>
		/// https://github.com/r-lyeh-archived/sole
		/// </summary>
		UUID uuid;
		std::string AssetName;
		std::filesystem::path AssetPath;

		void SetBaseMetaData(const std::filesystem::path& path);

		Asset() : uuid{ GenerateUUID() }
		{

		}
	};
}


