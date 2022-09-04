#define ASSIMP_DETAIL
#define NOMINMAX

#include "AssetImporterWorker_Three_D_Model.h"

#include <cstring>
#include <memory>

#include <Asset/ThreeDModelAsset.h>
#include "AssetImporterWorker_Texture.h"
#include <Rendering/Buffer/eVertexArrayFlag.h>
#include <Asset/AssetImportExporter/AssetExporter/AssetExporter_Three_D_Model.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

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
	const aiScene* modelScene = NULL;
	if(path.extension().generic_u8string() == AssetImporterWorker_THREE_D_MODEL::MAIN_3D_MODEL_FILE_FORMAT)
	{
		UINT32 assimpImportProcessingSetting = ASSIMP_IMPORT_PROCESSING_SETTING;
		//if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		//{
			assimpImportProcessingSetting |= aiProcess_FlipUVs;
		//}

		modelScene = mAssimpImporter.ReadFile(path.generic_u8string(), assimpImportProcessingSetting);

		if (modelScene == NULL)
		{
			D_DEBUG_LOG(eLogType::D_ERROR, mAssimpImporter.GetErrorString());
			NEVER_HAPPEN;
			return false;
		}
	}
	else
	{

		modelScene = mAssimpImporter.ReadFile(path.generic_u8string(), ASSIMP_IMPORT_PROCESSING_SETTING);

		if (modelScene == NULL)
		{
			D_DEBUG_LOG(eLogType::D_ERROR, mAssimpImporter.GetErrorString());
			NEVER_HAPPEN;
			return false;
		}

		//when file isn't assbin file

		//need post process and exporting to .ass file

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// probably to request more postprocessing than we do in this example.

		std::filesystem::path exportPath = path;
		exportPath.replace_extension(MAIN_3D_MODEL_FILE_FORMAT);
		dooms::assetExporter::assetExporterThreeDModel::ExportToAssFile(exportPath, modelScene);
	}

	

	bool isSuccess = false;

	//scene->mMeshes[0]->
	// If the import failed, report it
	if (modelScene != nullptr && path.extension().generic_u8string() == AssetImporterWorker_THREE_D_MODEL::MAIN_3D_MODEL_FILE_FORMAT)
	{
		Creat3DModelAsset(modelScene, asset);
		//apiImporter.Release(); Believe RAII
		isSuccess = true;
	}

	try
	{
		mAssimpImporter.FreeScene();
	}
	catch (const std::exception& ex)
	{
		D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Export ASS File : %s", ex.what());
	}
	catch (const std::string& ex)
	{
		D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Export ASS File : %s", ex.c_str());
	}
	catch (...)
	{
		NEVER_HAPPEN;
	}

	return isSuccess;
}

void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::InitializeAssimp()
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

bool dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::IsValidMesh(const aiMesh* const assimpMesh)
{
	return
		(assimpMesh->mNumUVComponents[0] == 2) &&
		(assimpMesh->HasTangentsAndBitangents()) &&
		(assimpMesh->HasNormals()) &&
		(assimpMesh->HasTextureCoords(0));
}

dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::AssetImporterWorker_THREE_D_MODEL()
	:mAssimpImporter()
{
	InitializeAssimp();
}



void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::SetMeshNodeData
(
	FMeshNode* CurrentMeshNode, 
	aiNode* CurrentAssimpMeshNode, 
	FMeshNode* ParentMeshNode, 
	::dooms::asset::ThreeDModelAsset* ModelAsset, 
	const aiScene* AssimpScene
)
{
	CurrentMeshNode->ParentMeshNode = ParentMeshNode;
	CurrentMeshNode->MeshNodeName = CurrentAssimpMeshNode->mName.C_Str();
	
	if (CurrentAssimpMeshNode->mNumMeshes > 0)
	{
		CurrentMeshNode->ModelMeshIndexList.resize(CurrentAssimpMeshNode->mNumMeshes);
		for (UINT32 MeshIndex = 0; MeshIndex < CurrentAssimpMeshNode->mNumMeshes ; MeshIndex++)
		{
			CurrentMeshNode->ModelMeshIndexList[MeshIndex] = CurrentAssimpMeshNode->mMeshes[MeshIndex];
		}
	}
	else
	{
		CurrentMeshNode->ModelMeshIndexList.resize(0);
	}


	if (CurrentAssimpMeshNode->mNumChildren > 0)
	{
		CurrentMeshNode->MeshNodeChildrenList.resize(CurrentAssimpMeshNode->mNumChildren);
		for (UINT32 ChildMeshIndex = 0; ChildMeshIndex < CurrentAssimpMeshNode->mNumChildren ; ChildMeshIndex++)
		{
			SetMeshNodeData(&(CurrentMeshNode->MeshNodeChildrenList[ChildMeshIndex]), CurrentAssimpMeshNode->mChildren[ChildMeshIndex], CurrentMeshNode, ModelAsset, AssimpScene);
		}
	}
	else
	{
		CurrentMeshNode->MeshNodeChildrenList.resize(0);
	}

}




