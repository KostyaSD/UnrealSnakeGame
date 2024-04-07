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
	void SetGameTime(float Seconds);
	void SetScore(uint32 Score);
	void SetTimeFoodBar(float CurrentTime, float InMaxTime = 5.0f);
	void SetResetGameKeyName(const FString& ResetGameKeyName);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> TimeFoodBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResetGameText;
};