// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "UI/SG_GameOverWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "World/SG_WorldUtils.h"
#include "Kismet/GameplayStatics.h"

void USG_GameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BackToMenuButton);
	BackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToMenu);
	check(CloseGameButton);
	CloseGameButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseGame);
	check(NewGameButton);
	NewGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGame);
}

void USG_GameOverWidget::SetScore(uint32 Score)
{
	if (ScoreText)
	{
		ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
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

void USG_GameOverWidget::OnStartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), GetWorld()->GetFName(), true);
}
