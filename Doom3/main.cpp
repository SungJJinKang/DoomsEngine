#include "Source/Core/Game/GameCore.h"

#include "Source/Core/IO/AssetImporter.h"
using namespace Doom;

void ExitGame();



int main()
{
	GameCore::Init();

	ThreeDModelAsset asset;
	ThreeDModelAsset asset1;
	ThreeDModelAsset asset2;
	AssetImporter::ImportAsset<AssetType::THREE_D_MODELL>("C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj", asset);
	AssetImporter::ImportAsset<AssetType::THREE_D_MODELL>("C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj", asset1);
	AssetImporter::ImportAsset<AssetType::THREE_D_MODELL>("C:/Doom3FromScratch/Doom3/Assets/backpack/backpack.obj", asset2);
	while (GameCore::Loop())
	{
		
	}
}




void ExitGame()
{

}