// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "World/SG_WallBox.h"
#include "Core/Grid.h"
#include "World/SG_WorldUtils.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldWallBox, All, All);

ASG_WallBox::ASG_WallBox()
{

	PrimaryActorTick.bCanEverTick = false;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	WallLeft = CreateDefaultSubobject<UStaticMeshComponent>("WallLeft");
	check(WallLeft);
	WallLeft->SetupAttachment(Origin);

	WallRight = CreateDefaultSubobject<UStaticMeshComponent>("WallRight");
	check(WallRight);
	WallRight->SetupAttachment(Origin);

	WallUp = CreateDefaultSubobject<UStaticMeshComponent>("WallUp");
	check(WallUp);
	WallUp->SetupAttachment(Origin);

	WallDown = CreateDefaultSubobject<UStaticMeshComponent>("WallDown");
	check(WallDown);
	WallDown->SetupAttachment(Origin);
}

void ASG_WallBox::SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize)
{
	if (!Grid)
	{
		UE_LOG(LogWorldWallBox, Fatal, TEXT("Grid is null, game aborted!"));
	}

	GridDim = Grid->dim();
	CellSize = InCellSize;
	WorldWidth = GridDim.width * CellSize;
	WorldHeight = GridDim.height * CellSize;

	SetupTransform(WallLeft,					   //
		FVector(WorldHeight, CellSize, CellSize),  //
		FVector(WorldHeight, CellSize, CellSize)   //
	);

	SetupTransform(WallRight,									   //
		FVector(WorldHeight, CellSize, CellSize),				   //
		FVector(WorldHeight, 2 * WorldWidth - CellSize, CellSize)  //
	);

	SetupTransform(WallUp,										   //
		FVector(CellSize, WorldWidth - 2 * CellSize, CellSize),	   //
		FVector(2 * WorldHeight - CellSize, WorldWidth, CellSize)  //
	);

	SetupTransform(WallDown,									 //
		FVector(CellSize, WorldWidth - 2 * CellSize, CellSize),	 //
		FVector(CellSize, WorldWidth, CellSize)					 //
	);
}

void ASG_WallBox::SetupTransform(UStaticMeshComponent* Mesh, FVector ScaleWall, FVector LocationWall)
{
	if (!Mesh->GetStaticMesh())
	{
		return;
	}
	const FBox Box = Mesh->GetStaticMesh()->GetBoundingBox();
	const auto Size = Box.GetSize();

	check(!Size.IsZero());
	Mesh->SetRelativeScale3D(ScaleWall / Size);
	Mesh->SetRelativeLocation(0.5 * LocationWall);
}