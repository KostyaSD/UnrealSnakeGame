// Snake Game, Copyright GamesWID. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
class SNAKEGAME_API Bonus
{
public:
	Bonus() = default;

	void setPosition(const Position& position);

	Position position() const;

private:
	Position m_position;
};
}  // namespace SnakeGame