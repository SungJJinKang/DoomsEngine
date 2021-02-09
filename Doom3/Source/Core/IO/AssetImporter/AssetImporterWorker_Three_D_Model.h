#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../API/ASSIMP.h"
#include "../../Asset/ThreeDModelAsset.h"




namespace doom
{
	namespace assetimporter
	{
		template <> struct api_importer_type<Asset::eAssetType::THREE_D_MODEL> { using type = typename Assimp::Importer; };
		template<>
		void AssetApiImporter<Asset::eAssetType::THREE_D_MODEL>::InitApiImporter(api_importer_type_t<Asset::eAssetType::THREE_D_MODEL>& apiImporter)
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


		template <>
		class AssetImporterWorker<Asset::eAssetType::THREE_D_MODEL>
		{
			friend class Assetimporter;
#ifdef DEBUG_MODE
			class AssimpLogStream : public Assimp::LogStream {
			public:
				// Write womethink using your own functionality
				inline void write(const char* message)
				{
					D_DEBUG_LOG({ "Assimp Debugger : ", message });
				}


			};
#endif
		private:
			static std::optional<Asset::asset_type_t<Asset::eAssetType::THREE_D_MODEL>> ImportSpecificAsset(const std::filesystem::path& path)
			{
				std::stringstream stream;
				stream << std::this_thread::get_id();

				D_DEBUG_LOG(stream.str());


#ifdef DEBUG_MODE
				static bool IsAssimpDebuggerInitialized;

				if (IsAssimpDebuggerInitialized == false)
				{
					Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
					// Select the kinds of messages you want to receive on this log stream
					const unsigned int severity = Assimp::Logger::Err;// | Assimp::Logger::Warn;

					// Attaching it to the default logger
					Assimp::DefaultLogger::get()->attachStream(new AssimpLogStream, severity);

					IsAssimpDebuggerInitialized = true;
				}
#endif

				AssetApiImporter<Asset::eAssetType::THREE_D_MODEL> apiImporterContainer = AssetApiImporter<Asset::eAssetType::THREE_D_MODEL>::GetApiImporter();
				auto apiImporter = apiImporterContainer.Get();

				// And have it read the given file with some example postprocessing
				// Usually - if speed is not the most important aspect for you - you'll
				// probably to request more postprocessing than we do in this example.
				const aiScene* scene = apiImporter->ReadFile(path.string(),
					aiProcess_RemoveComponent |
					//aiProcess_SplitLargeMeshes |
					aiProcess_Triangulate |
					aiProcess_JoinIdenticalVertices |
					aiProcess_GenSmoothNormals |
					aiProcess_CalcTangentSpace |
					aiProcess_TransformUVCoords |
					aiProcess_SortByPType |
					aiProcess_ImproveCacheLocality
				);

				Asset::asset_type_t<Asset::eAssetType::THREE_D_MODEL> asset{};

				//scene->mMeshes[0]->
				// If the import failed, report it
				if (scene != nullptr && scene->mRootNode != nullptr)
				{


					//Copy Asset meshes
					asset.mNumOfModelMeshAssets = scene->mNumMeshes;
					asset.mModelMeshAssets = new ThreeDModelMesh[asset.mNumOfModelMeshAssets];
					for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
					{
						auto mesh = scene->mMeshes[meshIndex];

						asset.mModelMeshAssets[meshIndex].mName = mesh->mName.C_Str();
						asset.mModelMeshAssets[meshIndex].mPrimitiveType = static_cast<ePrimitiveType>(mesh->mPrimitiveTypes);


						// store Vertices
						asset.mModelMeshAssets[meshIndex].mNumOfVertexs = mesh->mNumVertices;
						asset.mModelMeshAssets[meshIndex].mMeshVertexDatas = new MeshVertexData[asset.mModelMeshAssets[meshIndex].mNumOfVertexs];

						D_ASSERT(mesh->mNumUVComponents[0] == 2);
						D_ASSERT(mesh->HasTangentsAndBitangents());
						D_ASSERT(mesh->HasNormals());
						D_ASSERT(mesh->HasTextureCoords(0));

						// we support only uv one channel
						for (unsigned int verticeIndex = 0; verticeIndex < asset.mModelMeshAssets[meshIndex].mNumOfVertexs; verticeIndex++)
						{
							std::memmove(&(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mVertex), &(mesh->mVertices[verticeIndex]), sizeof(decltype(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mVertex)));
							std::memmove(&(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTexCoord), &(mesh->mTextureCoords[0][verticeIndex]), sizeof(decltype(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTexCoord)));
							std::memmove(&(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mNormal), &(mesh->mNormals[verticeIndex]), sizeof(decltype(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mNormal)));
							std::memmove(&(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTangent), &(mesh->mTangents[verticeIndex]), sizeof(decltype(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTangent)));
							std::memmove(&(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mBitangent), &(mesh->mBitangents[verticeIndex]), sizeof(decltype(asset.mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mBitangent)));
						}


						// we put indices of all faces at ThreeDModelMesh.mMeshIndices 
						asset.mModelMeshAssets[meshIndex].bHasIndices = mesh->HasFaces();
						if (asset.mModelMeshAssets[meshIndex].bHasIndices)
						{
							asset.mModelMeshAssets[meshIndex].mNumOfIndices = 0;
							for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
							{
								// counting number of faces
								asset.mModelMeshAssets[meshIndex].mNumOfIndices += mesh->mFaces[faceIndex].mNumIndices;

								//asset.mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices = new unsigned int[asset.mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices];
								//memmove(&(asset.mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices[0]), &(mesh->mFaces[faceIndex].mIndices[0]), sizeof(unsigned int) * asset.mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices);
							}


							asset.mModelMeshAssets[meshIndex].mMeshIndices = new unsigned int[asset.mModelMeshAssets[meshIndex].mNumOfIndices]; // reserve indices space
							unsigned int indiceIndex = 0;
							for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
							{
								// copy indice datas from indices of face of mesh of assimp to my asset's indices
								memmove(&(asset.mModelMeshAssets[meshIndex].mMeshIndices[indiceIndex]), &(mesh->mFaces[faceIndex].mIndices[0]), sizeof(unsigned int) * mesh->mFaces[faceIndex].mNumIndices);
								indiceIndex += mesh->mFaces[faceIndex].mNumIndices;
							}
						}



					}

					//scene->mRootNode
					asset.mRootModelNode = new ThreeDModelNode();
					asset.mRootModelNode->mThreeDModelNodeParent = nullptr;
					SetThreeDModelNodesData(asset.mRootModelNode, scene->mRootNode, nullptr, asset, scene);
					apiImporter->FreeScene();
					apiImporterContainer.Release();
					return asset;
				}
				else
				{
					D_DEBUG_LOG({ path.string(), " : 3D Model Asset has no scene" });
					return {};
				}

				// We're done. Everything will be cleaned up by the importer destructor
			}
			/// Create Nodes Recursively
			/// </summary>
			/// <param name="currentNode"></param>
			/// <param name="currentAssimpNode"></param>
			/// <param name="parentNode"></param>
			/// <param name="modelAsset"></param>
			/// <param name="assimpScene"></param>
			/// <returns></returns>
			static void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene)
			{
				currentNode->mThreeDModelNodeParent = parentNode;
				currentNode->mThreeDModelAsset = &modelAsset;
				currentNode->mName = currentAssimpNode->mName.C_Str();

				currentNode->mNumOfModelMeshes = currentAssimpNode->mNumMeshes;
				if (currentAssimpNode->mNumMeshes > 0)
				{
					currentNode->mModelMeshIndexs = new unsigned int[currentNode->mNumOfModelMeshes];
					for (unsigned int meshIndex = 0; meshIndex < currentNode->mNumOfModelMeshes; meshIndex++)
					{
						currentNode->mModelMeshIndexs[meshIndex] = currentAssimpNode->mMeshes[meshIndex];
					}
				}
				else
				{
					currentNode->mModelMeshIndexs = nullptr;
				}

				currentNode->mNumOfThreeDModelNodeChildrens = currentAssimpNode->mNumChildren;
				if (currentAssimpNode->mNumChildren > 0)
				{
					currentNode->mThreeDModelNodeChildrens = new ThreeDModelNode[currentNode->mNumOfThreeDModelNodeChildrens];
					for (unsigned int childrenIndex = 0; childrenIndex < currentNode->mNumOfThreeDModelNodeChildrens; childrenIndex++)
					{
						SetThreeDModelNodesData(&(currentNode->mThreeDModelNodeChildrens[childrenIndex]), currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
					}
				}
				else
				{
					currentNode->mThreeDModelNodeChildrens = nullptr;
				}

			}

		};

		



		
	}

	

}