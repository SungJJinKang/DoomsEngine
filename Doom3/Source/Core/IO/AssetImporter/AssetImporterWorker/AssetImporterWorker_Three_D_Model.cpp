#define ASSIMP_DETAIL
#define NOMINMAX

#include "AssetImporterWorker_Three_D_Model.h"

#include <cstring>
#include <memory>

#include <Asset/ThreeDModelAsset.h>
#include "AssetImporterWorker_Texture.h"
#include <Graphics/Buffer/eVertexArrayFlag.h>
#include <IO/AssetExporter/AssetExporter_Three_D_Model.h>


using namespace dooms;
using namespace dooms::assetImporter;


const UINT32 dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::ASSIMP_IMPORT_PROCESSING_SETTING
{
	static_cast<UINT32>(
		aiProcess_RemoveComponent |
		aiProcess_GenBoundingBoxes | 
		aiProcess_CalcTangentSpace
	)
};




#ifdef DEBUG_MODE
namespace dooms
{
	namespace assetImporter 
	{
		class AssimpLogStream : public Assimp::LogStream {
		public:
			AssimpLogStream() = default;
			// Write womethink using your own functionality
			inline virtual void write(const char* message) override
			{
				D_DEBUG_LOG(eLogType::D_LOG, "Assimp Debugger : %s", message);
			}
		};
	}
}
#endif



