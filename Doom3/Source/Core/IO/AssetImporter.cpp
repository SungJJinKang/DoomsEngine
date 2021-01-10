#define STB_IMAGE_IMPLEMENTATION
#include "AssetImporter.h"

#include <map>
#include <string>

#include "../Core.h"


/* Assimp threading
* 
Thread-safety / using Assimp concurrently from several threads¢Ò
The library can be accessed by multiple threads simultaneously, as long as the following prerequisites are fulfilled:

Users of the C++-API should ensure that they use a dedicated #Assimp::Importer instance for each thread. Constructing instances of #Assimp::Importer is expensive, so it might be a good idea to let every thread maintain its own thread-local instance (which can be used to load as many files as necessary).

The C-API is thread safe.

When supplying custom IO logic, one must make sure the underlying implementation is thread-safe.

Custom log streams or logger replacements have to be thread-safe, too.

Multiple concurrent imports may or may not be beneficial, however. For certain file formats in conjunction with little or no post processing IO times tend to be the performance bottleneck. Intense post processing together with ¡®slow¡¯ file formats like X or Collada might scale well with multiple concurrent imports.
*/


// Create a logger instance

#ifdef DEBUG_VERSION

/*
auto a = Assimp::DefaultLogger::create("", Logger::VERBOSE);

// Now I am ready for logging my stuff
Assimp::DefaultLogger::get()->info("this is my info-call");
*/

#endif

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
