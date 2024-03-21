// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "GameMode/SG_GameMode.h"
#include "SG_GameMode.h"
#include "SnakeGame/Core/Types.h"

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	Snake::Settings GS{GridSize.X, GridSize.Y};
	Game = MakeUnique<Snake::Game>(GS);
}
