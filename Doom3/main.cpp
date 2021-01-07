#include "Source/Core/Game/GameFlow.h"

using namespace Doom;

void InitGame(GameFlow& gameflow);
void GameLoop(GameFlow& gameflow);
void ExitGame(GameFlow& gameflow);



int main()
{
	GameFlow gameflow{};

	InitGame(gameflow);
	GameLoop(gameflow);
	
}

void InitGame(GameFlow& gameflow)
{
	gameflow.Init();
}

void GameLoop(GameFlow& gameflow)
{
	while (true)
	{
		gameflow.Loop();
	}
}

void ExitGame(GameFlow& gameflow)
{

}