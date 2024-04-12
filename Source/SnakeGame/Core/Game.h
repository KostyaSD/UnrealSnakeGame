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

class SNAKEGAME_API Game
{
public:
	Game(const Settings& settings, const IPositionRandomizerPtr& randomizer = MakeShared<PositionRandomizer>());

	TSharedPtr<Grid> grid() const { return m_grid; }

	TSharedPtr<Snake> snake() const { return m_snake; }

	TSharedPtr<Food> food() const { return m_food; }

	void update(float deltaSeconds, const Input& input, bool timeOut);

	uint32 score() const { return m_score; }

	void subscribeOnGameplayEvent(GameplayEventCallback callback);

private:
	Settings c_settings;  // const
	TSharedPtr<Grid> m_grid;
	TSharedPtr<Snake> m_snake;
	TSharedPtr<Food> m_food;

	float m_moveSeconds{0.0f};
	bool m_gameOver{false};
	uint32 m_score{0};

	TArray<GameplayEventCallback> m_gameplayEventCallbacks;

	void updateGrid();
	bool updateTime(float deltaSeconds);
	bool died(const Position& prevTailPosition) const;

	void generateFood();
	bool foodTaken() const;

	FORCEINLINE void dispatchEvent(GameplayEvent Event);
};
}  // namespace SnakeGame
