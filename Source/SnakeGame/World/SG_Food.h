// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
	GENERATED_BODY()

public:
	ASG_Food();

	void SetModel(const TSharedPtr<SnakeGame::Food>& Food, uint32 CellSize, const SnakeGame::Dim& Dims);
	void UpdateColor(const FLinearColor& Color);

	void Explode();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Origin;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FoodMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FVX")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

private:
	TWeakPtr<SnakeGame::Food> Food;
	uint32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor FoodColor;
	FVector GetFoodWorldLocation() const;
};
