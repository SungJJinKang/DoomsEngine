#pragma once

#include <Asset/eAssetType.h>

namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker;
		class AssetImporterWorker_Audio;
		class AssetImporterWorker_Font;
		class AssetImporterWorker_Shader;
		class AssetImporterWorker_Text;
		class AssetImporterWorker_Texture;
		class AssetImporterWorker_THREE_D_MODEL;

		template <asset::eAssetType assetType>
		struct AssetImporterWorkerType
		{
			using type = void;
		};

		template<>
		struct AssetImporterWorkerType<asset::eAssetType::AUDIO>
		{
			using type = AssetImporterWorker_Audio;
		};

		template<>
		struct AssetImporterWorkerType<asset::eAssetType::FONT>
		{
			using type = AssetImporterWorker_Font;
		};

		template<>
		struct AssetImporterWorkerType<asset::eAssetType::SHADER>
		{
			using type = AssetImporterWorker_Shader;
		};

		template<>
		struct AssetImporterWorkerType<asset::eAssetType::TEXTURE>
		{
			using type = AssetImporterWorker_Texture;
		};

		template<>
		struct AssetImporterWorkerType<asset::eAssetType::THREE_D_MODEL>
		{
			using type = AssetImporterWorker_THREE_D_MODEL;
		};

		template<>
		struct AssetImporterWorkerType<asset::eAssetType::TEXT>
		{
			using type = AssetImporterWorker_Text;
		};
	}
}
