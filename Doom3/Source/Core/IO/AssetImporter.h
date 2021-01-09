#pragma once

// TODO : use std::filesystem::path 
// TODO : According To File format (filesystem::path::extension), use proper 3rd library ( assimp, sdl )...

#include <filesystem>
#include <type_traits>
#include <map>
#include <string>
#include <optional>

#include "../Core.h"

#include "../Asset/Asset.h"
#include "../Asset/AudioAsset.h"
#include "../Asset/FontAsset.h"
#include "../Asset/TextureAsset.h"
#include "../Asset/ThreeDModelAsset.h"

#include "../API/ASSIMP.h"
#include "../API/STB_IMAGE.h"

struct aiScene;





namespace Doom
{
	class AssetImporter
	{
	private :
		static const std::map<std::string, Doom::AssetType> AssetExtension;

		template <AssetType assetType>
		struct AssetTypeConditional;


		template <> struct AssetTypeConditional<Doom::AssetType::AUDIO> { using type = AudioAsset; };
		template <> struct AssetTypeConditional<Doom::AssetType::FONT> { using type = FontAsset; };
		template <> struct AssetTypeConditional<Doom::AssetType::TEXTURE> { using type = TextureAsset; };
		template <> struct AssetTypeConditional<Doom::AssetType::THREE_D_MODELL> { using type = ThreeDModelAsset; };

		template <AssetType assetType>
		using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

		template <AssetType assetType>
		static AssetTypeConditional_t<assetType> ReadAssetFile(std::filesystem::path path)
		{
			static_assert(false, "Please put proper type");
			return {};
		}

		template<>
		static AudioAsset ReadAssetFile<AssetType::AUDIO>(std::filesystem::path path)
		{
			return {};
		}

		template<>
		static FontAsset ReadAssetFile<AssetType::FONT>(std::filesystem::path path)
		{
			return {};
		}

		template<>
		static TextureAsset ReadAssetFile<AssetType::TEXTURE>(std::filesystem::path path)
		{
			return {};
		}

		template<>
		static ThreeDModelAsset ReadAssetFile<AssetType::THREE_D_MODELL>(std::filesystem::path path)
		{
			Assimp::Importer importer;
			importer.SetPropertyInteger("AI_CONFIG_PP_RVC_FLAGS",
				aiComponent_COLORS |
				aiComponent_BONEWEIGHTS |
				aiComponent_ANIMATIONS |
				aiComponent_LIGHTS |
				aiComponent_CAMERAS |
				aiComponent_MATERIALS |
				aiComponent_TEXTURES
			);// set removed components flags


			// And have it read the given file with some example postprocessing
			// Usually - if speed is not the most important aspect for you - you'll
			// probably to request more postprocessing than we do in this example.
			const aiScene* scene = importer.ReadFile(path.string(),
				aiProcess_RemoveComponent |
				aiProcess_SplitLargeMeshes |
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_GenSmoothNormals |
				aiProcess_CalcTangentSpace |
				aiProcess_TransformUVCoords |
				aiProcess_SortByPType |
				aiProcess_ImproveCacheLocality 
			);
			//scene->mMeshes[0]->
			// If the import failed, report it
			if (!scene) {
				if (scene->mRootNode)
				{
				}
			}



			// Now we can access the file's contents.
			//DoTheSceneProcessing(scene);

			// We're done. Everything will be cleaned up by the importer destructor
			return {};
		}
	public:
		template <AssetType assetType>
		static AssetTypeConditional_t<assetType> ImportAsset(std::filesystem::path path)
		{
			
				if (path.has_extension())
				{
					auto extension = path.extension().string();
					try
					{
						if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
						{
							return ReadAssetFile<assetType>(path);
						}
					}
					catch (std::out_of_range& e)
					{
						Doom::Debug::Log({ "Cant Find proper extension : ", extension });
					}
				}
				else
				{
					Doom::Debug::Log("Fail To Find File Format");
				}

			return {};
		}
		
	};
}


