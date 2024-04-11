// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/SG_GameMode.h"
#include "Core/Game.h"
#include "SG_SandBoxGameMode.generated.h"

class ASG_Grid;
class ASG_WallBox;

UCLASS()
class SNAKEGAME_API ASG_SandBoxGameMode : public ASG_GameMode
{
	GENERATED_BODY()

public:
	ASG_SandBoxGameMode();
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

//protected:
//	UPROPERTY(EditDefaultsOnly, Category = "Design")
//	TSubclassOf<ASG_Grid> GridVisualClass;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Design")
//	TSubclassOf<ASG_WallBox> WallBoxVisualClass;
//
//private:
//	TSharedPtr<SnakeGame::Game> Game;
//
//	UPROPERTY()
//	TObjectPtr<ASG_Grid> GridVisual;
//
//	UPROPERTY()
//	TObjectPtr<ASG_WallBox> WallBoxVisual;
};