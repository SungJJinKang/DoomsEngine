#include "AssetExporter_Three_D_Model.h"

#include <assimp/Exporter.hpp>
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
					aiProcess_JoinIdenticalVertices |
					aiProcess_GenSmoothNormals |
					aiProcess_CalcTangentSpace |
					aiProcess_TransformUVCoords |
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
	//what is ExportProperties see https://github.com/assimp/assimp/blob/master/include/assimp/config.h.in -> AI_CONFIG_EXPORT_XFILE_64BIT 
	aiReturn status = assimpExporter.Export(pScene, mAssFileFormatId, path.generic_u8string(), ASSIMP_EXPORT_PROCESSING_SETTING);
	if (status == aiReturn::aiReturn_FAILURE || status == aiReturn::aiReturn_OUTOFMEMORY)
	{
		D_DEBUG_LOG("Fail To Export ASS File", eLogType::D_ERROR);
		NEVER_HAPPEN;
	}

}

void dooms::assetExporter::assetExporterThreeDModel::SetAssFileFormatId(const char* id)
{
	mAssFileFormatId = id;
}
