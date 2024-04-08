// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Types.h"
#include "World/SG_WorldTypes.h"
#include "SG_Bonus.generated.h"

namespace SnakeGame
{
class Bonus;
}

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASG_Bonus : public AActor
{
	GENERATED_BODY()

public:
	ASG_Bonus();

	virtual void Tick(float DeltaTime) override;

	void SetModel(const TSharedPtr<SnakeGame::Bonus>& InBonus, uint32 InCellSize, const SnakeGame::Dim& InDims);

	void UpdateColor(const FLinearColor& Color);

	void Hide();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Origin;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BonusMesh;

private:
	TWeakPtr<SnakeGame::Bonus> Bonus;
	uint32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor BonusColor;

	FVector GetBonusWorldLocation() const;
};