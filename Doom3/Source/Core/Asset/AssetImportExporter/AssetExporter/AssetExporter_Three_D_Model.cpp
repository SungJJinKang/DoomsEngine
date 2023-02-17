#include "AssetExporter_Three_D_Model.h"

#include <assimp/Exporter.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

namespace dooms
{

	namespace assetExporter
	{
		namespace assetExporterThreeDModel
		{
			static std::string mAssFileFormatId{};

			const UINT32 ASSIMP_EXPORT_PROCESSING_SETTING =
			{
				static_cast<UINT32>(
					aiProcess_RemoveComponent |
					aiProcess_Triangulate |
					aiProcess_SortByPType |
					aiProcess_CalcTangentSpace |
					aiProcess_GenNormals |
					aiProcess_ImproveCacheLocality |
					aiProcess_GenBoundingBoxes
				)
			};

		}
	}
}

void dooms::assetExporter::assetExporterThreeDModel::ExportToAssFile
(
	const std::filesystem::path& path,
	const aiScene* const pScene
)
{
	D_ASSERT(mAssFileFormatId.size() > 0);
	Assimp::Exporter assimpExporter{};
	
	std::unique_ptr<Assimp::ExportProperties> exportProperties = std::make_unique<Assimp::ExportProperties>();
	exportProperties->SetPropertyInteger
	(
		AI_CONFIG_PP_SBP_REMOVE, 
		aiPrimitiveType_POLYGON | aiPrimitiveType_LINE | aiPrimitiveType_POINT
	);
	//what is ExportProperties see https://github.com/assimp/assimp/blob/master/include/assimp/config.h.in -> AI_CONFIG_EXPORT_XFILE_64BIT 

	try
	{
		aiReturn status = assimpExporter.Export
		(
			pScene,
			mAssFileFormatId,
			path.generic_u8string(),
			ASSIMP_EXPORT_PROCESSING_SETTING,
			exportProperties.get()
		);
		if (status == aiReturn::aiReturn_FAILURE || status == aiReturn::aiReturn_OUTOFMEMORY)
		{
			D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Export ASS File");
			ASSUME_ZERO;
		}
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
		ASSUME_ZERO;
	}
	
	exportProperties.release(); // TODO : FIX THIS
}

void dooms::assetExporter::assetExporterThreeDModel::SetAssFileFormatId(const char* id)
{
	mAssFileFormatId = id;
}
