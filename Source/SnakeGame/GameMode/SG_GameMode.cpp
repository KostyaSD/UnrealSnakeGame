// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "GameMode/SG_GameMode.h"
#include "SG_GameMode.h"
#include "Core/Types.h"
#include "World/SG_Grid.h"

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	const Snake::Settings GS{GridSize.X, GridSize.Y};
	Game = MakeUnique<Snake::Game>(GS);
	check(Game.IsValid());

	const FTransform GridOrigin = FTransform::Identity;
	check(GetWorld());
	GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	check(GridVisual);
	GridVisual->SetModel(Game->grid(), CellSize);
	GridVisual->FinishSpawning(GridOrigin);
}
