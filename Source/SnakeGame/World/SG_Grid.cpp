// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "World/SG_Grid.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid, All, All);

ASG_Grid::ASG_Grid()
{

	PrimaryActorTick.bCanEverTick = true;
}

void ASG_Grid::BeginPlay()
{
	Super::BeginPlay();
}

void ASG_Grid::SetModel(const TSharedPtr<Snake::Grid>& Grid, int32 InCellSize)
{
	if (!Grid.IsValid())
	{
		UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null, game aborted!"));
	}
	GridDim = Grid.Get()->dim();
	CellSize = InCellSize;
	WorldWidth = GridDim.widht * CellSize;
	WorldHeight = GridDim.height * CellSize;
}

void ASG_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawGrid();
}

void ASG_Grid::DrawGrid()
{
	for (int32 i = 0; i < GridDim.height + 1; ++i)
	{
		const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
		DrawDebugLine(GetWorld(), StartLocation, StartLocation + GetActorRightVector() * WorldWidth, FColor::Red, false, -1.0f, 0.0f, 1.0f);
	}

	for (int32 i = 0; i < GridDim.widht + 1; ++i)
	{
		const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
		DrawDebugLine(
			GetWorld(), StartLocation, StartLocation + GetActorForwardVector() * WorldHeight, FColor::Red, false, -1.0f, 0.0f, 1.0f);
	}
}
