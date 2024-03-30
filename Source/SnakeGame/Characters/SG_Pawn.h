// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/Types.h"
#include "SG_Pawn.generated.h"

class UCameraComponent;

UCLASS()
class SNAKEGAME_API ASG_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ASG_Pawn();

	void UpdateLocation(const SnakeGame::Dim& Dim, uint32 CellSize, const FTransform& GridOrigin);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

private:

	SnakeGame::Dim Dim;
	uint32 CellSize;
	FTransform GridOrigin;
	FDelegateHandle ResizeHandle;

	void OnViewportResized(FViewport* Viewport, uint32 Val);
};
