#include "AssetImporterWorker_Three_D_Model.h"

#include <type_traits>


//ai_real is assimp's vector element data type
//assimp's vector element data type should equal to my Math::vector's element type
static_assert(std::is_same_v<ai_real, Vector3::value_type>);


namespace doom
{
	namespace assetimporter
	{
		//extern template class AssetApiImporter<Asset::eAssetType::THREE_D_MODEL>;

		template std::optional<Asset::asset_type_t<Asset::eAssetType::THREE_D_MODEL>> ReadAssetFile<Asset::eAssetType::THREE_D_MODEL>(std::filesystem::path path);
		
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


		void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene)
		{
			currentNode->mThreeDModelNodeParent = parentNode;
			currentNode->mThreeDModelAsset = &modelAsset;
			currentNode->mName = currentAssimpNode->mName.C_Str();
			currentNode->mNumOfThreeDmModelMeshes = currentAssimpNode->mNumMeshes;

			currentNode->mThreeDmModelMeshes = new ThreeDModelMesh * [currentAssimpNode->mNumMeshes];
			for (unsigned int meshIndex = 0; meshIndex < currentAssimpNode->mNumMeshes; meshIndex++)
			{
				currentNode->mThreeDmModelMeshes[meshIndex] = &(modelAsset.mModelMeshes[currentAssimpNode->mMeshes[meshIndex]]);
			}

			currentNode->mNumOfThreeDModelNodeChildrens = currentAssimpNode->mNumChildren;
			currentNode->mThreeDModelNodeChildrens = new ThreeDModelNode[currentAssimpNode->mNumChildren];
			for (unsigned int childrenIndex = 0; childrenIndex < currentAssimpNode->mNumChildren; childrenIndex++)
			{
				doom::assetimporter::SetThreeDModelNodesData(&(currentNode->mThreeDModelNodeChildrens[childrenIndex]), currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
			}
		}
		
		template<>
		std::optional<Asset::asset_type_t<Asset::eAssetType::THREE_D_MODEL>> ReadAssetFile<Asset::eAssetType::THREE_D_MODEL>(std::filesystem::path path)
		{
			std::stringstream stream;
			stream << std::this_thread::get_id();

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
			AssetApiImporter<Asset::eAssetType::THREE_D_MODEL> apiImporterContainer = AssetApiImporter<Asset::eAssetType::THREE_D_MODEL>::GetApiImporter();
			auto apiImporter = apiImporterContainer.Get();

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

			Asset::asset_type_t<Asset::eAssetType::THREE_D_MODEL> asset{};

			//scene->mMeshes[0]->
			// If the import failed, report it
			if (scene != nullptr && scene->mRootNode != nullptr)
			{


				//Copy Asset meshes
				asset.mNumOfModelMesh = scene->mNumMeshes;
				asset.mModelMeshes = new ThreeDModelMesh[asset.mNumOfModelMesh];
				for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
				{
					auto mesh = scene->mMeshes[meshIndex];

					asset.mModelMeshes[meshIndex].mName = mesh->mName.C_Str();
					asset.mModelMeshes[meshIndex].mNumOfVertices = mesh->mNumVertices;

					D_ASSERT(mesh->mNumUVComponents[0] == 2);
					D_ASSERT(mesh->HasTangentsAndBitangents());
					D_ASSERT(mesh->HasNormals());
					D_ASSERT(mesh->HasTextureCoords(0));


					for (unsigned int verticeIndex = 0; verticeIndex < asset.mModelMeshes[meshIndex].mNumOfVertices; verticeIndex++)
					{
						memmove(&(asset.mModelMeshes[meshIndex].mMeshVertexData.mVertex), &(mesh->mVertices[verticeIndex]), sizeof(decltype(asset.mModelMeshes[meshIndex].mMeshVertexData.mVertex)));
						memmove(&(asset.mModelMeshes[meshIndex].mMeshVertexData.mTexCoord), &(mesh->mTextureCoords[0][verticeIndex]), sizeof(decltype(asset.mModelMeshes[meshIndex].mMeshVertexData.mTexCoord)));
						memmove(&(asset.mModelMeshes[meshIndex].mMeshVertexData.mNormal), &(mesh->mNormals[verticeIndex]), sizeof(decltype(asset.mModelMeshes[meshIndex].mMeshVertexData.mNormal)));
						memmove(&(asset.mModelMeshes[meshIndex].mMeshVertexData.mTangent), &(mesh->mTangents[verticeIndex]), sizeof(decltype(asset.mModelMeshes[meshIndex].mMeshVertexData.mTangent)));
						memmove(&(asset.mModelMeshes[meshIndex].mMeshVertexData.mBitangent), &(mesh->mBitangents[verticeIndex]), sizeof(decltype(asset.mModelMeshes[meshIndex].mMeshVertexData.mBitangent)));


					}


				}

				//scene->mRootNode
				asset.mRootNode.mThreeDModelNodeParent = nullptr;
				SetThreeDModelNodesData(&(asset.mRootNode), scene->mRootNode, nullptr, asset, scene);
				apiImporter->FreeScene();
				apiImporterContainer.Release();
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