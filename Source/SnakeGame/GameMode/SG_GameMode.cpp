// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "GameMode/SG_GameMode.h"
#include "SG_GameMode.h"
#include "SnakeGame/Core/Types.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_Grid.h"
#include "World/SG_WallBox.h"
#include "World/SG_Snake.h"
#include "World/SG_Food.h"
#include "World/SG_Bonus.h"
#include "World/SG_WorldTypes.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/SG_Pawn.h"
#include "UI/SG_HUD.h"
#include "World/SG_WorldUtils.h"
#include "Settings/SG_GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSnakeGameMode, All, All);

ASG_GameMode::ASG_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	// init core game
	Game = MakeShared<SnakeGame::Game>(MakeSettings());
	check(Game.IsValid());
	SubscribeOnGameEvents();

	// init world grid
	const FTransform GridOrigin = FTransform::Identity;
	check(GetWorld());
	GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	check(GridVisual);
	GridVisual->SetModel(Game->grid(), CellSize);
	GridVisual->FinishSpawning(GridOrigin);

	// init WallBox
	WallBoxVisual = GetWorld()->SpawnActorDeferred<ASG_WallBox>(WallBoxVisualClass, GridOrigin);
	WallBoxVisual->SetModel(Game->grid(), CellSize);
	WallBoxVisual->FinishSpawning(GridOrigin);

	// init world snake
	SnakeVisual = GetWorld()->SpawnActorDeferred<ASG_Snake>(SnakeVisualClass, GridOrigin);
	SnakeVisual->SetModel(Game->snake(), CellSize, Game->grid()->dim());
	SnakeVisual->FinishSpawning(GridOrigin);

	// init world food
	FoodVisual = GetWorld()->SpawnActorDeferred<ASG_Food>(FoodVisualClass, GridOrigin);
	FoodVisual->SetModel(Game->food(), CellSize, Game->grid()->dim());
	FoodVisual->FinishSpawning(GridOrigin);

	// init world bonus
	BonusVisual = GetWorld()->SpawnActorDeferred<ASG_Bonus>(BonusVisualClass, GridOrigin);
	BonusVisual->SetModel(Game->bonus(), CellSize, Game->grid()->dim());
	BonusVisual->FinishSpawning(GridOrigin);

	// set pawn location fitting grid in viewport
	auto* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	auto* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
	check(Pawn);
	check(Game->grid().IsValid());
	Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigin);

	// update colors
	check(ColorsTable);
	const auto RowsCount = ColorsTable->GetRowNames().Num();
	check(RowsCount >= 1);
	ColorTableIndex = FMath::RandRange(0, RowsCount - 1);
	UpdateColors();

	//
	SetupInput();

	//
	HUD = Cast<ASG_HUD>(PC->GetHUD());
	check(HUD);
	HUD->SetModel(Game);
	const FString ResetGameKeyName = SnakeGame::WorldUtils::FindActionKeyName(InputMapping, ResetGameInputAction);
	HUD->SetInputKeyNames(ResetGameKeyName);

	SnakeGame::WorldUtils::SetUIInput(GetWorld(), false);
}

void ASG_GameMode::NextColor()
{
	if (ColorsTable)
	{
		ColorTableIndex = (ColorTableIndex + 1) % ColorsTable->GetRowNames().Num();
		UpdateColors();
	}
}

void ASG_GameMode::UpdateColors()
{
	const auto RowName = ColorsTable->GetRowNames()[ColorTableIndex];
	const auto* ColorSet = ColorsTable->FindRow<FSnakeColors>(RowName, {});
	if (ColorSet)
	{
		GridVisual->UpdateColors(*ColorSet);
		SnakeVisual->UpdateColors(*ColorSet);
		WallBoxVisual->UpdateColors(ColorSet->GridWallColor);
		FoodVisual->UpdateColor(ColorSet->FoodColor);
		BonusVisual->UpdateColor(ColorSet->BonusColor);
	}
}

void ASG_GameMode::SetupInput()
{
	if (!GetWorld()) return;

	if (auto* PC = GetWorld()->GetFirstPlayerController())
	{
		if (auto* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			InputSystem->AddMappingContext(InputMapping, 0);
		}

		auto* Input = Cast<UEnhancedInputComponent>(PC->InputComponent);
		check(Input);
		Input->BindAction(MoveForwardInputAction, ETriggerEvent::Started, this, &ThisClass::OnMoveForward);
		Input->BindAction(MoveRightInputAction, ETriggerEvent::Started, this, &ThisClass::OnMoveRight);
		Input->BindAction(ResetGameInputAction, ETriggerEvent::Started, this, &ThisClass::OnGameReset);
	}
}

