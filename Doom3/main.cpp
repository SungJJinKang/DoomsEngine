#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"
#include "Source/Core/Game/GameFlow.h"


using namespace doom;

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