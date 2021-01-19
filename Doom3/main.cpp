#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"
#include "Source/Core/Game/GameFlow.h"

#include "Source/Core/Asset/Asset.h"
#include "Source/Core/IO/AssetImporter/AssetImporter.h"

#include "Source/Core/Grahpics/Shader.h"
using namespace Doom;

void ExitGame();

#include <filesystem>

int main()
{
	GameCore::Init();


	GameFlow::Loop();

	//window terminated
}




void ExitGame()
{

}