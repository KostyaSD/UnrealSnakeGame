// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SG_Grid.generated.h"

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
	GENERATED_BODY()

public:
	ASG_Grid();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
