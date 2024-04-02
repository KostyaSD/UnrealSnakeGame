// Snake Game, Copyright GamesWID. All Rights Reserved.


#include "Settings/SG_GameUserSettings.h"

USG_GameUserSettings::USG_GameUserSettings()
{
	check(GameSpeeds.Num() == StaticEnum<EGameSpeed>()->NumEnums() - 1);
	check(GridSizes.Num() == StaticEnum<EGridSize>()->NumEnums() - 1);
}

USG_GameUserSettings* USG_GameUserSettings::Get()
{
	return GEngine ? Cast<USG_GameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

void USG_GameUserSettings::SaveSnakeSettings(EGameSpeed GameSpeed, EGridSize GridSize)
{
	CurrentSpeed = GameSpeeds[GameSpeed];
	CurrentGridSize = GridSizes[GridSize];
}