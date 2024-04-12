// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_WorldTypes.h"
#include "SG_WallBox.generated.h"

namespace SnakeGame
{
class Grid;
}

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class SNAKEGAME_API ASG_WallBox : public AActor
{
	GENERATED_BODY()

public:
	ASG_WallBox();

	void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 CellSize);
	void SetupTransform(UStaticMeshComponent* Mesh, FVector ScaleWall, FVector LocationWall);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Origin;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallLeft;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallRight;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallUp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallDown;

private:
	FLinearColor GridWallColor;

	SnakeGame::Dim GridDim;
	uint32 CellSize;
	uint32 WorldWidth;
	uint32 WorldHeight;
};
