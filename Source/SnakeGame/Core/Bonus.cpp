// Snake Game, Copyright GamesWID. All Rights Reserved.


#include "Core/Bonus.h"

using namespace SnakeGame;

void Bonus::setPosition(const Position& position)
{
	m_position = position;
}

Position Bonus::position() const
{
	return m_position;
}
