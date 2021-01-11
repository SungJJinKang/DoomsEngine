#define STB_IMAGE_IMPLEMENTATION
#include "AssetImporter.h"

#include <map>
#include <string>

#include "../Core.h"







Assimp::Importer Doom::AssetImporter::MainThreadAssimpImporter{};
Assimp::Importer Doom::AssetImporter::MultiThreadAssimpImporter[MAX_ASSETIMPORTER_THREAD_COUNT]{};
 
template <Doom::AssetType assetType>
std::mutex Doom::AssetImporter::AssetImporterMutex{};

const std::map<std::string, Doom::AssetType> Doom::AssetImporter::AssetExtension
{
	//3D Model Asset Formats
	{"dae", Doom::AssetType::THREE_D_MODELL},
	{"blend", Doom::AssetType::THREE_D_MODELL},
	{"bvh", Doom::AssetType::THREE_D_MODELL},
	{"3ds", Doom::AssetType::THREE_D_MODELL},
	{"ase", Doom::AssetType::THREE_D_MODELL},
	{"obj", Doom::AssetType::THREE_D_MODELL},
	{"glFT", Doom::AssetType::THREE_D_MODELL},
	{"ply", Doom::AssetType::THREE_D_MODELL},
	{"dxf", Doom::AssetType::THREE_D_MODELL},
	{"ifc", Doom::AssetType::THREE_D_MODELL},
	{"nff", Doom::AssetType::THREE_D_MODELL},
	{"smd", Doom::AssetType::THREE_D_MODELL},
	{"vta", Doom::AssetType::THREE_D_MODELL},
	{"mdl", Doom::AssetType::THREE_D_MODELL},
	{"mdl2", Doom::AssetType::THREE_D_MODELL},
	{"mdl3", Doom::AssetType::THREE_D_MODELL},
	{"pk3", Doom::AssetType::THREE_D_MODELL},
	{"mdmdcl2", Doom::AssetType::THREE_D_MODELL},
	{"md5mesh", Doom::AssetType::THREE_D_MODELL},
	{"md5anim", Doom::AssetType::THREE_D_MODELL},
	{"md5camera ", Doom::AssetType::THREE_D_MODELL},
	{"q3o", Doom::AssetType::THREE_D_MODELL},
	{"q3s", Doom::AssetType::THREE_D_MODELL},
	{"raw", Doom::AssetType::THREE_D_MODELL},
	{"ac", Doom::AssetType::THREE_D_MODELL},
	{"stl", Doom::AssetType::THREE_D_MODELL},
	{"dxf", Doom::AssetType::THREE_D_MODELL},
	{"irrmesh", Doom::AssetType::THREE_D_MODELL},
	{"irr", Doom::AssetType::THREE_D_MODELL},
	{"off", Doom::AssetType::THREE_D_MODELL},
	{"dterxf", Doom::AssetType::THREE_D_MODELL},
	{"mdl", Doom::AssetType::THREE_D_MODELL},
	{"hmp", Doom::AssetType::THREE_D_MODELL},
	{"mesh", Doom::AssetType::THREE_D_MODELL},
	{"skeleton", Doom::AssetType::THREE_D_MODELL},
	{"material", Doom::AssetType::THREE_D_MODELL},
	{"ms3d", Doom::AssetType::THREE_D_MODELL},
	{"lwo", Doom::AssetType::THREE_D_MODELL},
	{"lws", Doom::AssetType::THREE_D_MODELL},
	{"lxo", Doom::AssetType::THREE_D_MODELL},
	{"csm", Doom::AssetType::THREE_D_MODELL},
	{"ply", Doom::AssetType::THREE_D_MODELL},
	{"cob", Doom::AssetType::THREE_D_MODELL},
	{"scn", Doom::AssetType::THREE_D_MODELL}

	//////////////////////////////////////////////////////////////////////////
};

void Doom::AssetImporter::AssimpLogStream::write(const char* message) 
{
	Doom::Debug::Log({ "Assimp Debugger : ", message });
}