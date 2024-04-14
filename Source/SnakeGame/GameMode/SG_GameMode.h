// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/Game.h"
#include "Engine/DataTable.h"
#include "InputActionValue.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;
class ASG_Snake;
class UInputAction;
class UInputMappingContext;
class ASG_Food;
class ASG_Bonus;
class ASG_HUD;
class ASG_WallBox;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASG_GameMode();
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	bool bOverrideUserSettings{false};

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	bool bOverrideGrid{false};

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	bool bOverrideWallBox{false};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100", EditCondition = "bOverrideUserSettings", EditConditionHides),
		Category = "Settings")
	FUintPoint GridDims{10, 10};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100", EditCondition = "bOverrideUserSettings", EditConditionHides),
		Category = "Settings")
	uint32 CellSize{10};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10", EditCondition = "bOverrideUserSettings", EditConditionHides),
		Category = "Settings")
	uint32 SnakeDefaultSize{5};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.01", ClampMax = "10", EditCondition = "bOverrideUserSettings", EditConditionHides),
		Category = "Settings")
	float GameSpeed{1.0f};

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "5", ClampMax = "25", EditCondition = "bOverrideUserSettings", EditConditionHides),
		Category = "Settings")
	int32 MaxTime{15};

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bOverrideGrid", EditConditionHides), Category = "Design")
	TSubclassOf<ASG_Grid> GridVisualClass;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bOverrideWallBox", EditConditionHides), Category = "Design")
	TSubclassOf<ASG_WallBox> WallBoxVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Snake> SnakeVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Food> FoodVisualClass;	
	
	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TSubclassOf<ASG_Bonus> BonusVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TObjectPtr<UDataTable> ColorsTable;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputAction> MoveForwardInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputAction> MoveRightInputAction;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bOverrideUserSettings", EditConditionHides), Category = "SnakeInput")
	TObjectPtr<UInputAction> ResetGameInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputMappingContext> InputMapping;

private:
	UPROPERTY()
	TObjectPtr<ASG_Grid> GridVisual;

	UPROPERTY()
	TObjectPtr<ASG_WallBox> WallBoxVisual;

	UPROPERTY()
	TObjectPtr<ASG_Snake> SnakeVisual;

	UPROPERTY()
	TObjectPtr<ASG_Food> FoodVisual;

	UPROPERTY()
	TObjectPtr<ASG_Bonus> BonusVisual;

	UPROPERTY()
	TObjectPtr<ASG_HUD> HUD;

	float TimeBar{0.0f};

private:
	bool IsNgOut = true;
	TSharedPtr<SnakeGame::Game> Game;
	uint32 ColorTableIndex{0};
	SnakeGame::Input SnakeInput{SnakeGame::Input::Default};

	SnakeGame::Settings MakeSettings();

	void UpdateColors();

	void SetupInput();
	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value);
	void OnGameReset(const FInputActionValue& Value);

	void SubscribeOnGameEvents();
};
