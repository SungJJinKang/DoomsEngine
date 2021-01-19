#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"
#include "Source/Core/Game/GameFlow.h"

#include "Source/Core/IO/AssetImporter/AssetImporter.h"

#include "Source/Core/Grahpics/Shader.h"
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

	
	{
		AssetImporter<AssetType::TEXT> importer{ 1 };

		auto future = importer.ImportAssetAsync("C:/Doom3FromScratch/Doom3/Assets/Shader/DefaultShader.glsl");
		auto str = future->get();

		if (str.has_value())
		{
			Shader shader{ str->String };
		}
		
	}
	

	GameFlow::Loop();

	//window terminated
}




void ExitGame()
{

}