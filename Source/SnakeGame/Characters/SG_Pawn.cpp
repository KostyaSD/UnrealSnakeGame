// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "Characters/SG_Pawn.h"

ASG_Pawn::ASG_Pawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASG_Pawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASG_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASG_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
