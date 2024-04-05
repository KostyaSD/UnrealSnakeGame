// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Utils.h"

namespace SnakeGame
{

class Grid;
class Snake;
class Food;
class Bonus;

class SNAKEGAME_API Game
{
public:
	Game(const Settings& settings, const IPositionRandomizerPtr& randomizer = MakeShared<PositionRandomizer>());

	TSharedPtr<Grid> grid() const { return m_grid; }

	TSharedPtr<Snake> snake() const { return m_snake; }

	TSharedPtr<Food> food() const { return m_food; }

	TSharedPtr<Bonus> bonus() const { return m_bonus; }

	void update(float deltaSeconds, const Input& input);

	uint32 score() const { return m_score; }

	float gameTime() const { return m_gameTime; }

	void subscribeOnGameplayEvent(GameplayEventCallback callback);

private:
	const Settings c_settings;
	TSharedPtr<Grid> m_grid;
	TSharedPtr<Snake> m_snake;
	TSharedPtr<Food> m_food;
	TSharedPtr<Bonus> m_bonus;

	float m_moveSeconds{0.0f};
	bool m_gameOver{false};
	uint32 m_score{0};
	float m_gameTime{0.0f};

	TArray<GameplayEventCallback> m_gameplayEventCallbacks;

	void updateGrid();
	bool updateTime(float deltaSeconds);
	bool died(const Position& prevTailPosition) const;

	void generateFood();
	bool foodTaken() const;

	void generateBonus();
	bool bonusTaken() const;

	FORCEINLINE void dispatchEvent(GameplayEvent Event);
};
}  // namespace SnakeGame
