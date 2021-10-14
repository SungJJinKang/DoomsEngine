#define ASSIMP_DETAIL
#define NOMINMAX

#include "AssetImporterWorker_Three_D_Model.h"

#include <cstring>
#include <Asset/ThreeDModelAsset.h>



using namespace doom;
using namespace doom::assetimporter;


const UINT32 doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::ASSIMP_IMPORT_PROCESSING_SETTING
{
	static_cast<UINT32>(
		aiProcess_RemoveComponent |
		aiProcess_GenBoundingBoxes | 
		aiProcess_CalcTangentSpace
	)
};

const UINT32 doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::ASSIMP_EXPORT_PROCESSING_SETTING
{
	static_cast<UINT32>(
		aiProcess_RemoveComponent |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_TransformUVCoords |
		aiProcess_ImproveCacheLocality |
		aiProcess_GenBoundingBoxes
	)
};



#ifdef DEBUG_MODE
namespace doom
{
	namespace assetimporter 
	{
		class AssimpLogStream : public Assimp::LogStream {
		public:
			// Write womethink using your own functionality
			inline void write(const char* message)
			{
				D_DEBUG_LOG({ "Assimp Debugger : ", message });
			}
		};
	}
}
#endif



void doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::SetAssFileFormatId(const char* id)
{
	AssetImporterWorker_THREE_D_MODEL::mAssFileFormatId = id;
}


bool doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::ImportThreeDModelAsset(
	const std::filesystem::path& path, 
	::doom::asset::ThreeDModelAsset* asset
)
{
	/// read http://sir-kimmi.de/assimp/lib_html/assfile.html
	const aiScene* modelScene = mAssimpImporter.ReadFile(path.generic_u8string(), ASSIMP_IMPORT_PROCESSING_SETTING);

	if (modelScene == NULL)
	{
		D_DEBUG_LOG(mAssimpImporter.GetErrorString(), eLogType::D_ERROR);
		NEVER_HAPPEN;
		return false;
	}
	

	if (path.extension().generic_u8string() != AssetImporterWorker_THREE_D_MODEL::MAIN_3D_MODEL_FILE_FORMAT)
	{//when file isn't assbin file

		//need post process and exporting to .ass file

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// probably to request more postprocessing than we do in this example.

		std::filesystem::path exportPath = path;
		exportPath.replace_extension(MAIN_3D_MODEL_FILE_FORMAT);
		ExportToAssFile(exportPath, modelScene);
	}

	D_ASSERT(modelScene != nullptr);
	
	//scene->mMeshes[0]->
	// If the import failed, report it
	if (modelScene != nullptr)
	{
		Creat3DModelAsset(modelScene, asset);
		mAssimpImporter.FreeScene();
		//apiImporter.Release(); Believe RAII
		return true;
	}
	else
	{
		D_DEBUG_LOG({ path.generic_u8string(), " : 3D Model Asset has no scene" });
		mAssimpImporter.FreeScene();
		return false;
	}

	//modelScene->
	// We're done. Everything will be cleaned up by the importer destructor
}

void AssetImporterWorker_THREE_D_MODEL::InitializeAssimp()
{
	if(AssetImporterWorker::IsInitialized == false)
	{
		mAssimpImporter.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
			aiComponent_COLORS |
			aiComponent_BONEWEIGHTS |
			aiComponent_ANIMATIONS |
			aiComponent_LIGHTS |
			aiComponent_CAMERAS |
			aiComponent_MATERIALS |
			aiComponent_TEXTURES
		);// set removed components flags

		AssetImporterWorker::IsInitialized = true;
	}
}

AssetImporterWorker_THREE_D_MODEL::AssetImporterWorker_THREE_D_MODEL()
	:mAssimpImporter()
{
	InitializeAssimp();
}


void doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::SetThreeDModelNodesData
(
	ThreeDModelNode* currentNode, 
	aiNode* currentAssimpNode, 
	ThreeDModelNode* parentNode, 
	::doom::asset::ThreeDModelAsset* modelAsset, 
	const aiScene* assimpScene
)
{
	currentNode->mThreeDModelNodeParent = parentNode;
	currentNode->mThreeDModelAsset = modelAsset;
	currentNode->mName = currentAssimpNode->mName.C_Str();

	currentNode->mNumOfModelMeshes = currentAssimpNode->mNumMeshes;
	if (currentAssimpNode->mNumMeshes > 0)
	{
		currentNode->mModelMeshIndexs = std::make_unique<UINT32[]>(currentNode->mNumOfModelMeshes);
		for (UINT32 meshIndex = 0; meshIndex < currentNode->mNumOfModelMeshes; meshIndex++)
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
		currentNode->mThreeDModelNodeChildrens = std::make_unique<ThreeDModelNode[]>(currentNode->mNumOfThreeDModelNodeChildrens);
		for (UINT32 childrenIndex = 0; childrenIndex < currentNode->mNumOfThreeDModelNodeChildrens; childrenIndex++)
		{
			SetThreeDModelNodesData(&(currentNode->mThreeDModelNodeChildrens[childrenIndex]), currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
		}
	}
	else
	{
		currentNode->mThreeDModelNodeChildrens = nullptr;
	}

}


void doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::Creat3DModelAsset
(
	const aiScene* pScene, 
	::doom::asset::ThreeDModelAsset* asset
)
{
	//pScene->mMeshes[0]->
	// If the import failed, report it
	D_ASSERT(pScene != nullptr && pScene->mRootNode != nullptr);

	//Copy Asset meshes
	asset->mNumOfModelMeshAssets = pScene->mNumMeshes;
	asset->mModelMeshAssets = std::make_unique<ThreeDModelMesh[]>(asset->mNumOfModelMeshAssets);
	for (UINT32 meshIndex = 0; meshIndex < pScene->mNumMeshes; meshIndex++)
	{
		auto mesh = pScene->mMeshes[meshIndex];


		asset->mModelMeshAssets[meshIndex].mName = mesh->mName.C_Str();

		//why address of mAABB3D.mLowerBound
		//because mAABB is virtual class, it has virtual table pointer internally ( we can't access )
		//so if you access to mAABB3D, virtual table pointer take up foremost 4 byte of mAABB3D

		asset->mModelMeshAssets[meshIndex].mAABB3D.mLowerBound.x = mesh->mAABB.mMin.x;
		asset->mModelMeshAssets[meshIndex].mAABB3D.mLowerBound.y = mesh->mAABB.mMin.y;
		asset->mModelMeshAssets[meshIndex].mAABB3D.mLowerBound.z = mesh->mAABB.mMin.z;
		asset->mModelMeshAssets[meshIndex].mAABB3D.mLowerBound.w = 0.0f;

		asset->mModelMeshAssets[meshIndex].mAABB3D.mUpperBound.x = mesh->mAABB.mMax.x;
		asset->mModelMeshAssets[meshIndex].mAABB3D.mUpperBound.y = mesh->mAABB.mMax.y;
		asset->mModelMeshAssets[meshIndex].mAABB3D.mUpperBound.z = mesh->mAABB.mMax.z;
		asset->mModelMeshAssets[meshIndex].mAABB3D.mUpperBound.w = 0.0f;

		asset->mModelMeshAssets[meshIndex].mSphere.mRadius = (asset->mModelMeshAssets[meshIndex].mAABB3D.mUpperBound - asset->mModelMeshAssets[meshIndex].mAABB3D.mLowerBound).magnitude() * 0.5f;

		switch (mesh->mPrimitiveTypes)
		{
		case aiPrimitiveType::aiPrimitiveType_LINE:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::LINES;
			break;
		case aiPrimitiveType::aiPrimitiveType_POINT:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::POINTS;
			break;
		case aiPrimitiveType::aiPrimitiveType_POLYGON:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::TRIANGLES;
			break;
		case aiPrimitiveType::aiPrimitiveType_TRIANGLE:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::TRIANGLES;
			break;
		case aiPrimitiveType::_aiPrimitiveType_Force32Bit:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::TRIANGLES;
			break;
		default:
			D_ASSERT(0);
		}


		// store Vertices
		asset->mModelMeshAssets[meshIndex].mNumOfVertexs = mesh->mNumVertices;
		asset->mModelMeshAssets[meshIndex].mMeshVertexDatas = std::make_unique<MeshVertexData[]>(asset->mModelMeshAssets[meshIndex].mNumOfVertexs);

		D_ASSERT(mesh->mNumUVComponents[0] == 2);
		D_ASSERT(mesh->HasTangentsAndBitangents());
		D_ASSERT(mesh->HasNormals());
		D_ASSERT(mesh->HasTextureCoords(0));

		// we support only uv one channel
		for (UINT32 verticeIndex = 0; verticeIndex < asset->mModelMeshAssets[meshIndex].mNumOfVertexs; verticeIndex++)
		{
			std::memcpy(&(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mVertex), &(mesh->mVertices[verticeIndex]), sizeof(decltype(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mVertex)));
			std::memcpy(&(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTexCoord), &(mesh->mTextureCoords[0][verticeIndex]), sizeof(decltype(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTexCoord)));
			std::memcpy(&(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mNormal), &(mesh->mNormals[verticeIndex]), sizeof(decltype(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mNormal)));
			std::memcpy(&(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTangent), &(mesh->mTangents[verticeIndex]), sizeof(decltype(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mTangent)));
			std::memcpy(&(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mBitangent), &(mesh->mBitangents[verticeIndex]), sizeof(decltype(asset->mModelMeshAssets[meshIndex].mMeshVertexDatas[verticeIndex].mBitangent)));
		}


		// we put indices of all faces at ThreeDModelMesh.mMeshIndices 
		asset->mModelMeshAssets[meshIndex].bHasIndices = mesh->HasFaces();
		if (asset->mModelMeshAssets[meshIndex].bHasIndices)
		{
			asset->mModelMeshAssets[meshIndex].mNumOfIndices = 0;
			for (UINT32 faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
			{
				// counting number of faces
				asset->mModelMeshAssets[meshIndex].mNumOfIndices += mesh->mFaces[faceIndex].mNumIndices;

				//asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices = new UINT32[asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices];
				//memmove(&(asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices[0]), &(mesh->mFaces[faceIndex].mIndices[0]), sizeof(UINT32) * asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices);
			}


			asset->mModelMeshAssets[meshIndex].mMeshIndices = std::make_unique<UINT32[]>(asset->mModelMeshAssets[meshIndex].mNumOfIndices); // reserve indices space
			UINT32 indiceIndex = 0;
			for (UINT32 faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
			{
				// copy indice datas from indices of face of mesh of assimp to my asset's indices
				memcpy(&(asset->mModelMeshAssets[meshIndex].mMeshIndices[indiceIndex]), &(mesh->mFaces[faceIndex].mIndices[0]), sizeof(UINT32) * mesh->mFaces[faceIndex].mNumIndices);
				indiceIndex += mesh->mFaces[faceIndex].mNumIndices;
			}
		}
	}

	//pScene->mRootNode
	asset->mRootModelNode = std::make_unique<ThreeDModelNode>();
	asset->mRootModelNode->mThreeDModelNodeParent = nullptr;
	SetThreeDModelNodesData(asset->mRootModelNode.get(), pScene->mRootNode, nullptr, asset, pScene);

}


void doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::ExportToAssFile
(
	const std::filesystem::path& path,
	const aiScene* pScene
)
{
	D_ASSERT(AssetImporterWorker_THREE_D_MODEL::mAssFileFormatId.size() > 0);
	Assimp::Exporter assimpExporter{};
	//what is ExportProperties see https://github.com/assimp/assimp/blob/master/include/assimp/config.h.in -> AI_CONFIG_EXPORT_XFILE_64BIT 
	aiReturn status = assimpExporter.Export(pScene, AssetImporterWorker_THREE_D_MODEL::mAssFileFormatId, path.generic_u8string(), ASSIMP_EXPORT_PROCESSING_SETTING);
	if (status == aiReturn::aiReturn_FAILURE || status == aiReturn::aiReturn_OUTOFMEMORY)
	{
		D_DEBUG_LOG("Fail To Export ASS File", eLogType::D_ERROR);
		NEVER_HAPPEN;
	}
}


bool doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::ImportSpecificAsset
(
	const std::filesystem::path& path, 
	doom::asset::Asset* asset
) 
{
	return ImportThreeDModelAsset(path, static_cast<doom::asset::ThreeDModelAsset*>(asset));
}

doom::asset::eAssetType AssetImporterWorker_THREE_D_MODEL::GetEAssetType() const
{
	return doom::asset::eAssetType::THREE_D_MODEL;
}

void AssetImporterWorker_THREE_D_MODEL::InitializeAssetImporterWorkerStatic()
{
	if (AssetImporterWorker::IsInitialized == false)
	{
#ifdef DEBUG_MODE
		Assimp::DefaultLogger::create("", Assimp::Logger::NORMAL);
		// Select the kinds of messages you want to receive on this log stream
		const UINT32 severity = Assimp::Logger::Err;// | Assimp::Logger::Warn;

		// Attaching it to the default logger
		Assimp::DefaultLogger::get()->attachStream(new doom::assetimporter::AssimpLogStream, severity);
#endif

		Assimp::Exporter exporter{};
		SIZE_T formatCount = exporter.GetExportFormatCount();
		for (SIZE_T i = 0; i < formatCount; i++)
		{
			const char* extension = exporter.GetExportFormatDescription(i)->fileExtension;
			if (std::strcmp(extension, AssetImporterWorker_THREE_D_MODEL::MAIN_3D_MODEL_FILE_FORMAT.data() + 1) == 0)
			{
				doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::SetAssFileFormatId(extension);
				break;
			}
		}

		AssetImporterWorker::IsInitialized = true;
	}

}
