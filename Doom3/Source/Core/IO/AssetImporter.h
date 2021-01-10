#pragma once


#include <filesystem>
#include <type_traits>
#include <map>
#include <string>
#include <optional>
#include <utility>

#include <thread>
#include <mutex>


#include "../Core.h"

#include "../Asset/Asset.h"
#include "../Asset/AudioAsset.h"
#include "../Asset/FontAsset.h"
#include "../Asset/TextureAsset.h"
#include "../Asset/ThreeDModelAsset.h"

#include "../API/ASSIMP.h"
#include "../API/STB_IMAGE.h"







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
		static AssetTypeConditional_t<assetType>* ReadAssetFile(std::filesystem::path path)
		{
			static_assert(false, "Please put proper type");
			return {};
		}

		template<>
		static AudioAsset* ReadAssetFile<AssetType::AUDIO>(std::filesystem::path path)
		{
			return {};
		}

		template<>
		static  FontAsset* ReadAssetFile<AssetType::FONT>(std::filesystem::path path)
		{
			return {};
		}

		template<>
		static TextureAsset* ReadAssetFile<AssetType::TEXTURE>(std::filesystem::path path)
		{
			return {};
		}

		// TODO : Support MultiThreading Import
		// TODO : Only Big Size File should be imported on multiThread
		

		//static std::array<std::pair<Assimp::Importer>>ThreeDModelAssetImporterMutex;
	


		/// <summary>
		/// Create Nodes Recursively
		/// </summary>
		/// <param name="currentNode"></param>
		/// <param name="currentAssimpNode"></param>
		/// <param name="parentNode"></param>
		/// <param name="modelAsset"></param>
		/// <param name="assimpScene"></param>
		/// <returns></returns>
		static void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset* modelAsset, const aiScene* assimpScene)
		{
			currentNode->ThreeDModelNodeParent = parentNode;
			currentNode->ThreeDModelAsset = modelAsset;
			currentNode->Name = currentAssimpNode->mName.C_Str();
			currentNode->NumOfThreeDModelMeshes = currentAssimpNode->mNumMeshes;
			for (int meshIndex = 0; meshIndex < currentAssimpNode->mNumMeshes; meshIndex++)
			{
				currentNode->ThreeDModelMeshes[meshIndex] = modelAsset->ModelMeshes[currentAssimpNode->mMeshes[meshIndex]];
			}

			currentNode->NumOfThreeDModelNodeChildrens = currentAssimpNode->mNumChildren;
			currentNode->ThreeDModelNodeChildrens = new ThreeDModelNode * [currentAssimpNode->mNumChildren];
			for (int childrenIndex = 0; childrenIndex < currentAssimpNode->mNumChildren; childrenIndex++)
			{
				currentNode->ThreeDModelNodeChildrens[childrenIndex] = new ThreeDModelNode();
				SetThreeDModelNodesData(currentNode->ThreeDModelNodeChildrens[childrenIndex], currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
			}
		}

		//static std::optional<ThreeDModelAsset> Read3dModelFile
		/// <summary>
		/// Support MultiThreading because 3d model asset is big file size
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		template<>
		static ThreeDModelAsset* ReadAssetFile<AssetType::THREE_D_MODELL>(std::filesystem::path path)
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

			auto pathStr = "C:/Doom3FromScratch/Doom3/Assets/backpack.obj";
			// And have it read the given file with some example postprocessing
			// Usually - if speed is not the most important aspect for you - you'll
			// probably to request more postprocessing than we do in this example.
			const aiScene* scene = importer.ReadFile(pathStr,
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
			if (scene != nullptr && scene->mRootNode != nullptr)
			{

				ThreeDModelAsset* threeDModelAsset = new ThreeDModelAsset();

				//Copy Asset meshes
				threeDModelAsset->NumOfModelMeshed = scene->mNumMeshes;
				threeDModelAsset->ModelMeshes = new ThreeDModelMesh * [threeDModelAsset->NumOfModelMeshed];
				for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
				{
					auto mesh = scene->mMeshes[meshIndex];
					threeDModelAsset->ModelMeshes[meshIndex] = new ThreeDModelMesh();
					threeDModelAsset->ModelMeshes[meshIndex]->Name = mesh->mName.C_Str();

					threeDModelAsset->ModelMeshes[meshIndex]->NumOfVertices = mesh->mNumVertices;
					for (int verticeIndex = 0; verticeIndex < scene->mMeshes[meshIndex]->mNumVertices; verticeIndex++)
					{
						auto vertice = mesh->mVertices[verticeIndex];
						threeDModelAsset->ModelMeshes[meshIndex]->Vertices[verticeIndex] = new glm::vec3(vertice.x, vertice.y, vertice.z);

						threeDModelAsset->ModelMeshes[meshIndex]->NumOfTexCoords = 0;
						threeDModelAsset->ModelMeshes[meshIndex]->TexCoords = nullptr;
						if (mesh->HasTextureCoords(0))
						{//if has texCoord sets
							for (int texCoordIndex = 0; texCoordIndex < AI_MAX_NUMBER_OF_TEXTURECOORDS; texCoordIndex++)
							{
								if (mesh->mTextureCoords[verticeIndex] == NULL)
								{
									threeDModelAsset->ModelMeshes[meshIndex]->NumOfTexCoords = texCoordIndex;
									break;
								}
							}

							threeDModelAsset->ModelMeshes[meshIndex]->TexCoords = new glm::vec3 * [threeDModelAsset->ModelMeshes[meshIndex]->NumOfTexCoords];
							for (int texCoordIndex = 0; texCoordIndex < threeDModelAsset->ModelMeshes[meshIndex]->NumOfTexCoords; texCoordIndex++)
							{
								auto texCoord = mesh->mTextureCoords[verticeIndex][texCoordIndex];
								threeDModelAsset->ModelMeshes[meshIndex]->TexCoords[texCoordIndex] = new glm::vec3(texCoord.x, texCoord.y, texCoord.z);
							}
						}
					}

					threeDModelAsset->ModelMeshes[meshIndex]->Tangents = mesh->HasTangentsAndBitangents() ? new glm::vec3(mesh->mTangents->x, mesh->mTangents->y, mesh->mTangents->z) : nullptr;
					threeDModelAsset->ModelMeshes[meshIndex]->BiTangents = mesh->HasTangentsAndBitangents() ? new glm::vec3(mesh->mBitangents->x, mesh->mBitangents->y, mesh->mBitangents->z) : nullptr;
					threeDModelAsset->ModelMeshes[meshIndex]->Normals = mesh->HasNormals() ? new glm::vec3(mesh->mNormals->x, mesh->mNormals->y, mesh->mNormals->z) : nullptr;
				}

				//scene->mRootNode
				SetThreeDModelNodesData(&threeDModelAsset->rootNode, scene->mRootNode, nullptr, threeDModelAsset, scene);
				return threeDModelAsset;

			}
			else
			{
				Debug::Log({ path.string(), " : 3D Model Asset has no scene" });
				return nullptr;
			}

			// We're done. Everything will be cleaned up by the importer destructor
		}
	public:
		template <AssetType assetType>
		static bool ImportAsset(std::filesystem::path path, AssetTypeConditional_t<assetType>** asset)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						AssetTypeConditional_t<assetType>* importedAsset = ReadAssetFile<assetType>(path);
						if (importedAsset != nullptr)
						{
							*asset = importedAsset;
							return true;
						}
						else
						{
							Doom::Debug::Log("Fail To Find File Format");
							return false;
						}
					}
				}
				catch (std::out_of_range& e)
				{
					Doom::Debug::Log({ "Can't Find proper extension : ", extension });
				}
			}
			Doom::Debug::Log("Fail To Find File Format");
			return false;
		}
	};
}


