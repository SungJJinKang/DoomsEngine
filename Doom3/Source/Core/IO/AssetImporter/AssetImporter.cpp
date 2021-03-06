#include "AssetImporter.h"

using namespace doom;
using namespace assetimporter;


const std::unordered_map<std::string, ::doom::asset::eAssetType> doom::assetimporter::Assetimporter::AssetExtension
{
	//3D Model Asset Formats
	{".dae", ::doom::asset::eAssetType::THREE_D_MODEL},
	{ ".blend", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".bvh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".3ds", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ase", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".obj", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".glFT", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ply", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ifc", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".nff", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".smd", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".vta", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl2", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl3", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".pk3", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdmdcl2", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".md5mesh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".md5anim", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".md5camera ", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".q3o", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".q3s", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".raw", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ac", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".stl", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".irrmesh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".irr", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".off", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".dterxf", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".hmp", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mesh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".skeleton", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".material", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ms3d", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".lwo", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".lws", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".lxo", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".csm", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ply", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".cob", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".scn", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".fbx", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".assbin", ::doom::asset::eAssetType::THREE_D_MODEL },

	//////////////////////////////////////////////////////////////////////////

	{ ".txt", ::doom::asset::eAssetType::TEXT },
	{ ".ini", ::doom::asset::eAssetType::TEXT },

	/////////////////////////////////////////////////////

	{ ".glsl", ::doom::asset::eAssetType::SHADER },

	/////////////////////////////////////////////////////////

	{ ".jpg", ::doom::asset::eAssetType::TEXTURE },
	{ ".jpeg", ::doom::asset::eAssetType::TEXTURE },
	{ ".png", ::doom::asset::eAssetType::TEXTURE },
	{ ".bmp", ::doom::asset::eAssetType::TEXTURE },
	{ ".tga", ::doom::asset::eAssetType::TEXTURE },
	//{ ".hdr", ::doom::asset::eAssetType::TEXTURE },
	{ ".dds", ::doom::asset::eAssetType::TEXTURE }
};

const std::unordered_map<::doom::asset::eAssetType, std::string>  doom::assetimporter::Assetimporter::AssetInBuildExtension
{
	{::doom::asset::eAssetType::TEXTURE, ".dds"},
	{::doom::asset::eAssetType::THREE_D_MODEL, ".assbin"}

};

std::optional<::doom::asset::eAssetType> Assetimporter::GetAssetType(const std::filesystem::path& path)
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

