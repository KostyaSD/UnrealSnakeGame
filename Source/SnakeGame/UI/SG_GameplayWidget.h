// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameplayWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class SNAKEGAME_API USG_GameplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScore(uint32 Score);
	void SetSpeed(float Speed);
	void SetTimeFoodBar(float CurrentTime, float InMaxTime);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SpeedText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> TimeFoodBar;
};