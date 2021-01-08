#include "Source/Core/Game/GameCore.h"

using namespace Doom;

void InitGame(GameCore& gameCore);
void GameLoop(GameCore& gameCore);
void ExitGame(GameCore& gameCore);



int main()
{
	GameCore gameCore{};

	InitGame(gameCore);
	GameLoop(gameCore);
	
}

void InitGame(GameCore& gameCore)
{
	gameCore.Init();
}

void GameLoop(GameCore& gameCore)
{
	while (true)
	{
		gameCore.Loop();
	}
}

void ExitGame(GameCore& gameCore)
{

}