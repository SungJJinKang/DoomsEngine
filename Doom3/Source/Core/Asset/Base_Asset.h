#pragma once

#include <string>
#include <filesystem>
#include <utility>
#include <memory>

#include "../Core.h"
#include "../API/UUID.h"

namespace doom
{
	

	class AudioAsset;
	class FontAsset;
	class TextAsset;
	class TextureAsset;
	class ThreeDModelAsset;

	enum class eAssetType
	{
		AUDIO = 0,
		FONT,
		TEXT,
		TEXTURE,
		THREE_D_MODEL,
		SHADER,
	};


	namespace assetimporter
	{
		class AssetManager;
		class Assetimporter;
		template <eAssetType assetType>
		class AssetImporterWorker;

		template<eAssetType assetType>
		class AssetContainer;

		template<eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor;

	
	}

	class Asset
	{
		friend class assetimporter::AssetManager;
		friend class assetimporter::Assetimporter;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

		template<eAssetType loopVariable>
		friend class assetimporter::AssetContainer;

	private:

		D_UUID mUUID;
		std::string mAssetFileName;
		std::filesystem::path mAssetPath;
		unsigned long long mAssetFileSize;

		bool bmIsDataLoaded;

		void SetBaseMetaData(const std::filesystem::path& path);

	protected:

	

		/// <summary>
		/// post processing after asset imported.
		/// this function should be called at main thread
		/// </summary>
		virtual void OnEndImportInMainThread() {}
		virtual void OnEndImportInSubThread() {}

	public:
		
		Asset();
		Asset(bool isConatiningData);
		Asset(const Asset&) = delete;
		Asset(Asset&&) noexcept = default;
		Asset& operator=(const Asset&) = delete;
		Asset& operator=(Asset&&) noexcept = default;
		virtual ~Asset() {}

		D_UUID GetUUID();
		D_UUID GetUUID() const;
		std::string GetAssetFileName();
		const std::string& GetAssetFileName() const;
		unsigned long long GetAssetFileSize() const;
		std::filesystem::path GetAssetPath();
		bool GetIsDataLoaded();
		
		static std::string GetAssetTypeString(const eAssetType& assetType);

		template <eAssetType assetType>
		struct asset_type
		{
			using type = void;
		};

		template <eAssetType assetType>
		using asset_type_t = typename asset_type<assetType>::type;

		static constexpr inline eAssetType FirstElementOfAssetType = eAssetType::AUDIO;
		static constexpr inline eAssetType LastElementOfAssetType = eAssetType::SHADER;
		static constexpr inline unsigned int GetAssetTypeCount() {
			return static_cast<unsigned int>(LastElementOfAssetType) + 1u;
		}

	

		

		
	};


	
}


