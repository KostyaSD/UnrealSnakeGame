// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_StartGameWidget.generated.h"

class UButton;
class UComboBoxString;
class UWidgetSwitcher;

UCLASS()
class SNAKEGAME_API USG_StartGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OptionsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackOptionsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> GameSpeedComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> GridSizeComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameLevel;

	virtual void NativeOnInitialized() override;

private:

		int32 IndexSwitcher{0};
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnCloseGame();

	UFUNCTION()
	void ActiveWidgetSwitcher();

	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	void SaveSettings();

	void InitComboBox(
		const TObjectPtr<UComboBoxString>& ComboBox, TFunction<TArray<FString>()> OptionsGetter, TFunction<FString()> CurrentOptionGetter);
};