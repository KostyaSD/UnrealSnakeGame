// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SG_Pawn.generated.h"

UCLASS()
class SNAKEGAME_API ASG_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ASG_Pawn();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
};