void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::Creat3DModelAsset
(
	const aiScene* pScene, 
	::dooms::asset::ThreeDModelAsset* ModelAsset
)
{
	//pScene->mMeshes[0]->
	// If the import failed, report it
	D_ASSERT(pScene != nullptr && pScene->mRootNode != nullptr);
	
	//Copy Asset meshes
	ModelAsset->MeshRawDataList.resize(pScene->mNumMeshes);
	for (UINT32 MeshIndex = 0; MeshIndex < pScene->mNumMeshes; MeshIndex++)
	{
		const aiMesh* const AssimpMesh = pScene->mMeshes[MeshIndex];

		if(IsValidMesh(AssimpMesh) == false)
		{
			ModelAsset->MeshRawDataList[MeshIndex].bIsValidMesh = false;
			continue;
		}

		ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag = 0;

		ModelAsset->MeshRawDataList[MeshIndex].MeshName = AssimpMesh->mName.C_Str();

		//why address of mAABB3D.mLowerBound
		//because mAABB is virtual class, it has virtual table pointer internally ( we can't access )
		//so if you access to mAABB3D, virtual table pointer take up foremost 4 byte of mAABB3D

		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mLowerBound.x = AssimpMesh->mAABB.mMin.x;
		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mLowerBound.y = AssimpMesh->mAABB.mMin.y;
		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mLowerBound.z = AssimpMesh->mAABB.mMin.z;
		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mLowerBound.w = 0.0f;

		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mUpperBound.x = AssimpMesh->mAABB.mMax.x;
		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mUpperBound.y = AssimpMesh->mAABB.mMax.y;
		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mUpperBound.z = AssimpMesh->mAABB.mMax.z;
		ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mUpperBound.w = 0.0f;

		ModelAsset->MeshRawDataList[MeshIndex].BoundingSphere.mRadius = (ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mUpperBound - ModelAsset->MeshRawDataList[MeshIndex].BoundingBox.mLowerBound).magnitude() * 0.5f;

		switch (AssimpMesh->mPrimitiveTypes)
		{
		case aiPrimitiveType::aiPrimitiveType_LINE:
			ModelAsset->MeshRawDataList[MeshIndex].PrimitiveType = dooms::graphics::GraphicsAPI::ePrimitiveType::LINES;
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VERTEX_VECTOR2;
			break;
		case aiPrimitiveType::aiPrimitiveType_POINT:
			ModelAsset->MeshRawDataList[MeshIndex].PrimitiveType = dooms::graphics::GraphicsAPI::ePrimitiveType::POINTS;
			D_ASSERT(false);
			break;
		case aiPrimitiveType::aiPrimitiveType_POLYGON:
			ModelAsset->MeshRawDataList[MeshIndex].PrimitiveType = dooms::graphics::GraphicsAPI::ePrimitiveType::TRIANGLES;
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VERTEX_VECTOR3;
			break;
		case aiPrimitiveType::aiPrimitiveType_TRIANGLE:
		case aiPrimitiveType::aiPrimitiveType_TRIANGLE | aiPrimitiveType::aiPrimitiveType_NGONEncodingFlag:
			ModelAsset->MeshRawDataList[MeshIndex].PrimitiveType = dooms::graphics::GraphicsAPI::ePrimitiveType::TRIANGLES;
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VERTEX_VECTOR3;
			break;
		case aiPrimitiveType::_aiPrimitiveType_Force32Bit:
			ModelAsset->MeshRawDataList[MeshIndex].PrimitiveType = dooms::graphics::GraphicsAPI::ePrimitiveType::TRIANGLES;
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::VERTEX_VECTOR3;
			break;
		default:
			D_ASSERT(0);
		}


		// store Vertices

		//D_ASSERT(IsValidMesh(mesh) == true);

		// we support only uv one channel
		
		if (AssimpMesh->HasTextureCoords(0))
		{
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::TEXCOORD;
		}

		if (AssimpMesh->HasNormals())
		{
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::NORMAL;
		}

		if (AssimpMesh->HasTangentsAndBitangents())
		{
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::TANGENT;
			ModelAsset->MeshRawDataList[MeshIndex].VertexArrayFlag |= dooms::graphics::eVertexArrayFlag::BI_TANGENT;
		}

		ModelAsset->MeshRawDataList[MeshIndex].Allocate(AssimpMesh->mNumVertices);

		std::memcpy(ModelAsset->MeshRawDataList[MeshIndex].Vertex, AssimpMesh->mVertices, AssimpMesh->mNumVertices * sizeof(*(AssimpMesh->mVertices)));

		if (AssimpMesh->HasTextureCoords(0))
		{
			std::memcpy(ModelAsset->MeshRawDataList[MeshIndex].TexCoord, AssimpMesh->mTextureCoords[0], AssimpMesh->mNumVertices * sizeof(*(AssimpMesh->mTextureCoords[0])));
		}

		if (AssimpMesh->HasNormals())
		{
			std::memcpy(ModelAsset->MeshRawDataList[MeshIndex].Normal, AssimpMesh->mNormals, AssimpMesh->mNumVertices * sizeof(*(AssimpMesh->mNormals)));
		}

		if (AssimpMesh->HasTangentsAndBitangents())
		{
			std::memcpy(ModelAsset->MeshRawDataList[MeshIndex].Tangent, AssimpMesh->mTangents, AssimpMesh->mNumVertices * sizeof(*(AssimpMesh->mTangents)));
			std::memcpy(ModelAsset->MeshRawDataList[MeshIndex].Bitangent, AssimpMesh->mBitangents, AssimpMesh->mNumVertices * sizeof(*(AssimpMesh->mBitangents)));
		}

		// we put indices of all faces at ThreeDModelMesh.mMeshIndices 
		ModelAsset->MeshRawDataList[MeshIndex].bHasIndices = AssimpMesh->HasFaces();
		if (ModelAsset->MeshRawDataList[MeshIndex].bHasIndices)
		{
			UINT32 CountOfIndice = 0;
			for (UINT32 faceIndex = 0; faceIndex < AssimpMesh->mNumFaces; faceIndex++)
			{
				// counting number of faces
				CountOfIndice += AssimpMesh->mFaces[faceIndex].mNumIndices;

				//asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices = new UINT32[asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices];
				//memmove(&(asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mIndices[0]), &(mesh->mFaces[faceIndex].mIndices[0]), sizeof(UINT32) * asset->mModelMeshAssets[meshIndex].mMeshFaceDatas[faceIndex].mNumIndices);
			}


			ModelAsset->MeshRawDataList[MeshIndex].MeshIndices.resize(CountOfIndice); // reserve indices space
			UINT32 indiceIndex = 0;
			for (UINT32 faceIndex = 0; faceIndex < AssimpMesh->mNumFaces; faceIndex++)
			{
				// copy indice datas from indices of face of mesh of assimp to my asset's indices
				std::memcpy(&(ModelAsset->MeshRawDataList[MeshIndex].MeshIndices[indiceIndex]), &(AssimpMesh->mFaces[faceIndex].mIndices[0]), sizeof(UINT32) * AssimpMesh->mFaces[faceIndex].mNumIndices);
				indiceIndex += AssimpMesh->mFaces[faceIndex].mNumIndices;
			}
		}

		ModelAsset->MeshRawDataList[MeshIndex].bIsValidMesh = true;
		
	}

	//pScene->mRootNode
	ModelAsset->Root3DModelNode = std::make_unique<FMeshNode>();
	ModelAsset->Root3DModelNode->ParentMeshNode = nullptr;
	SetMeshNodeData(ModelAsset->Root3DModelNode.get(), pScene->mRootNode, nullptr, ModelAsset, pScene);

}


dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::~AssetImporterWorker_THREE_D_MODEL() = default;

bool dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::ImportSpecificAsset
(
	const std::filesystem::path& path, 
	dooms::asset::Asset* asset
) 
{
	return ImportThreeDModelAsset(path, static_cast<dooms::asset::ThreeDModelAsset*>(asset));
}

dooms::asset::eAssetType dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::GetEAssetType() const
{
	return dooms::asset::eAssetType::THREE_D_MODEL;
}

#ifdef DEBUG_MODE
static std::unique_ptr<dooms::assetImporter::AssimpLogStream> AttachedAssimpLogStream = nullptr;
static const UINT32 AssimpLoggerStreamSeverity = Assimp::Logger::Err;// | Assimp::Logger::Warn;
void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::ClearAssimpLooger()
{
	if (AttachedAssimpLogStream)
	{
		Assimp::DefaultLogger::get()->detachStream(AttachedAssimpLogStream.get(), AssimpLoggerStreamSeverity);
		AttachedAssimpLogStream.reset();
	}
	Assimp::DefaultLogger::kill();
}
#endif

void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::InitializeAssetImporterWorkerStatic()
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

void dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::UnInitializeAssetImporterWorkerStatic()
{
#ifdef DEBUG_MODE
	ClearAssimpLooger();
#endif
}
