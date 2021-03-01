#include "AssetImporter.h"

using namespace doom;
using namespace assetimporter;


const std::map<std::string, doom::eAssetType> doom::assetimporter::Assetimporter::AssetExtension
{
	//3D Model Asset Formats
	{".dae", doom::eAssetType::THREE_D_MODEL},
	{ ".blend", doom::eAssetType::THREE_D_MODEL },
	{ ".bvh", doom::eAssetType::THREE_D_MODEL },
	{ ".3ds", doom::eAssetType::THREE_D_MODEL },
	{ ".ase", doom::eAssetType::THREE_D_MODEL },
	{ ".obj", doom::eAssetType::THREE_D_MODEL },
	{ ".glFT", doom::eAssetType::THREE_D_MODEL },
	{ ".ply", doom::eAssetType::THREE_D_MODEL },
	{ ".dxf", doom::eAssetType::THREE_D_MODEL },
	{ ".ifc", doom::eAssetType::THREE_D_MODEL },
	{ ".nff", doom::eAssetType::THREE_D_MODEL },
	{ ".smd", doom::eAssetType::THREE_D_MODEL },
	{ ".vta", doom::eAssetType::THREE_D_MODEL },
	{ ".mdl", doom::eAssetType::THREE_D_MODEL },
	{ ".mdl2", doom::eAssetType::THREE_D_MODEL },
	{ ".mdl3", doom::eAssetType::THREE_D_MODEL },
	{ ".pk3", doom::eAssetType::THREE_D_MODEL },
	{ ".mdmdcl2", doom::eAssetType::THREE_D_MODEL },
	{ ".md5mesh", doom::eAssetType::THREE_D_MODEL },
	{ ".md5anim", doom::eAssetType::THREE_D_MODEL },
	{ ".md5camera ", doom::eAssetType::THREE_D_MODEL },
	{ ".q3o", doom::eAssetType::THREE_D_MODEL },
	{ ".q3s", doom::eAssetType::THREE_D_MODEL },
	{ ".raw", doom::eAssetType::THREE_D_MODEL },
	{ ".ac", doom::eAssetType::THREE_D_MODEL },
	{ ".stl", doom::eAssetType::THREE_D_MODEL },
	{ ".dxf", doom::eAssetType::THREE_D_MODEL },
	{ ".irrmesh", doom::eAssetType::THREE_D_MODEL },
	{ ".irr", doom::eAssetType::THREE_D_MODEL },
	{ ".off", doom::eAssetType::THREE_D_MODEL },
	{ ".dterxf", doom::eAssetType::THREE_D_MODEL },
	{ ".mdl", doom::eAssetType::THREE_D_MODEL },
	{ ".hmp", doom::eAssetType::THREE_D_MODEL },
	{ ".mesh", doom::eAssetType::THREE_D_MODEL },
	{ ".skeleton", doom::eAssetType::THREE_D_MODEL },
	{ ".material", doom::eAssetType::THREE_D_MODEL },
	{ ".ms3d", doom::eAssetType::THREE_D_MODEL },
	{ ".lwo", doom::eAssetType::THREE_D_MODEL },
	{ ".lws", doom::eAssetType::THREE_D_MODEL },
	{ ".lxo", doom::eAssetType::THREE_D_MODEL },
	{ ".csm", doom::eAssetType::THREE_D_MODEL },
	{ ".ply", doom::eAssetType::THREE_D_MODEL },
	{ ".cob", doom::eAssetType::THREE_D_MODEL },
	{ ".scn", doom::eAssetType::THREE_D_MODEL },
	{ ".fbx", doom::eAssetType::THREE_D_MODEL },
	//////////////////////////////////////////////////////////////////////////

	{ ".txt", doom::eAssetType::TEXT },
	{ ".ini", doom::eAssetType::TEXT },

	/////////////////////////////////////////////////////

	{ ".glsl", doom::eAssetType::SHADER },

	/////////////////////////////////////////////////////////

	{ ".jpg", doom::eAssetType::TEXTURE },
	{ ".jpeg", doom::eAssetType::TEXTURE },
	{ ".png", doom::eAssetType::TEXTURE },
	{ ".bmp", doom::eAssetType::TEXTURE },
	{ ".tga", doom::eAssetType::TEXTURE },
	//{ ".hdr", doom::eAssetType::TEXTURE },
	{ ".dds", doom::eAssetType::TEXTURE }
};

std::optional<doom::eAssetType> Assetimporter::GetAssetType(const std::filesystem::path& path)
{
	if (path.has_extension())
	{
		auto citer = AssetExtension.find(path.extension().string());
		if (citer != AssetExtension.cend())
		{//find extenstion
			return citer->second;
		}
		else
		{
			return {};
		}
	}
	else
	{
		return {};
	}
}

Assetimporter::Assetimporter(size_t poolSize)
{
}


Assetimporter::~Assetimporter()
{
}

