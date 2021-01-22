#pragma once

#include <string>
#include <filesystem>
#include "../Core.h"
#include "../API/UUID.h"

namespace Doom
{

	class AudioAsset;
	class FontAsset;
	class TextAsset;
	class TextureAsset;
	class ThreeDModelAsset;

	class Asset
	{
	public:
		
		enum AssetType : unsigned int
		{
			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODEL,
			SHADER,
		};

		static constexpr inline AssetType FirstElementOfAssetType = AssetType::AUDIO;
		static constexpr inline AssetType LastElementOfAssetType = AssetType::SHADER;
		static constexpr inline unsigned int GetAssetTypeCount() {
			return static_cast<unsigned int>(LastElementOfAssetType) + 1u;
		}

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

		virtual inline void OnImportEndOnMainThread(){}
		virtual inline void OnImportEndOnSubThread() {}
	};
}


