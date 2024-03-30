// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/Game.h"
#include "Engine/DataTable.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;
class UDataTable;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASG_GameMode();
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
	FUintPoint GridDims{10, 10};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
	uint32 CellSize{10};
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10"), Category = "Settings")
	uint32 SnakeDefaultsSize{5};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.01", ClampMax = "10"), Category = "Settings")
	float GameSpeed{1.0f};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASG_Grid> GridVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	UDataTable* ColorsTable;

private:
	TUniquePtr<SnakeGame::Game> Game;

	UPROPERTY()
	ASG_Grid* GridVisual;

	uint32 ColorTableIndex{0};

	SnakeGame::Input SnakeInput{1, 0};

	void UpdateColors();
};
