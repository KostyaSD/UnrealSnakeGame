// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "UI/SG_HUD.h"
#include "UI/SG_GameplayWidget.h"
#include "UI/SG_GameOverWidget.h"
#include "Core/Game.h"

ASG_HUD::ASG_HUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASG_HUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
	check(GameplayWidget);
	GameWidgets.Add(EUIGameState::GameInProgress, GameplayWidget);

	GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverWidgetClass);
	check(GameOverWidget);
	GameWidgets.Add(EUIGameState::GameOver, GameOverWidget);

	for (auto& [UIState, GameWidget] : GameWidgets)
	{
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
	if (!InGame) return;

	using namespace SnakeGame;

	Game = InGame;

	SetUIGameState(EUIGameState::GameInProgress);

	InGame->subscribeOnGameplayEvent(
		[&](GameplayEvent Event)
		{
			switch (Event)
			{
				case GameplayEvent::FoodTaken:	//
					GameplayWidget->SetScore(InGame->score());
					break;

				case GameplayEvent::GameCompleted: [[fallthrough]];
				case GameplayEvent::GameOver:  //
					GameOverWidget->SetScore(InGame->score());
					SetUIGameState(EUIGameState::GameOver);
					break;
			}
		});
}

void ASG_HUD::SetTimerValue(float CurrentTime, float InMaxTime)
{
	GameplayWidget->SetTimeFoodBar(InMaxTime - CurrentTime, InMaxTime);
}

void ASG_HUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASG_HUD::SetUIGameState(EUIGameState InGameState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameWidgets.Contains(InGameState))
	{
		CurrentWidget = GameWidgets[InGameState];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (InGameState == EUIGameState::GameInProgress && Game.IsValid())
	{
		GameplayWidget->SetScore(Game.Pin()->score());
		GameOverWidget->SetScore(Game.Pin()->score());
	}

	GameState = InGameState;
}
