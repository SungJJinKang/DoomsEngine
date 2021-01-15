#include "Source/Core/Game/GameCore.h"

#include "Source/Core/IO/AssetImporter.h"
using namespace Doom;

void ExitGame();

#include <filesystem>

int main()
{
	GameCore::Init();

	ThreeDModelAsset asset;
	ThreeDModelAsset asset1;
	ThreeDModelAsset asset2;

	std::vector<std::filesystem::path> paths
	{
		"C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj",
		"C:/Doom3FromScratch/Doom3/Assets/dagothmask.fbx",
		"C:/Doom3FromScratch/Doom3/Assets/model.dae",
		"C:/Doom3FromScratch/Doom3/Assets/planet.obj",
		"C:/Doom3FromScratch/Doom3/Assets/rock.obj",
		"C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj",
		"C:/Doom3FromScratch/Doom3/Assets/dagothmask.fbx",
		"C:/Doom3FromScratch/Doom3/Assets/model.dae",
		"C:/Doom3FromScratch/Doom3/Assets/planet.obj",
		"C:/Doom3FromScratch/Doom3/Assets/rock.obj",
		"C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj",
		"C:/Doom3FromScratch/Doom3/Assets/dagothmask.fbx",
		"C:/Doom3FromScratch/Doom3/Assets/model.dae",
		"C:/Doom3FromScratch/Doom3/Assets/planet.obj",
		"C:/Doom3FromScratch/Doom3/Assets/rock.obj",
		"C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj",
		"C:/Doom3FromScratch/Doom3/Assets/dagothmask.fbx",
		"C:/Doom3FromScratch/Doom3/Assets/model.dae",
		"C:/Doom3FromScratch/Doom3/Assets/planet.obj",
		"C:/Doom3FromScratch/Doom3/Assets/rock.obj",
	};

	AssetImporter<AssetType::THREE_D_MODELL, 5> importer{};
	auto assets = importer.ImportAssetChunk(paths);
	while (GameCore::Loop())
	{
		
	}
}




void ExitGame()
{

}