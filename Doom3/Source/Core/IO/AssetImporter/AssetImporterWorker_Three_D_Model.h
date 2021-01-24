#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../API/ASSIMP.h"
#include "../../Asset/ThreeDModelAsset.h"



#include <thread>

namespace Doom
{
	namespace AssetImporter
	{
		template <> struct api_importer_type<Asset::AssetType::THREE_D_MODEL> { using type = typename Assimp::Importer; };

		template<>
		void AssetApiImporter<Asset::AssetType::THREE_D_MODEL>::InitApiImporter(api_importer_type_t<Asset::AssetType::THREE_D_MODEL>& apiImporter)
		{
			apiImporter.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
				aiComponent_COLORS |
				aiComponent_BONEWEIGHTS |
				aiComponent_ANIMATIONS |
				aiComponent_LIGHTS |
				aiComponent_CAMERAS |
				aiComponent_MATERIALS |
				aiComponent_TEXTURES
			);// set removed components flags
		}


		/// Create Nodes Recursively
		/// </summary>
		/// <param name="currentNode"></param>
		/// <param name="currentAssimpNode"></param>
		/// <param name="parentNode"></param>
		/// <param name="modelAsset"></param>
		/// <param name="assimpScene"></param>
		/// <returns></returns>
		inline void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene)
		{
			currentNode->ThreeDModelNodeParent = parentNode;
			currentNode->ThreeDModelAsset = &modelAsset;
			currentNode->Name = currentAssimpNode->mName.C_Str();
			currentNode->NumOfThreeDModelMeshes = currentAssimpNode->mNumMeshes;

			currentNode->ThreeDModelMeshes = new ThreeDModelMesh * [currentAssimpNode->mNumMeshes];
			for (unsigned int meshIndex = 0; meshIndex < currentAssimpNode->mNumMeshes; meshIndex++)
			{
				currentNode->ThreeDModelMeshes[meshIndex] = modelAsset.ModelMeshes[currentAssimpNode->mMeshes[meshIndex]];
			}

			currentNode->NumOfThreeDModelNodeChildrens = currentAssimpNode->mNumChildren;
			currentNode->ThreeDModelNodeChildrens = new ThreeDModelNode * [currentAssimpNode->mNumChildren];
			for (unsigned int childrenIndex = 0; childrenIndex < currentAssimpNode->mNumChildren; childrenIndex++)
			{
				currentNode->ThreeDModelNodeChildrens[childrenIndex] = new ThreeDModelNode();
				Doom::AssetImporter::SetThreeDModelNodesData(currentNode->ThreeDModelNodeChildrens[childrenIndex], currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
			}
		}


#ifdef DEBUG_MODE
		class AssimpLogStream : public Assimp::LogStream {
		public:
			// Write womethink using your own functionality
			inline void write(const char* message)
			{
				DEBUG_LOG({ "Assimp Debugger : ", message });
			}


		};
#endif


		template<>
		inline std::optional<Asset::asset_type_t<Asset::AssetType::THREE_D_MODEL>> ReadAssetFile<Asset::AssetType::THREE_D_MODEL>(std::filesystem::path path)
		{
			std::stringstream stream;
			stream  << std::this_thread::get_id();

			DEBUG_LOG(stream.str());

#ifdef DEBUG_MODE
			static bool IsAssimpDebuggerInitialized;

			if (IsAssimpDebuggerInitialized == false)
			{
				Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
				// Select the kinds of messages you want to receive on this log stream
				const unsigned int severity = Assimp::Logger::Err | Assimp::Logger::Warn;

				// Attaching it to the default logger
				Assimp::DefaultLogger::get()->attachStream(new AssimpLogStream, severity);

				IsAssimpDebuggerInitialized = true;
			}
#endif
			AssetApiImporter<Asset::AssetType::THREE_D_MODEL> apiImporter = AssetApiImporter<Asset::AssetType::THREE_D_MODEL>::GetApiImporter();

			/* Do this AssetImporter Constructor
			apiImporter->SetPropertyInteger("AI_CONFIG_PP_RVC_FLAGS",
				aiComponent_COLORS |
				aiComponent_BONEWEIGHTS |
				aiComponent_ANIMATIONS |
				aiComponent_LIGHTS |
				aiComponent_CAMERAS |
				aiComponent_MATERIALS |
				aiComponent_TEXTURES
			);// set removed components flags
			*/

			// And have it read the given file with some example postprocessing
			// Usually - if speed is not the most important aspect for you - you'll
			// probably to request more postprocessing than we do in this example.
			const aiScene* scene = apiImporter->ReadFile(path.string(),
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

			Asset::asset_type_t<Asset::AssetType::THREE_D_MODEL> asset{};

			//scene->mMeshes[0]->
			// If the import failed, report it
			if (scene != nullptr && scene->mRootNode != nullptr)
			{


				//Copy Asset meshes
				asset.NumOfModelMeshed = scene->mNumMeshes;
				asset.ModelMeshes = new ThreeDModelMesh * [asset.NumOfModelMeshed];
				for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
				{
					auto mesh = scene->mMeshes[meshIndex];
					asset.ModelMeshes[meshIndex] = new ThreeDModelMesh();
					asset.ModelMeshes[meshIndex]->Name = mesh->mName.C_Str();

					asset.ModelMeshes[meshIndex]->NumOfVertices = mesh->mNumVertices;
					asset.ModelMeshes[meshIndex]->Vertices = new Vector3 * [mesh->mNumVertices];

					for (unsigned int verticeIndex = 0; verticeIndex < scene->mMeshes[meshIndex]->mNumVertices; verticeIndex++)
					{
						auto vertice = mesh->mVertices[verticeIndex];
						asset.ModelMeshes[meshIndex]->Vertices[verticeIndex] = new Vector3(vertice.x, vertice.y, vertice.z);

						asset.ModelMeshes[meshIndex]->NumOfTexCoords = 0;
						asset.ModelMeshes[meshIndex]->TexCoords = nullptr;
						if (mesh->HasTextureCoords(0))
						{//if has texCoord sets
							for (unsigned int texCoordIndex = 0; texCoordIndex < AI_MAX_NUMBER_OF_TEXTURECOORDS; texCoordIndex++)
							{
								if (mesh->mTextureCoords[texCoordIndex] == NULL)
								{
									asset.ModelMeshes[meshIndex]->NumOfTexCoords = texCoordIndex;
									break;
								}
							}

							asset.ModelMeshes[meshIndex]->TexCoords = new Vector3 * [asset.ModelMeshes[meshIndex]->NumOfTexCoords];
							for (unsigned int texCoordIndex = 0; texCoordIndex < asset.ModelMeshes[meshIndex]->NumOfTexCoords; texCoordIndex++)
							{
								auto& texCoord = mesh->mTextureCoords[texCoordIndex][verticeIndex];
								asset.ModelMeshes[meshIndex]->TexCoords[texCoordIndex] = new Vector3(texCoord.x, texCoord.y, texCoord.z);
							}
						}
					}

					asset.ModelMeshes[meshIndex]->Tangents = mesh->HasTangentsAndBitangents() ? new Vector3(mesh->mTangents->x, mesh->mTangents->y, mesh->mTangents->z) : nullptr;
					asset.ModelMeshes[meshIndex]->BiTangents = mesh->HasTangentsAndBitangents() ? new Vector3(mesh->mBitangents->x, mesh->mBitangents->y, mesh->mBitangents->z) : nullptr;
					asset.ModelMeshes[meshIndex]->Normals = mesh->HasNormals() ? new Vector3(mesh->mNormals->x, mesh->mNormals->y, mesh->mNormals->z) : nullptr;
				}

				//scene->mRootNode
				asset.rootNode.ThreeDModelNodeParent = nullptr;
				SetThreeDModelNodesData(&(asset.rootNode), scene->mRootNode, nullptr, asset, scene);
				apiImporter->FreeScene();
				apiImporter.Release();
				return asset;
			}
			else
			{
				DEBUG_LOG({ path.string(), " : 3D Model Asset has no scene" });
				return {};
			}

			// We're done. Everything will be cleaned up by the importer destructor
		}
		

	}

	

}