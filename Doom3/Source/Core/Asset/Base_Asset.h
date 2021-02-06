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
		
		enum class eAssetType : unsigned int
		{
			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODEL,
			SHADER,
		};
		static std::string GetAssetTypeString(const eAssetType& assetType);

		template <Asset::eAssetType assetType>
		struct asset_type
		{
			using type = void;
		};

		template <Asset::eAssetType assetType>
		using asset_type_t = typename asset_type<assetType>::type;

		static constexpr inline eAssetType FirstElementOfAssetType = eAssetType::AUDIO;
		static constexpr inline eAssetType LastElementOfAssetType = eAssetType::SHADER;
		static constexpr inline unsigned int GetAssetTypeCount() {
			return static_cast<unsigned int>(LastElementOfAssetType) + 1u;
		}

		D_UUID mUUID;
		std::string mAssetFileName;
		std::filesystem::path mAssetPath;

		void SetBaseMetaData(const std::filesystem::path& path);

		bool bIsContainingData;

		Asset();
		Asset(bool isConatiningData);

		Asset(const Asset&) = default;
		Asset(Asset&&) noexcept = default;
		Asset& operator=(const Asset&) = default;
		Asset& operator=(Asset&&) = default;

		/// <summary>
		/// post processing after asset imported.
		/// this function should be called at main thread
		/// </summary>
		virtual void OnEndImportInMainThread(){}
		virtual void OnEndImportInSubThread() {}
	};

	

}


