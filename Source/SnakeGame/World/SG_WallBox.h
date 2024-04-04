// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_WorldTypes.h"
// #include "SnakeGame/Core/Types.h"
#include "SG_WallBox.generated.h"

namespace SnakeGame
{
class Grid;
}

class UStaticMeshComponent;
UCLASS()
class SNAKEGAME_API ASG_WallBox : public AActor
{
	GENERATED_BODY()

public:
	ASG_WallBox();

	void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 CellSize);
	void UpdateColors(const FLinearColor& Color);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Origin;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallLeftMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallRightMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallUpMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallDownMesh;

private:
	FLinearColor GridWallColor;

	SnakeGame::Dim GridDim;
	uint32 CellSize;
	uint32 WorldWidth;
	uint32 WorldHeight;
};
