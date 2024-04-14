// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "UI/SG_GameCompletedWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "World/SG_WorldUtils.h"
#include "Kismet/GameplayStatics.h"

void USG_GameCompletedWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BackToMenuButton);
	BackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToMenu);
	check(CloseGameButton);
	CloseGameButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseGame);
	check(NewGameButton);
	NewGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGame);
}
void USG_GameCompletedWidget::SetScore(uint32 Score)
{
	if (ScoreText)
	{
		ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
	}
}

void USG_GameCompletedWidget::OnStartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), GetWorld()->GetFName(), true);
}

void USG_GameCompletedWidget::OnBackToMenu()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MenuLevel);
}

void USG_GameCompletedWidget::OnCloseGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