bool dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::ImportThreeDModelAsset(
	const std::filesystem::path& path, 
	::dooms::asset::ThreeDModelAsset* asset
)
{
	/// read http://sir-kimmi.de/assimp/lib_html/assfile.html
	const aiScene* modelScene = mAssimpImporter.ReadFile(path.generic_u8string(), ASSIMP_IMPORT_PROCESSING_SETTING);

	if (modelScene == NULL)
	{
		D_DEBUG_LOG(eLogType::D_ERROR, mAssimpImporter.GetErrorString());
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
		dooms::assetExporter::assetExporterThreeDModel::ExportToAssFile(exportPath, modelScene);
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
		D_DEBUG_LOG(eLogType::D_LOG, "%s : 3D Model Asset has no scene", path.generic_u8string().c_str());
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



void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::SetThreeDModelNodesData
(
	ThreeDModelNode* currentNode, 
	aiNode* currentAssimpNode, 
	ThreeDModelNode* parentNode, 
	::dooms::asset::ThreeDModelAsset* modelAsset, 
	const aiScene* assimpScene
)
{
	currentNode->mThreeDModelNodeParent = parentNode;
	currentNode->mName = currentAssimpNode->mName.C_Str();
	
	if (currentAssimpNode->mNumMeshes > 0)
	{
		currentNode->mModelMeshIndexs.resize(currentAssimpNode->mNumMeshes);
		for (UINT32 meshIndex = 0; meshIndex < currentAssimpNode->mNumMeshes ; meshIndex++)
		{
			currentNode->mModelMeshIndexs[meshIndex] = currentAssimpNode->mMeshes[meshIndex];
		}
	}
	else
	{
		currentNode->mModelMeshIndexs.resize(0);
	}


	if (currentAssimpNode->mNumChildren > 0)
	{
		currentNode->mThreeDModelNodeChildrens.resize(currentAssimpNode->mNumChildren, nullptr);
		for (UINT32 childrenIndex = 0; childrenIndex < currentAssimpNode->mNumChildren ; childrenIndex++)
		{
			SetThreeDModelNodesData(&(currentNode->mThreeDModelNodeChildrens[childrenIndex]), currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
		}
	}
	else
	{
		currentNode->mThreeDModelNodeChildrens.resize(0);
	}

}




void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::Creat3DModelAsset
(
	const aiScene* pScene, 
	::dooms::asset::ThreeDModelAsset* asset
)
{
	//pScene->mMeshes[0]->
	// If the import failed, report it
	D_ASSERT(pScene != nullptr && pScene->mRootNode != nullptr);

	//Copy Asset meshes
	asset->mModelMeshAssets.resize(pScene->mNumMeshes, nullptr);
	for (UINT32 meshIndex = 0; meshIndex < pScene->mNumMeshes; meshIndex++)
	{
		auto mesh = pScene->mMeshes[meshIndex];

		asset->mModelMeshAssets[meshIndex].mVertexArrayFlag = 0;

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
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VertexVector2;
			break;
		case aiPrimitiveType::aiPrimitiveType_POINT:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::POINTS;
			D_ASSERT(false);
			break;
		case aiPrimitiveType::aiPrimitiveType_POLYGON:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::TRIANGLES;
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VertexVector3;
			break;
		case aiPrimitiveType::aiPrimitiveType_TRIANGLE:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::TRIANGLES;
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VertexVector3;
			break;
		case aiPrimitiveType::_aiPrimitiveType_Force32Bit:
			asset->mModelMeshAssets[meshIndex].mPrimitiveType = ePrimitiveType::TRIANGLES;
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VertexVector3;
			break;
		default:
			D_ASSERT(0);
		}


		// store Vertices

		D_ASSERT(mesh->mNumUVComponents[0] == 2);
		D_ASSERT(mesh->HasTangentsAndBitangents());
		D_ASSERT(mesh->HasNormals());
		D_ASSERT(mesh->HasTextureCoords(0));

		// we support only uv one channel

		asset->mModelMeshAssets[meshIndex].mMeshDatas.Allocate(mesh->mNumVertices);

		std::memcpy(asset->mModelMeshAssets[meshIndex].mMeshDatas.mVertex, mesh->mVertices, mesh->mNumVertices * sizeof(*(mesh->mVertices)));

		if (mesh->HasTextureCoords(0))
		{
			std::memcpy(asset->mModelMeshAssets[meshIndex].mMeshDatas.mTexCoord, mesh->mTextureCoords[0], mesh->mNumVertices * sizeof(*(mesh->mTextureCoords[0])));
		}

		if (mesh->HasNormals())
		{
			std::memcpy(asset->mModelMeshAssets[meshIndex].mMeshDatas.mNormal, mesh->mNormals, mesh->mNumVertices * sizeof(*(mesh->mNormals)));
		}

		if (mesh->HasTangentsAndBitangents())
		{
			std::memcpy(asset->mModelMeshAssets[meshIndex].mMeshDatas.mTangent, mesh->mTangents, mesh->mNumVertices * sizeof(*(mesh->mTangents)));
			std::memcpy(asset->mModelMeshAssets[meshIndex].mMeshDatas.mBitangent, mesh->mBitangents, mesh->mNumVertices * sizeof(*(mesh->mBitangents)));
		}

		if(mesh->HasTextureCoords(0))
		{
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::TexCoord;
		}

		if(mesh->HasNormals())
		{
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::mNormal;
		}

		if(mesh->HasTangentsAndBitangents())
		{
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::mTangent;
			asset->mModelMeshAssets[meshIndex].mVertexArrayFlag |= dooms::graphics::eVertexArrayFlag::mBitangent;
		}

		// we put indices of all faces at ThreeDModelMesh.mMeshIndices 
		asset->mModelMeshAssets[meshIndex].bHasIndices = mesh->HasFaces();
		if (asset->mModelMeshAssets[meshIndex].bHasIndices)
		{
			UINT32 numberOfIndeces = 0;
			for (UINT32 faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
			{
				// counting number of faces
				numberOfIndeces += mesh->mFaces[faceIndex].mNumIndices;

				//asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices = new UINT32[asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices];
				//memmove(&(asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices[0]), &(mesh->mFaces[faceIndex].mIndices[0]), sizeof(UINT32) * asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices);
			}


			asset->mModelMeshAssets[meshIndex].mMeshIndices.resize(numberOfIndeces); // reserve indices space
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
	asset->mRootModelNode = dooms::CreateDObject<ThreeDModelNode>();
	asset->mRootModelNode->mThreeDModelNodeParent = nullptr;
	SetThreeDModelNodesData(asset->mRootModelNode, pScene->mRootNode, nullptr, asset, pScene);

}




bool dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::ImportSpecificAsset
(
	const std::filesystem::path& path, 
	dooms::asset::Asset* asset
) 
{
	return ImportThreeDModelAsset(path, static_cast<dooms::asset::ThreeDModelAsset*>(asset));
}

dooms::asset::eAssetType AssetImporterWorker_THREE_D_MODEL::GetEAssetType() const
{
	return dooms::asset::eAssetType::THREE_D_MODEL;
}

#ifdef DEBUG_MODE
static std::unique_ptr<dooms::assetImporter::AssimpLogStream> AttachedAssimpLogStream = nullptr;
static const UINT32 AssimpLoggerStreamSeverity = Assimp::Logger::Err;// | Assimp::Logger::Warn;
void AssetImporterWorker_THREE_D_MODEL::ClearAssimpLooger()
{
	if (AttachedAssimpLogStream)
	{
		Assimp::DefaultLogger::get()->detatchStream(AttachedAssimpLogStream.get(), AssimpLoggerStreamSeverity);
		AttachedAssimpLogStream.reset();
	}
	Assimp::DefaultLogger::kill();
}
#endif

void AssetImporterWorker_THREE_D_MODEL::InitializeAssetImporterWorkerStatic()
{
	bool expected = false;
	if (AssetImporterWorker::IsInitializedStatic.compare_exchange_strong(expected, true, std::memory_order_seq_cst, std::memory_order_relaxed) )
	{
#ifdef DEBUG_MODE
		ClearAssimpLooger();

		Assimp::DefaultLogger::create("", Assimp::Logger::NORMAL);
		// Select the kinds of messages you want to receive on this log stream
		// Attaching it to the default logger
		AttachedAssimpLogStream = std::make_unique<dooms::assetImporter::AssimpLogStream>();
		Assimp::DefaultLogger::get()->attachStream(AttachedAssimpLogStream.get(), AssimpLoggerStreamSeverity);
#endif

		Assimp::Exporter exporter{};
		size_t formatCount = exporter.GetExportFormatCount();
		for (size_t i = 0; i < formatCount; i++)
		{
			const char* extension = exporter.GetExportFormatDescription(i)->fileExtension;
			if (std::strcmp(extension, AssetImporterWorker_THREE_D_MODEL::MAIN_3D_MODEL_FILE_FORMAT.data() + 1) == 0)
			{
				dooms::assetExporter::assetExporterThreeDModel::SetAssFileFormatId(extension);
				break;
			}
		}

		AssetImporterWorker::IsInitializedStatic = true;
	}

}

void AssetImporterWorker_THREE_D_MODEL::UnInitializeAssetImporterWorkerStatic()
{
#ifdef DEBUG_MODE
	ClearAssimpLooger();
#endif
}
