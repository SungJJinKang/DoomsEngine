#include "Source/Core/Game/GameCore.h"

#include "Source/Core/IO/AssetImporter.h"
using namespace Doom;

void ExitGame();



int main()
{
	GameCore::Init();
	
	ThreeDModelAsset* asset;
	AssetImporter::ImportAsset<AssetType::THREE_D_MODELL>("C:/Doom3FromScratch/Doom3/Assets/backpack.obj", &asset);
	while (GameCore::Loop())
	{
		
	}
}




void ExitGame()
{

}