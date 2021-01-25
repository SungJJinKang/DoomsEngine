#pragma once

#include <string>
#include <filesystem>
#include "../Core.h"
#include "../API/UUID.h"

namespace doom
{

	class AudioAsset;
	class FontAsset;
	class TextAsset;
	class TextureAsset;
	class ThreeDModelAsset;

	class Asset
	{
	public:
		
		enum eAssetType : unsigned int
		{
			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODEL,
			SHADER,
		};

		static constexpr inline eAssetType FirstElementOfAssetType = eAssetType::AUDIO;
		static constexpr inline eAssetType LastElementOfAssetType = eAssetType::SHADER;
		static constexpr inline unsigned int GetAssetTypeCount() {
			return static_cast<unsigned int>(LastElementOfAssetType) + 1u;
		}

		template <Asset::eAssetType assetType>
		struct asset_type
		{
			using type = void;
		};

		template <Asset::eAssetType assetType>
		using asset_type_t = typename asset_type<assetType>::type;

		D_UUID mUUID;
		std::string mAssetName;
		std::filesystem::path mAssetPath;

		inline void SetBaseMetaData(const std::filesystem::path& path)
		{
			mAssetName = path.has_filename() ? path.filename().string() : "";
			mAssetPath = path.string();
		}

		bool IsContainingData;
		Asset(bool isConatiningData) : IsContainingData{ isConatiningData }
		{
			if (isConatiningData == true)
			{
				this->mUUID = GenerateUUID();
			}
		}

		Asset() : mUUID{ GenerateUUID() }, IsContainingData{ true }
		{

		}

		virtual inline void OnImportEndOnMainThread(){}
		virtual inline void OnImportEndOnSubThread() {}
	};
}


