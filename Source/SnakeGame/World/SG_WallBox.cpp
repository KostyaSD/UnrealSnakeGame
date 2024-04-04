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

	WallLeftMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallLeftMesh");
	check(WallLeftMesh);
	WallLeftMesh->SetupAttachment(Origin);

	WallRightMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallRightMesh");
	check(WallRightMesh);
	WallRightMesh->SetupAttachment(Origin);

	WallUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallUpMesh");
	check(WallUpMesh);
	WallUpMesh->SetupAttachment(Origin);

	WallDownMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallDownMesh");
	check(WallDownMesh);
	WallDownMesh->SetupAttachment(Origin);
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

	FVector ScaleWall{};
	FVector LocationWall{};

	// scale mesh 1
	check(WallLeftMesh->GetStaticMesh());
	const FBox BoxL = WallLeftMesh->GetStaticMesh()->GetBoundingBox();
	const auto SizeL = BoxL.GetSize();

	check(SizeL.X);
	check(SizeL.Y);

	// scale mesh 2
	check(WallRightMesh->GetStaticMesh());
	const FBox BoxR = WallRightMesh->GetStaticMesh()->GetBoundingBox();
	const auto SizeR = BoxR.GetSize();

	check(SizeR.X);
	check(SizeR.Y);

	// scale mesh 3
	check(WallUpMesh->GetStaticMesh());
	const FBox BoxU = WallUpMesh->GetStaticMesh()->GetBoundingBox();
	const auto SizeU = BoxU.GetSize();

	check(SizeU.X);
	check(SizeU.Y);

	// scale mesh 4
	check(WallDownMesh->GetStaticMesh());
	const FBox BoxD = WallDownMesh->GetStaticMesh()->GetBoundingBox();
	const auto SizeD = BoxD.GetSize();

	check(SizeD.X);
	check(SizeD.Y);

	// 1 Left
	WallLeftMesh->SetRelativeScale3D(FVector(WorldHeight / SizeL.X, CellSize / SizeL.Y, CellSize / SizeL.Z));
	WallLeftMesh->SetRelativeLocation(FVector(0.5 * WorldHeight, 0.5 * CellSize, CellSize * 0.5));

	// 2 Right
	WallRightMesh->SetRelativeScale3D(FVector(WorldHeight / SizeR.X, CellSize / SizeR.Y, CellSize / SizeR.Z));
	WallRightMesh->SetRelativeLocation(FVector(0.5 * WorldHeight, WorldWidth - CellSize * 0.5, CellSize * 0.5));

	// 3 Up
	WallUpMesh->SetRelativeScale3D(FVector(CellSize / SizeU.X, (WorldWidth / SizeU.Y) - (2 * CellSize / SizeU.Y), CellSize / SizeU.Z));
	WallUpMesh->SetRelativeLocation(FVector(WorldHeight - CellSize * 0.5, 0.5 * WorldWidth, CellSize * 0.5));

	// 4 Down
	WallDownMesh->SetRelativeScale3D(FVector(CellSize / SizeD.X, (WorldWidth / SizeD.Y) - (2 * CellSize / SizeD.Y), CellSize / SizeD.Z));
	WallDownMesh->SetRelativeLocation(FVector(CellSize * 0.5, 0.5 * WorldWidth, CellSize * 0.5));
}

void ASG_WallBox::UpdateColors(const FLinearColor& Color)
{
	GridWallColor = Color;
	if (auto* WallLeftMaterial = WallLeftMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		WallLeftMaterial->SetVectorParameterValue("Color", Color);
	}

	if (auto* WallRightMaterial = WallRightMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		WallRightMaterial->SetVectorParameterValue("Color", Color);
	}

	if (auto* WallUpMaterial = WallUpMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		WallUpMaterial->SetVectorParameterValue("Color", Color);
	}
	
	if (auto* WallDownMaterial = WallDownMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		WallDownMaterial->SetVectorParameterValue("Color", Color);
	}
}

