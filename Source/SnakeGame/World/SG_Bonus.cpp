// Snake Game, Copyright GamesWID. All Rights Reserved.


#include "World/SG_Bonus.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeGame/Core/Bonus.h"
#include "World/SG_WorldUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ASG_Bonus::ASG_Bonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>("BonusMesh");
	check(BonusMesh);
	BonusMesh->SetupAttachment(Origin);
}

void ASG_Bonus::SetModel(const TSharedPtr<SnakeGame::Bonus>& InBonus, uint32 InCellSize, const SnakeGame::Dim& InDims)
{
	Bonus = InBonus;
	CellSize = InCellSize;
	Dims = InDims;

	SnakeGame::WorldUtils::ScaleMesh(BonusMesh, 0.8 * FVector(CellSize));

	SetActorHiddenInGame(false);
}

void ASG_Bonus::UpdateColor(const FLinearColor& Color)
{
	BonusColor = Color;
	if (auto* FoodMaterial = BonusMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		FoodMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ASG_Bonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetBonusWorldLocation());
}

void ASG_Bonus::Explode()
{
	if (UNiagaraComponent* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetBonusWorldLocation()))
	{
		NS->SetVariableLinearColor("SnakeColor", BonusColor);
	}
}

FVector ASG_Bonus::GetBonusWorldLocation() const
{
	if (!Bonus.IsValid()) return FVector::ZeroVector;
	return SnakeGame::WorldUtils::LinkPositionToVector(Bonus.Pin()->position(), CellSize, Dims);
}

void ASG_Bonus::Hide(bool InHide)
{
	SetActorHiddenInGame(InHide);
}

