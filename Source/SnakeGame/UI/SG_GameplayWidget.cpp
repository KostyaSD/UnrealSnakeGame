// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "UI/SG_GameplayWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "World/SG_WorldUtils.h"

void USG_GameplayWidget::SetScore(uint32 Score)
{
	if (ScoreText)
	{
		ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
	}
}

void USG_GameplayWidget::SetTimeFoodBar(float CurrentTime, float InMaxTime)
{
	TimeFoodBar->SetPercent(CurrentTime / InMaxTime);
}
