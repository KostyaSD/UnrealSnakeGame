// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "UI/SG_GameOverWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "World/SG_WorldUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/SG_GameUserSettings.h"

void USG_GameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BackToMenuButton);
	BackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToMenu);
	CloseGameButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseGame);
}

void USG_GameOverWidget::SetScore(uint32 Score)
{
	if (ScoreText)
	{
		ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
	}
}

void USG_GameOverWidget::SetResetGameKeyName(const FString& ResetGameKeyName)
{
	if (ResetGameText)
	{
		const FString ResetGameInfo = FString::Printf(TEXT("press <%s> to reset"), *ResetGameKeyName.ToLower());
		ResetGameText->SetText(FText::FromString(ResetGameInfo));
	}
}

void USG_GameOverWidget::OnBackToMenu()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
}

void USG_GameOverWidget::OnCloseGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void USG_GameOverWidget::OnNewGame()
{

}