// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "GameMode/SG_GameMode.h"
#include "SG_GameMode.h"
#include "Core/Types.h"
#include "Core/Grid.h"
#include "World/SG_Grid.h"
#include "World/SG_WorldTypes.h"
#include "Characters/SG_Pawn.h"

ASG_GameMode::ASG_GameMode()
{
	PrimaryActorTick.bCanEverTick= true;
}

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	// init core game
	SnakeGame::Settings GS;
	GS.gridDims = SnakeGame::Dim{GridDims.X, GridDims.Y};
	GS.gameSpeed = GameSpeed;
	GS.snake.defaultSize = SnakeDefaultsSize;
	GS.snake.startPosition = SnakeGame::Position{GridDims.X / 2, GridDims.Y / 2};

	Game = MakeUnique<SnakeGame::Game>(GS);
	check(Game.IsValid());

	// init world grid
	const FTransform GridOrigin = FTransform::Identity;
	check(GetWorld());
	GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	check(GridVisual);
	GridVisual->SetModel(Game->grid(), CellSize);
	GridVisual->FinishSpawning(GridOrigin);

	// set pawn location fitting grid in viewport
	auto* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	auto* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
	check(Pawn);
	check(Game->grid().IsValid());
	Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigin);

	check(ColorsTable);
	const auto RowsCount = ColorsTable->GetRowNames().Num();
	check(RowsCount >= 1);

	ColorTableIndex = FMath::RandRange(0, RowsCount - 1);
	UpdateColors();
}

void ASG_GameMode::UpdateColors()
{
	const auto RowName = ColorsTable->GetRowNames()[ColorTableIndex];
	const auto* ColorSet = ColorsTable->FindRow<FSnakeColors>(RowName, {});
	if (ColorSet)
	{
		GridVisual->UpdateColors(*ColorSet);
		// SnakeVisual->UpdateColors(*ColorSet);
		// FoodVisual->UpdateColor(ColorSet->FoodColor);
	}
}

void ASG_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Game.IsValid())
	{
		Game->update(DeltaSeconds, SnakeInput);
	}
}