// Snake Game, Copyright GamesWID. All Rights Reserved.

#include "SnakeGame/Core/Game.h"
#include "SnakeGame/Core/Grid.h"
#include "SnakeGame/Core/Snake.h"
#include "SnakeGame/Core/Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

using namespace SnakeGame;

Game::Game(const Settings& settings) : c_settings(settings)
{
	m_grid = MakeShared<Grid>(settings.gridDims);
	m_snake = MakeShared<Snake>(settings.snake);
	m_food = MakeShared<Food>();
	updateGrid();
	generateFood();
}

void Game::update(float deltaSeconds, const Input& input)
{
	if (m_gameOver || !updateTime(deltaSeconds)) return;
	move(input);

	if (died())
	{
		m_gameOver = true;
	}

	// if (m_gameOver || !updateTime(deltaSeconds)) return;

	// const auto prevTailPosition = m_snake->tail();
	// m_snake->move(input);

	// if (died(prevTailPosition))
	//{
	//	m_gameOver = true;
	//	dispatchEvent(GameplayEvent::GameOver);
	//	return;
	// }

	// if (foodTaken())
	//{
	//	++m_score;
	//	m_snake->increase();
	//	dispatchEvent(GameplayEvent::FoodTaken);
	//	generateFood();
	// }

	// updateGrid();
}

void Game::move(const Input& input)
{
	m_snake->move(input);
	updateGrid();
}

void Game::updateGrid()
{
	m_grid->update(m_snake->body(), CellType::Snake);
	m_grid->printDebug();
}

bool Game::updateTime(float deltaSeconds)
{
	m_moveSeconds += deltaSeconds;
	if (m_moveSeconds < c_settings.gameSpeed) return false;
	m_moveSeconds = 0.0f;
	return true;
}

bool Game::died() const
{
	return m_grid->hitTest(m_snake->head(), CellType::Wall) ||	//
		   m_grid->hitTest(m_snake->head(), CellType::Snake);
}

void Game::generateFood()
{
	m_food->setPosition(m_grid->randomEmptyPosition());
	m_grid->update(m_food->position(), CellType::Food);
}
