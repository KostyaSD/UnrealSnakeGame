// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "GameMode/SG_SandBoxGameMode.h"
#include "GameMode/SG_GameMode.h"
#include "World/SG_WallBox.h"
#include "World/SG_Grid.h"
#include "World/SG_WorldUtils.h"

ASG_SandBoxGameMode::ASG_SandBoxGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASG_SandBoxGameMode::StartPlay()
{
	Super::StartPlay();

	//const FTransform GridOrigin = FTransform::Identity;
	//check(GetWorld());
	//GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	//check(GridVisual);
	//GridVisual->SetModel(Game->grid(), CellSize);
	//GridVisual->FinishSpawning(GridOrigin);

	////init WallBox
	//WallBoxVisual = GetWorld()->SpawnActorDeferred<ASG_WallBox>(WallBoxVisualClass, GridOrigin);
	//WallBoxVisual->SetModel(Game->grid(), CellSize);
	//WallBoxVisual->FinishSpawning(GridOrigin);
}

void ASG_SandBoxGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
