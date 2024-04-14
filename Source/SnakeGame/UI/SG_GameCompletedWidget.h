// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameCompletedWidget.generated.h"

class UTextBlock;
class UButton;
class UWorld;

UCLASS()
class SNAKEGAME_API USG_GameCompletedWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetScore(uint32 Score);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackToMenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MenuLevel;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnBackToMenu();

	UFUNCTION()
	void OnCloseGame();
};
