// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "GameMode/SG_GameMode.h"
#include "SG_GameMode.h"
#include "Core/Types.h"
#include "Core/Grid.h"
#include "World/SG_Grid.h"
#include "World/SG_WorldTypes.h"
#include "Characters/SG_Pawn.h"

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	// init core game
	const SnakeGame::Settings GS{GridDims.X, GridDims.Y};
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
		//SnakeVisual->UpdateColors(*ColorSet);
		//FoodVisual->UpdateColor(ColorSet->FoodColor);

	}
}