void ASG_GameMode::OnMoveForward(const FInputActionValue& Value)
{
	const float InputValue = Value.Get<float>();
	if (InputValue == 0.0f) return;
	SnakeInput = SnakeGame::Input{0, static_cast<int8>(InputValue)};
}

void ASG_GameMode::OnMoveRight(const FInputActionValue& Value)
{
	const float InputValue = Value.Get<float>();
	if (InputValue == 0.0f) return;
	SnakeInput = SnakeGame::Input{static_cast<int8>(InputValue), 0};
}

void ASG_GameMode::OnGameReset(const FInputActionValue& Value)
{
	if (const bool InputValue = Value.Get<bool>())
	{
		Game = MakeShared<SnakeGame::Game>(MakeSettings());
		check(Game.IsValid());
		SubscribeOnGameEvents();
		GridVisual->SetModel(Game->grid(), CellSize);
		SnakeVisual->SetModel(Game->snake(), CellSize, Game->grid()->dim());
		FoodVisual->SetModel(Game->food(), CellSize, Game->grid()->dim());
		BonusVisual->SetModel(Game->bonus(), CellSize, Game->grid()->dim());
		HUD->SetModel(Game);
		SnakeInput = SnakeGame::Input::Default;
		NextColor();
		SnakeGame::WorldUtils::SetUIInput(GetWorld(), false);
	}
}

void ASG_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Game.IsValid())
	{
		Game->update(DeltaSeconds, SnakeInput);
	}
	TimeBar += DeltaSeconds;
	if (TimeBar >= MaxTime)
	{
		TimeBar = 0.0f;
		OnGameplayEvent(SnakeGame::GameplayEvent::GameOver);
	}
	HUD->SetTimerValue(TimeBar, MaxTime);
}

SnakeGame::Settings ASG_GameMode::MakeSettings() const
{
	SnakeGame::Settings GS;

#if WITH_EDITOR
	if (bOverrideUserSettings)
	{
		GS.gridDims = SnakeGame::Dim{GridDims.X, GridDims.Y};
		GS.gameSpeed = GameSpeed;
	}
	else
#endif
		if (const auto* UserSettings = USG_GameUserSettings::Get())
	{
		GS.gridDims = UserSettings->GridSize();
		GS.gameSpeed = UserSettings->GameSpeed();
	}

	GS.snake.defaultSize = SnakeDefaultSize;
	GS.snake.startPosition = SnakeGame::Grid::center(GS.gridDims.width, GS.gridDims.height);
	return GS;
}

void ASG_GameMode::SubscribeOnGameEvents()
{
	Game->subscribeOnGameplayEvent([this](SnakeGame::GameplayEvent Event) { OnGameplayEvent(Event); });
}

void ASG_GameMode::OnGameplayEvent(SnakeGame::GameplayEvent Event)
{
	using namespace SnakeGame;
	switch (Event)
	{
		case GameplayEvent::GameOver:
			UE_LOG(LogSnakeGameMode, Display, TEXT("-------------- GAME OVER --------------"));
			UE_LOG(LogSnakeGameMode, Display, TEXT("-------------- SCORE: %i --------------"), Game->score());
			SnakeVisual->Explode();
			FoodVisual->Hide();
			BonusVisual->Hide();
			WorldUtils::SetUIInput(GetWorld(), true);
			break;
		case GameplayEvent::GameCompleted:
			UE_LOG(LogSnakeGameMode, Display, TEXT("-------------- GAME COMPLETED --------------"));
			UE_LOG(LogSnakeGameMode, Display, TEXT("-------------- SCORE: %i --------------"), Game->score());
			break;
		case GameplayEvent::FoodTaken:	//
			UE_LOG(LogSnakeGameMode, Display, TEXT("-------------- FOOD TAKEN --------------"));
			FoodVisual->Explode();
			TimeBar = 0.0f;
			break;
		case GameplayEvent::BonusTaken:	 //
			UE_LOG(LogSnakeGameMode, Display, TEXT("-------------- BONUS TAKEN --------------"));
			break;
	}
}